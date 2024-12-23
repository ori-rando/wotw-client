#include <Core/events/task.h>
#include <Common/vx.h>
#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago.h>
#include <Randomizer/archipelago/archipelago_protocol.h>
#include <Randomizer/archipelago/archipelago_save_meta.h>
#include "Core/api/uber_states/uber_state.h"
#include "Core/api/game/player.cpp"
#include "Core/api/uber_states/uber_state_handlers.h"
#include "Core/core.h"
#include "Core/enums/game_areas.h"
#include "Randomizer/archipelago/archipelago_ids.h"
#include "Randomizer/location_data/location.h"

#define UUID_SYSTEM_GENERATOR
#include <uuid.h>

namespace randomizer::archipelago {
    auto archipelago_save_data = std::make_shared<ArchipelagoSaveData>();

    [[maybe_unused]]
    auto on_game_ready = modloader::event_bus().register_handler(ModloaderEvent::GameReady, [](auto) {
        core::save_meta::register_slot(SaveMetaSlot::ArchipelagoData, SaveMetaSlotPersistence::None, archipelago_save_data);
    });

    ArchipelagoClient::ArchipelagoClient() {
        m_websocket.setOnMessageCallback([this](const auto& msg) { on_websocket_message(msg); });

        [[maybe_unused]]
        auto uber_state_bus_handle = core::api::uber_states::single_notification_bus().register_handler(
            core::api::uber_states::UberState(34543, 11226),
            [this](const core::api::uber_states::UberStateCallbackParams& params, auto) {
                if (params.state.get<bool>()) {
                    // Game completion
                    send_message(messages::StatusUpdate{30});
                }
            }
        );

        [[maybe_unused]]
        auto on_uber_state_changed = core::api::uber_states::notification_bus().register_handler([this](auto params) {
            auto got = randomizer::archipelago::locations_map.find (core::api::uber_states::UberState(params.state));

            if ( got != randomizer::archipelago::locations_map.end() ) {
                randomizer::location_data::Location location{
                    "AP",
                    GameArea::Void,
                    randomizer::location_data::LocationType::Unknown,
                    core::api::uber_states::UberStateCondition(params.state)
                };
                ids::archipelago_id_t location_id {ids::get_location_id(location)};
                m_cached_locations.push_back(location_id);  // Stores the locations that are checked, but not validated by the server
                send_message(messages::LocationChecks{std::vector<ids::archipelago_id_t>{m_cached_locations}});
            };
        });
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

    bool ArchipelagoClient::is_connected() const {
        return m_websocket.getReadyState() == ix::ReadyState::Open;
    }

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
                    {},
                    false,
                });
                break;
            }
            case ix::WebSocketMessageType::Close: {
                auto closed_reason = std::format("websocket closed '{}': {}", msg->closeInfo.code, msg->closeInfo.reason.c_str());
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

    void ArchipelagoClient::give_item(archipelago::messages::NetworkItem const& net_item) {
        std::variant<ids::Location, ids::BooleanItem, ids::ResourceItem> item;
        item = ids::get_item(net_item.item);
        item | vx::match {
            [](const ids::BooleanItem& item) {
                core::api::uber_states::UberState{item.uber_group, item.uber_state}.set(1);
            },
            [](const ids::ResourceItem& item) {
                switch (item.type) {
                    case ids::ResourceType::SpiritLight: {
                        core::api::game::player::set_spirit_light(core::api::game::player::get_spirit_light() + item.value);
                        break;
                    }
                    case ids::ResourceType::GorlekOre: {
                        core::api::game::player::set_ore(core::api::game::player::get_ore() + 1);
                        break;
                    }
                    case ids::ResourceType::Keystone: {
                        core::api::game::player::set_keystones(core::api::game::player::get_keystones() + 1);
                        break;
                    }
                    case ids::ResourceType::ShardSlot: {
                        core::api::game::player::set_shard_slots(core::api::game::player::get_shard_slots() + 1);
                        break;
                    }
                    case ids::ResourceType::HealthFragment: {
                        core::api::game::player::set_max_health(core::api::game::player::get_max_health() + 5);
                        break;
                    }
                    case ids::ResourceType::EnergyFragment: {
                        core::api::game::player::set_max_energy(core::api::game::player::get_max_energy() + float(0.5));
                        break;
                    }
                }
            },
            [net_item](const ids::Location& item) {
                modloader::error("archipelago", std::format("AP ID {} corresponds to a location, expected an item.", net_item.item));
            },
        };
        // TODO: inform the player
        core::message_controller().queue_central({
            // TODO link item id to name
            .text = core::Property<std::string>(std::format("{} from {}", net_item.item, m_players[net_item.player].alias)),
            .show_box = true,
        });
    }

    void ArchipelagoClient::handle_server_message(messages::ap_server_message_t const& message) {
        message | vx::match {
            [this](const messages::Connected& message) {
                m_players = message.players;
                for (int index{ 0 }; index < message.checked_locations.size(); ++index) {
                    // TODO: check the locations in the game
                }
            },
            [](const messages::ConnectionRefused& message) {
                for (int index{ 0 }; index < message.errors.size(); ++index) {
                    modloader::error("archipelago", std::format("Connection refused: {}", message.errors[index]));
                }
            },
            [](const messages::RoomInfo& message) {
                core::message_controller().queue_central({
                    .text = core::Property<std::string>(std::format("Hint cost: {}, Location points: {}", message.hint_cost, message.location_check_points)),
                    .show_box = true,
                });
                // if (message.seed_name != seed) {
                //     modloader::warn("archipelago", std::format("Seed from RoomInfo {} does not match the file seed {}", message.seed_name, seed));
                // }
                // TODO: check if seed name corresponds to the one in the .wotwr file
                // TODO: checksum for datapackages
            },
            [this](const messages::ReceivedItem& message) {
                if (message.index == m_last_item_index + 1) {
                    give_item(message.items[0]);
                    m_last_item_index++;
                }
                else if (message.index == 0) {
                    // AP server sent all the received items, only add the new ones
                    for (int index{ m_last_item_index }; index < message.items.size(); ++index) {
                        give_item(message.items[index]);
                        m_last_item_index++;
                    }
                }
                else {
                    // Ask the AP server to resync the items
                    send_message(messages::Sync{"Sync"});  // TODO fix the packet
                }
            },
            [this](const messages::LocationInfo& message) {
                for (int index{ 0 }; index < message.locations.size(); ++index) {
                    // TODO Link id to name
                    // TODO: delete location from the cache
                    // (message.locations[index].location);
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(std::format("{}'s {}", m_players[message.locations[index].player].alias, message.locations[index].item)),
                        .show_box = true,
                    });
                }
            },
            [this](const messages::RoomUpdate& message) {
                m_players = message.players;
                // TODO: Update checked locations (same way as in Connected)
                // TODO: check if new locations are already in cache; in that case remove them ?
            },
            [](const messages::PrintJSON& message) {
                for (int index{ 0 }; index < message.data.size(); ++index) {
                    core::message_controller().queue_central({
                        .text = core::Property<std::string>(message.data[index].get<std::string>()),
                        .show_box = true,
                    });
                // TODO: Use type for different formatting
                }
            },
            [](const messages::InvalidPacket& message) {
                modloader::error("archipelago", std::format("{}: Invalid packet sent {}: {}", message.type, message.original_cmd, message.text));
            },
        };
    }
} // namespace randomizer::archipelago

// Priority TODO list:
// Fix the Sync message
// Retrieve the credentials from the .wotwr file

// TODO list (not necessary for 1st implementation):
// Add the checked locations to the cache
// Send a StatusUpdate packet when ready/playing (cf p19)
// Check the locations from Connected and RoomUpdate for better coop + new save files
// Formatting for PrintJSON
// Datapackage checksum + save it somewhere
// Check seed name
// Release items when finished
