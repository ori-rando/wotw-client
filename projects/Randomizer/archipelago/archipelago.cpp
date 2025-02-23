#include <Common/ext.h>
#include <Common/vx.h>
#include <Core/api/game/game.h>
#include <Core/api/game/player.h>
#include <Core/api/uber_states/uber_state.h>
#include <Core/api/uber_states/uber_state_handlers.h>
#include <Core/core.h>
#include <Core/enums/game_areas.h>
#include <Core/events/task.h>
#include <Core/utils/json_serializers.h>
#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago.h>
#include <Randomizer/archipelago/archipelago_ids.h>
#include <Randomizer/archipelago/archipelago_protocol.h>
#include <Randomizer/archipelago/archipelago_save_meta.h>
#include <Randomizer/location_data/location.h>
#include <Randomizer/randomizer.h>
#include <Randomizer/seed/items/value_modifier.h>
#include <nlohmann/detail/conversions/from_json.hpp>


#define UUID_SYSTEM_GENERATOR
#include <uuid.h>

namespace randomizer::archipelago {
    auto archipelago_save_data = std::make_shared<ArchipelagoSaveData>();

    std::unordered_set<core::api::uber_states::UberState> locations_set;
    [[maybe_unused]]
    auto on_location_collection_loading = event_bus().register_handler(RandomizerEvent::LocationCollectionLoaded, EventTiming::Before, [](auto, auto) {
        locations_set.clear();
    });

    [[maybe_unused]]
    auto on_location_collection_loaded = event_bus().register_handler(RandomizerEvent::LocationCollectionLoaded, EventTiming::After, [](auto, auto) {
        for (const auto& location: location_collection().locations()) {
            core::api::uber_states::UberState loc_uber;
            loc_uber = core::api::uber_states::UberState(location.condition.state.group_int(), location.condition.state.state());

            auto existing_it = locations_set.find(loc_uber);
            if (existing_it == locations_set.end()) {
                locations_set.insert(loc_uber);
            }
        }

        modloader::info("archipelago", "Built location set");
        //}
    });

    [[maybe_unused]]
    auto on_game_ready = modloader::event_bus().register_handler(ModloaderEvent::GameReady, [](auto) {
        core::save_meta::register_slot(SaveMetaSlot::ArchipelagoData, SaveMetaSlotPersistence::None, archipelago_save_data);
    });

    // On game completion
    [[maybe_unused]]
    auto uber_state_bus_handle = core::api::uber_states::single_notification_bus().register_handler(
        core::api::uber_states::UberState(34543, 11226),
        [](const core::api::uber_states::UberStateCallbackParams& params, auto) {
            if (params.state.get<bool>()) {
                archipelago_client().game_finished_handler();
            }
        }
    );

    // On location checked
    [[maybe_unused]]
    auto on_uber_state_changed = core::api::uber_states::notification_bus().register_handler([](auto params) {
        auto existing_it = locations_set.find(core::api::uber_states::UberState(params.state));

        if (existing_it != locations_set.end()) {
            archipelago_client().location_handler(params);
        };
    });

    // Resync items
    [[maybe_unused]]
    auto on_new_game = core::api::game::event_bus().register_handler(GameEvent::NewGameInitialized, EventTiming::After, [](auto, auto) {
        archipelago_client().set_last_index(0);
    });
    [[maybe_unused]]
    auto on_restore_checkpoint = core::api::game::event_bus().register_handler(GameEvent::RestoreCheckpoint, EventTiming::After, [](auto, auto) {
        archipelago_client().ask_resync();
        modloader::info("archipelago", "Resync asked: Restore Checkpoint");
    });


    ArchipelagoClient::ArchipelagoClient() {
        m_websocket.setOnMessageCallback([this](const auto& msg) { on_websocket_message(msg); });
    }

    void ArchipelagoClient::connect(const std::string_view url, const std::string_view slot_name, const std::string_view password) {
        // Load files for data packages
        read_data_package("ap_data_package.json", m_data_package_cache);
        read_data_package("ap_item_id_to_name.json", m_item_id_to_name);
        read_data_package("ap_location_id_to_name.json", m_location_id_to_name);

        m_slot_name = slot_name;
        m_password = password;
        m_websocket.stop();
        m_websocket.setUrl(std::string(url));
        m_websocket.setPingInterval(30);
        m_websocket.disableAutomaticReconnection();
        m_websocket.start();
        m_should_connect = true;
        modloader::info("archipelago", "AP client connected.");
    }

    void ArchipelagoClient::disconnect() {
        m_should_connect = false;
        m_websocket.stop();
        modloader::info("archipelago", "AP client disconnected.");
    }

    bool ArchipelagoClient::is_connected() const { return m_websocket.getReadyState() == ix::ReadyState::Open; }

    void ArchipelagoClient::on_websocket_message(ix::WebSocketMessagePtr const& msg) {
        switch (msg->type) {
            case ix::WebSocketMessageType::Message: {
                modloader::info("archipelago", "Data package received");
                auto message_string = msg.get()->str;

                try {
                    nlohmann::json json = nlohmann::json::parse(message_string);
                    for (auto& packet: json) {
                        std::lock_guard guard(m_packet_mutex);
                        m_packets.push_back(packet);

                        const auto message = messages::parse_server_message(packet);

                        if (message.has_value()) {
                            handle_server_message(*message);
                        }
                    }
                } catch (nlohmann::json::exception& e) {
                    modloader::error("archipelago", std::format("Failed to parse message: {}, {}", e.what(), message_string));
                }
                m_packets.clear();
                break;
            }
            case ix::WebSocketMessageType::Open: {
                modloader::info("archipelago", "Connected to server");

                const uuids::uuid uuid = uuids::uuid_system_generator{}();

                send_message(
                    messages::Connect{
                        m_password,
                        "Ori and the Will of the Wisps",
                        m_slot_name,
                        uuids::to_string(uuid),
                        messages::NetworkVersion{0, 5, 0, "Version"},
                        0b111,
                        {"AP"},
                        false,
                        "Connect",
                }
                );
                break;
            }
            case ix::WebSocketMessageType::Close: {
                auto closed_reason = std::format("websocket closed '{}': {}", msg->closeInfo.code, msg->closeInfo.reason);
                modloader::warn("archipelago", closed_reason);

                if (m_should_connect) {
                    // If we are in here we did not expect this disconnect, underlying socket will auto reconnect.
                    core::events::schedule_task(3.f, [this] {
                        if (m_should_connect && !is_connected()) {
                            connect(m_websocket.getUrl(), m_slot_name, m_password);
                        }
                    });
                }
                break;
            }
            case ix::WebSocketMessageType::Error:
                core::events::schedule_task(10.f, [this]() {
                    if (m_should_connect) {
                        connect(m_websocket.getUrl(), m_slot_name, m_password);
                    }
                });
                break;
            case ix::WebSocketMessageType::Ping:
            case ix::WebSocketMessageType::Pong:
            case ix::WebSocketMessageType::Fragment:
                break;
        }
    }

    void ArchipelagoClient::location_handler(auto& params) {
        location_data::Location location{
            "AP", // Dummy infos, only the uber states are used
            GameArea::Void,
            location_data::LocationType::Unknown,
            core::api::uber_states::UberStateCondition(params.state, BooleanOperator::Greater, params.value)
        };
        ids::archipelago_id_t location_id{ids::get_location_id(location)};
        m_cached_locations.insert(location_id); // Stores the locations that are checked, but not yet validated by the server: useful for resync
        send_message(messages::LocationChecks{m_cached_locations, "LocationChecks"});
        modloader::info(
            "archipelago", std::format("Location checked. Group: {}, State: {}, Value: {}.", params.state.group_int(), params.state.state(), params.value)
        );
    }

    void ArchipelagoClient::game_finished_handler() { send_message(messages::StatusUpdate{messages::ClientStatus::ClientGoal, "StatusUpdate"}); }


    void ArchipelagoClient::update_data_package(const std::unordered_map<std::string, messages::GameData>& new_data) {
        for (auto& [game, data]: new_data) {
            m_data_package_cache[game] = data;
            m_item_id_to_name[game] = parse_data_package(data.item_name_to_id);
            m_location_id_to_name[game] = parse_data_package(data.location_name_to_id);
            modloader::info("archipelago", std::format("Data packages for {} updated.", game));
        }
        write_file(nlohmann::json(m_data_package_cache), "ap_data_package.json");
        write_file(nlohmann::json(m_item_id_to_name), "ap_item_id_to_name.json");
        write_file(nlohmann::json(m_location_id_to_name), "ap_location_id_to_name.json");
    }

    ArchipelagoClient::IdToName ArchipelagoClient::parse_data_package(const std::unordered_map<std::string, ids::archipelago_id_t>& data) {
        ArchipelagoClient::IdToName parsed_data;
        for (auto& [name, id]: data) {
            parsed_data[id] = name;
        }
        return parsed_data;
    }

    int ArchipelagoClient::get_last_index() { return archipelago_save_data->last_item_index; };

    void ArchipelagoClient::set_last_index(int index) { archipelago_save_data->last_item_index = index; };

    std::string ArchipelagoClient::get_item_name(const messages::NetworkItem& item, bool is_local) {
        messages::NetworkPlayer player = m_player_map[item.player];
        std::string game;
        if (is_local) { // When receiving items
            game = "Ori and the Will of the Wisps";
        } else { // When sending items
            game = m_slots[std::to_string(player.slot)].game;
        }
        auto existing_it = m_item_id_to_name[game].find(item.item);
        if (existing_it != m_item_id_to_name[game].end()) {
            return m_item_id_to_name[game][item.item];
        } else {
            modloader::error("archipelago", std::format("Failed to convert item ID {} from game {} to its name.", item.item, game));
            return std::format("Unknown item name from {}", game);
        };
    }

    std::string ArchipelagoClient::get_player_name(int player) { return m_player_map[player].alias; }

    std::string ArchipelagoClient::get_location_name(ids::archipelago_id_t id, const std::string& game) {
        auto existing_it = m_location_id_to_name[game].find(id);
        if (existing_it != m_location_id_to_name[game].end()) {
            return m_location_id_to_name[game][id];
        } else {
            modloader::error("archipelago", std::format("Failed to convert location ID {} from game {} to its name.", id, game));
            return std::format("Unknown location name from {}.", game);
        };
    }

    void ArchipelagoClient::collect_location(const ids::archipelago_id_t location_id) {
        // Collect locations from RoomUpdate and Connected packets, useful for coop
        // TODO does not work
        location_data::Location location{ids::get_location_from_id(location_id)};
        set_state(location.condition.state.group_int(),location.condition.state.state(), location.condition.value);
    }

    void ArchipelagoClient::set_state(int group, int state, auto value) {
        core::events::schedule_task_for_next_update([group, state, value] {
            core::api::uber_states::UberState(group, state).set(value);
            modloader::info("archipelago", std::format("Set {}|{} to {}", group, state, value));
        });
    }

    void ArchipelagoClient::apply_resources() {
        for (auto resource: m_resource_cache) {
            switch (resource.type) {
                case ids::ResourceType::SpiritLight: {
                    const auto& spirit_light = core::api::game::player::spirit_light();
                    const auto& spirit_light_collected = core::api::uber_states::UberState(UberStateGroup::RandoStats, 3);

                    spirit_light.set(spirit_light.get() + resource.value);
                    spirit_light_collected.set<int>(spirit_light_collected.get<int>() + resource.value);
                    break;
                }
                case ids::ResourceType::GorlekOre: {
                    const auto& gorlek_ore = core::api::game::player::ore();
                    const auto& gorlek_ore_collected = core::api::uber_states::UberState(UberStateGroup::RandoStats, 5);

                    gorlek_ore.set(gorlek_ore.get() + 1);
                    gorlek_ore_collected.set<int>(gorlek_ore_collected.get<int>() + 1);
                    break;
                }
                case ids::ResourceType::Keystone: {
                    const auto& keystone = core::api::game::player::keystones();
                    const auto& keystone_collected = core::api::uber_states::UberState(UberStateGroup::RandoStats, 0);

                    keystone.set(keystone.get() + 1);
                    keystone_collected.set<int>(keystone_collected.get<int>() + 1);
                    break;
                }
                case ids::ResourceType::ShardSlot: {
                    const auto& shard_slot = core::api::game::player::shard_slots();

                    shard_slot.set(shard_slot.get() + 1);
                    break;
                }
                case ids::ResourceType::HealthFragment: {
                    const auto& max_health = core::api::game::player::max_health();
                    const auto& health = core::api::game::player::health();

                    max_health.set(max_health.get() + 5);
                    health.set(static_cast<float>(max_health.get()));
                    break;
                }
                case ids::ResourceType::EnergyFragment: {
                    const auto& max_energy = core::api::game::player::max_energy();
                    const auto& energy = core::api::game::player::energy();

                    max_energy.set(max_energy.get() + 0.5f);
                    energy.set(max_energy.get());
                    break;
                }
            }
        }
        m_resource_cache.clear();
    }

    void ArchipelagoClient::give_item(messages::NetworkItem const& net_item) {
        std::variant<ids::Location, ids::BooleanItem, ids::ResourceItem, ids::UpgradeItem> item = ids::get_item(net_item.item);
        item |
            vx::match{
                [this](const ids::BooleanItem& item) {
                    set_state(item.uber_group, item.uber_state, true);
                    if (item.uber_group == 945 & item.uber_state == 58183) { // Central Luma TP
                        set_state(5377, 63173, true);
                    }
                },
                [this](const ids::UpgradeItem& item) {
                    std::vector<core::api::uber_states::UberState> item_uberstates;
                    set_state(item.uber_group, item.uber_state, true);
                    if (item.uber_group == static_cast<int16_t>(UberStateGroup::RandoUpgrade)) {
                        // Currently this is always true, as all upgrade items have this UberGroup.
                        switch (item.uber_state) { // Handle upgrades that affect multiple uberstates.
                            case 48: { // Splinter Shurikens
                                set_state(item.uber_group, 49, true);
                                break;
                            }
                            case 80: { // Skill Velocity
                                set_state(item.uber_group, 81, true);
                                set_state(item.uber_group, 82, true);
                                set_state(item.uber_group, 83, true);
                                set_state(item.uber_group, 84, true);
                                set_state(item.uber_group, 86, true);
                                set_state(item.uber_group, 90, true);
                                break;
                            }
                            case 87: { // Jumpgrade
                                set_state(item.uber_group, 88, true);
                                set_state(item.uber_group, 89, true);
                                break;
                            }
                            default: {
                                break;
                            }
                        }
                    }
                },
                [this](const ids::ResourceItem& item) {
                    m_resource_cache.emplace_back(item.type, item.value);
                    core::events::schedule_task_for_next_update([this] { apply_resources(); });
                },
                [net_item](const ids::Location& item) {
                    modloader::error("archipelago", std::format("AP ID {} corresponds to a location, expected an item.", net_item.item));
                },
            };
        modloader::info("archipelago", std::format("Received item: {} from {}.", get_item_name(net_item, true), get_player_name(net_item.player)));
        queue_reach_check();
        core::message_controller().queue_central({
            .text = core::Property<std::string>(std::format("{} from {}.", get_item_name(net_item, true), get_player_name(net_item.player))),
            .show_box = true,
        });

    }

    void ArchipelagoClient::read_data_package(const std::string& file_name, auto& data) {
        nlohmann::json j;
        if (!load_json_file(file_name, j)) {
            // Something went wrong
            // Error message is printed to modloader log
            return;
        }
        nlohmann::from_json(j, data);
    }

    void ArchipelagoClient::write_file(const nlohmann::json& data, const std::string& file_name) {
        std::ofstream o(modloader::base_path() / file_name);
        o << std::setw(4) << data << std::endl;
        modloader::info("Data", data.dump());
        modloader::info("archipelago", std::format("Write {} data package.", file_name));
    }

    void ArchipelagoClient::ask_resync() {
        send_message(messages::Sync{"Sync"});
        modloader::info("archipelago", "Sent Sync packet to AP server.");
    }

    void ArchipelagoClient::handle_server_message(messages::ap_server_message_t const& message) {
        message |
            vx::match{
                [this](const messages::Connected& message) {
                    modloader::info("archipelago", "Parsing Connected Packet");
                    m_player_map[0] = messages::NetworkPlayer{0, 0, "Archipelago", "Archipelago"};
                    for (auto& player: message.players) {
                        m_player_map[player.slot] = player;
                    }
                    m_slots = message.slot_info;
                    for (ids::archipelago_id_t location_id: message.checked_locations) {
                        collect_location(location_id);
                    }
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(std::format("Connected to Archipelago as {}.", m_slot_name)),
                        .show_box = true,
                    });
                },
                [](const messages::ConnectionRefused& message) {
                    modloader::info("archipelago", "Parsing ConnectionRefused Packet");
                    for (const std::string& error: message.errors) {
                        modloader::error("archipelago", std::format("Connection refused: {}.", error));
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(std::format("Connection to Archipelago refused: {}.", error)),
                            .show_box = true,
                        });
                    }
                },
                [this](const messages::RoomInfo& message) {
                    modloader::info("archipelago", "Parsing RoomInfo Packet");
                    modloader::info(
                        "archipelago", std::format("AP server version: {}.{}.{}", message.version.major, message.version.minor, message.version.build)
                    );
                    modloader::info(
                        "archipelago",
                        std::format(
                            "AP generator version: {}.{}.{}", message.generator_version.major, message.generator_version.minor, message.generator_version.build
                        )
                    );
                    modloader::info("archipelago", std::format("Hint cost: {}, Location points: {}.", message.hint_cost, message.location_check_points));

                    std::optional<std::string> ap_seed = game_seed().info().meta.archipelago_seed;
                    if (message.seed_name != ap_seed) {
                        modloader::warn(
                            "archipelago",
                            std::format(
                                "Seed from RoomInfo ({}) does not match the seed from the .wotwr file ({}).", message.seed_name, ap_seed.value_or("None")
                            )
                        );
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(
                                std::string("The seeds from the file and the server are different.\nMaybe you opened the wrong .wotwr file.")
                            ),
                            .show_box = true,
                        });
                    }

                    // Update data package
                    std::vector<std::string> outdated_games;
                    for (auto& [game, checksum]: message.datapackage_checksums) {
                        if (checksum != m_data_package_cache[game].checksum) {
                            outdated_games.push_back(game);
                            modloader::info("archipelago", std::format("Data packages for {} are obsolete.", game));
                        }
                    }
                    if (!outdated_games.empty()) {
                        send_message(messages::GetDataPackage{outdated_games, "GetDataPackage"});
                        modloader::info("archipelago", "Sent GetDataPackage packet to AP server.");
                    }
                },
                [this](const messages::ReceivedItems& message) {
                    modloader::info("archipelago", "Parsing ReceivedItems Packet");
                    modloader::info(
                        "archipelago",
                        std::format("Message index: {}, Saved index: {}, Message length {}", message.index, get_last_index(), message.items.size())
                    );
                    if (message.index == get_last_index() + 1) {
                        give_item(message.items[0]);
                        set_last_index(message.index);
                    } else if (message.index == 0) {
                        // AP server sent all the received items, only add the new ones
                        int start_index = get_last_index() == 0 ? 0 : get_last_index() + 1;
                        for (int index{start_index}; index < message.items.size(); ++index) {
                            give_item(message.items[index]);
                        }
                        set_last_index(static_cast<int>(message.items.size() - 1));
                    } else {
                        ask_resync();
                    }
                },
                [this](const messages::LocationInfo& message) {
                    modloader::info("archipelago", "Parsing LocationInfo Packet");
                    for (const messages::NetworkItem item: message.locations) {
                        m_cached_locations.erase(item.location);
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(std::format("{} sent to {}.", get_item_name(item, false), get_player_name(item.player))),
                            .show_box = true,
                        });
                    }
                },
                [this](const messages::RoomUpdate& message) {
                    modloader::info("archipelago", "Parsing RoomUpdate Packet");
                    for (auto& player: message.players) {
                        m_player_map[player.slot] = player;
                    }
                    for (ids::archipelago_id_t location_id: message.checked_locations) {
                        collect_location(location_id);
                        m_cached_locations.erase(location_id); // Remove location from the cache if it existed in it.
                    }
                },
                [this](const messages::PrintJSON& message) {
                    modloader::info("archipelago", "Parsing PrintJSON Packet");
                    switch (message.type) {
                        case "ItemSend" || "ItemCheat": {
                            core::message_controller().queue_central({
                                    .text = core::Property<std::string>(std::format("{} sent to {}.", get_item_name(message.item, false), get_player_name(message.receiving))),
                                    .show_box = true,
                                });
                            break;
                            }
                        case "Hint": {
                            core::message_controller().queue_central({
                                    .text = core::Property<std::string>(std::format("{} for {} is in {}.", get_item_name(message.item, false), get_location_name(message.item.location, "Ori and the Will of the Wisps"))),
                                    .show_box = true,
                                });
                            break;
                        }
                        case "Countdown": {
                            core::message_controller().queue_central({
                                .text = core::Property<std::string>(std::format("Countdown: {}", message.countdown)),
                                .show_box = true,
                            });
                            break;
                        }
                        default: {
                            std::string text = message.type;
                            for (auto& print_text : message.data) {
                                text += print_text.text;
                            }
                        }
                    }
                },
                [](const messages::InvalidPacket& message) {
                    modloader::info("archipelago", "Parsing InvalidPacket Packet");
                    modloader::error("archipelago", std::format("{}: Invalid packet sent {}: {}.", message.type, message.original_cmd, message.text));
                },
                [this](const messages::DataPackage& message) {
                    modloader::info("archipelago", "Parsing DataPackage Packet");
                    update_data_package(message.data.games);
                },
            };
    }
} // namespace randomizer::archipelago

// TODO list:
// Make a queue for received messages (see Network.cpp with the mutex)
// Formatting for PrintJSON
// Add death link support (see core/api/game/death_listener + add the tag in Connect packet)
// Clear the locations sets or do not remake them
