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
#include <Randomizer/seed/items/refill.h>
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
    });

    [[maybe_unused]]
    auto on_game_ready = modloader::event_bus().register_handler(ModloaderEvent::GameReady, [](auto) {
        core::save_meta::register_slot(SaveMetaSlot::ArchipelagoData, SaveMetaSlotPersistence::None, archipelago_save_data);
    });

    ArchipelagoClient::ArchipelagoClient() {
        m_websocket.setOnMessageCallback([this](const auto& msg) { on_websocket_message(msg); });

        // Load files for data packages
        read_data_package("ap_data_package.json", m_data_package_cache);
        read_data_package("ap_item_id_to_name.json", m_item_id_to_name);
        read_data_package("ap_location_id_to_name.json", m_location_id_to_name);

        // On game completion
        [[maybe_unused]]
        auto uber_state_bus_handle = core::api::uber_states::single_notification_bus().register_handler(
            core::api::uber_states::UberState(34543, 11226),
            [this](const core::api::uber_states::UberStateCallbackParams& params, auto) {
                if (params.state.get<bool>()) {
                    send_message(messages::StatusUpdate{messages::ClientStatus::ClientGoal});
                }
            }
        );

        // On location checked
        [[maybe_unused]]
        auto on_uber_state_changed = core::api::uber_states::notification_bus().register_handler([this](auto params) {
            auto existing_it = randomizer::archipelago::locations_set.find(core::api::uber_states::UberState(params.state));

            if (existing_it != randomizer::archipelago::locations_set.end()) {
                randomizer::location_data::Location location{
                    "AP", // Dummy infos, only the uber states are used
                    GameArea::Void,
                    randomizer::location_data::LocationType::Unknown,
                    core::api::uber_states::UberStateCondition(params.state, BooleanOperator::Greater, params.value)
                };
                ids::archipelago_id_t location_id{ids::get_location_id(location)};
                m_cached_locations.insert(location_id); // Stores the locations that are checked, but not yet validated by the server: useful for resync
                send_message(messages::LocationChecks{m_cached_locations}); // TODO send a vector instead ?
                modloader::info(
                    "archipelago",
                    std::format("Location checked. State: {}, Group: {}, Value: {}.", params.state.state(), params.state.group_int(), params.value)
                );
            };
        });

        // Resync items
        [[maybe_unused]] auto on_new_game = core::api::game::event_bus().register_handler(
            GameEvent::NewGameInitialized, EventTiming::After, [this](auto, auto) { ask_resync(); }
        );
        [[maybe_unused]] auto on_respawn(core::api::game::event_bus().register_handler(GameEvent::Respawn, EventTiming::After, [this](auto, auto) {
            ask_resync();
        }));
        [[maybe_unused]] auto on_restore_checkpoint(
            core::api::game::event_bus().register_handler(GameEvent::RestoreCheckpoint, EventTiming::After, [this](auto, auto) { ask_resync(); })
        );
        [[maybe_unused]] auto on_save_loaded(
            core::api::game::event_bus().register_handler(GameEvent::FinishedLoadingSave, EventTiming::After, [this](auto, auto) { ask_resync(); })
        );
    }

    void ArchipelagoClient::connect(const std::string_view url, const std::string_view slot_name, const std::string_view password) {
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

    bool ArchipelagoClient::is_connected() const { return m_websocket.getReadyState() == ix::ReadyState::Open; }

    void ArchipelagoClient::on_websocket_message(ix::WebSocketMessagePtr const& msg) {
        switch (msg->type) {
            case ix::WebSocketMessageType::Message: {
                auto message_string = msg.get()->str;

                try {
                    nlohmann::json json(message_string);

                    const auto message = messages::parse_server_message(json);

                    if (message.has_value()) {
                        handle_server_message(*message);
                    }
                } catch (nlohmann::json::exception& e) {
                    modloader::error("archipelago", std::format("Failed to parse message: {}, {}", e.what(), message_string));
                }
                break;
            }
            case ix::WebSocketMessageType::Open: {
                modloader::info("archipelago", "Connected to server");

                const uuids::uuid uuid = uuids::uuid_system_generator{}();

                send_message(messages::Connect{
                    m_password,
                    "Ori and the Will of the Wisps",
                    m_slot_name,
                    uuids::to_string(uuid),
                    messages::NetworkVersion{0, 5, 0},
                    0b111,
                    {"AP"},
                    false,
                });
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

    void ArchipelagoClient::update_data_package(const std::unordered_map<std::string, messages::GameData>& new_data) {
        for (auto& [game, data]: new_data) {
            m_data_package_cache.insert_or_assign(game, data);
            m_item_id_to_name.insert_or_assign(game, parse_data_package(data.item_name_to_id));
            m_location_id_to_name.insert_or_assign(game, parse_data_package(data.location_name_to_id));
            modloader::info("archipelago", std::format("Data packages for {} updated.", game));
        }
        write_file(m_data_package_cache, "ap_data_package.json");
        write_file(m_item_id_to_name, "ap_item_id_to_name.json");
        write_file(m_location_id_to_name, "ap_location_id_to_name.json");
    }

    ArchipelagoClient::IdToName ArchipelagoClient::parse_data_package(const std::unordered_map<std::string, ids::archipelago_id_t>& data) {
        ArchipelagoClient::IdToName parsed_data;
        for (auto& [name, id]: data) {
            parsed_data.insert_or_assign(id, name);
        }
        return parsed_data;
    }

    std::string ArchipelagoClient::get_item_name(const archipelago::messages::NetworkItem& item) {
        messages::NetworkPlayer player = m_players[item.player];
        std::string game = m_slots[player.slot].game;
        auto existing_it = m_item_id_to_name[game].find(item.item);
        if (existing_it != m_item_id_to_name[game].end()) {
            return m_item_id_to_name[game][item.item];
        } else {
            modloader::error("archipelago", std::format("Failed to convert item ID {} from game {} to its name.", item.item, game));
            return std::format("Unknown item name from {}.", game);
        };
    }

    std::string ArchipelagoClient::get_player_name(int player) { return m_players[player].alias; }

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
        location_data::Location location{ids::get_location_from_id(location_id)};
        core::api::uber_states::UberState(location.condition.state.group_int(), location.condition.state.state()).set(location.condition.value);
    }

    void ArchipelagoClient::give_item(archipelago::messages::NetworkItem const& net_item) {
        std::variant<ids::Location, ids::BooleanItem, ids::ResourceItem> item;
        item = ids::get_item(net_item.item);
        item |
            vx::match{
                [](const ids::BooleanItem& item) { core::api::uber_states::UberState{item.uber_group, item.uber_state}.set(1); },
                [](const ids::ResourceItem& item) {
                    switch (item.type) {
                        case ids::ResourceType::SpiritLight: {
                            const auto& spirit_light = core::api::game::player::spirit_light();
                            const auto& spirit_light_collected = core::api::uber_states::UberState(UberStateGroup::RandoStats, 3);

                            spirit_light.set(spirit_light.get() + item.value);
                            spirit_light_collected.set<int>(spirit_light_collected.get<int>() + item.value);
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
                },
                [net_item](const ids::Location& item) {
                    modloader::error("archipelago", std::format("AP ID {} corresponds to a location, expected an item.", net_item.item));
                },
            };
        core::message_controller().queue_central({
            .text = core::Property<std::string>(std::format("{} from {}.", get_item_name(net_item), get_player_name(net_item.player))),
            .show_box = true,
        });
    }

    void ArchipelagoClient::read_data_package(const std::string& file_name, auto& data) {
        nlohmann::json j;
        if (!load_json_file(file_name, j)) {
            // Something went wrong
            // Error message is printed to modloader log
            return;
        } else {
            nlohmann::from_json(j, data);
        }
    }

    void ArchipelagoClient::write_file(const nlohmann::json& data, const std::string& file_name) {
        // TODO verify that this works, and maybe save it somewhere else
        std::ofstream o(modloader::base_path() / file_name);
        o << std::setw(4) << data << std::endl;
        modloader::info("archipelago", std::format("Write {} data package.", file_name));
    }

    void ArchipelagoClient::ask_resync() {
        send_message(messages::Sync{});
        modloader::info("archipelago", "Sent Sync packet to AP server.");
    }

    void ArchipelagoClient::handle_server_message(messages::ap_server_message_t const& message) {
        message |
            vx::match{
                [this](const messages::Connected& message) {
                    m_players = message.players;
                    for (ids::archipelago_id_t location_id: message.checked_locations) {
                        collect_location(location_id);
                    }
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(std::format("Connected to Archipelago as {}.", m_slot_name)),
                        .show_box = true,
                    });
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(std::format("Current hint points: {}.", message.hint_points)),
                        .show_box = true,
                    });
                },
                [](const messages::ConnectionRefused& message) {
                    for (const std::string& error: message.errors) {
                        modloader::error("archipelago", std::format("Connection refused: {}.", error));
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(std::format("Connection to Archipelago refused: {}.", error)),
                            .show_box = true,
                        });
                    }
                },
                [this](const messages::RoomInfo& message) {
                    modloader::info(
                        "archipelago", std::format("AP server version: {}.{}.{}", message.version.major, message.version.minor, message.version.patch)
                    );
                    modloader::info(
                        "archipelago",
                        std::format(
                            "AP generator version: {}.{}.{}", message.generator_version.major, message.generator_version.minor, message.generator_version.patch
                        )
                    );
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(std::format("Hint cost: {}, Location points: {}.", message.hint_cost, message.location_check_points)
                        ),
                        .show_box = true,
                    });
                    auto seed_data = std::make_shared<randomizer::seed::Seed::Data>();
                    std::optional<std::string> ap_seed = seed_data->info.meta.archipelago_seed;
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
                        send_message(messages::GetDataPackage{outdated_games});
                        modloader::info("archipelago", "Sent GetDataPackage packet to AP server.");
                    }
                },
                [this](const messages::ReceivedItem& message) {
                    if (message.index == archipelago_save_data->last_item_index + 1) {
                        give_item(message.items[0]);
                        archipelago_save_data->last_item_index++;
                    } else if (message.index == 0) {
                        // AP server sent all the received items, only add the new ones
                        for (int index{archipelago_save_data->last_item_index}; index < message.items.size(); ++index) {
                            give_item(message.items[index]);
                            archipelago_save_data->last_item_index++;
                        }
                    } else {
                        ask_resync();
                    }
                },
                [this](const messages::LocationInfo& message) {
                    for (const messages::NetworkItem item: message.locations) {
                        m_cached_locations.erase(item.location);
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(std::format("{} sent to {}.", get_item_name(item), get_player_name(item.player))),
                            .show_box = true,
                        });
                    }
                },
                [this](const messages::RoomUpdate& message) {
                    m_players = message.players;
                    for (ids::archipelago_id_t location_id: message.checked_locations) {
                        collect_location(location_id);
                        m_cached_locations.erase(location_id); // Remove location from the cache if it existed in it.
                    }
                },
                [](const messages::PrintJSON& message) {
                    for (const nlohmann::json& text: message.data) {
                        core::message_controller().queue_central({
                            .text = core::Property<std::string>(text.get<std::string>()),
                            .show_box = true,
                        });
                        // TODO: Use type for different formatting
                    }
                },
                [](const messages::InvalidPacket& message) {
                    modloader::error("archipelago", std::format("{}: Invalid packet sent {}: {}.", message.type, message.original_cmd, message.text));
                },
                [this](const messages::DataPackage& message) { update_data_package(message.games); },
            };
    }
} // namespace randomizer::archipelago

// TODO list:
// Add the client in the main loop (do it when AP is in the flags ?)
// Send a StatusUpdate packet when ready/playing (cf p19)
// Formatting for PrintJSON
// See if stackable upgrades (e.g. health regen, extra djump) need a specific handling. If so, create 4th type of item ?
// Add death link support (see core/api/game/death_listener + add the tag in Connect packet)
