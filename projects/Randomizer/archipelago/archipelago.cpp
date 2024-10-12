#include <Core/events/task.h>
#include <Common/vx.h>
#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago.h>
#include <Randomizer/archipelago/archipelago_protocol.h>
#include <Randomizer/archipelago/archipelago_save_meta.h>

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

    void ArchipelagoClient::handle_server_message(messages::ap_server_message_t const& message) {
        message | vx::match {
            [](const messages::Connected& message) {
                // TODO
            },
            [](const messages::ConnectionRefused& message) {
                // TODO
            },
            [](const messages::RoomInfo& message) {
                // TODO
            },
            [](const messages::ReceivedItem& message) {
                // TODO
            },
        };
    }
} // namespace randomizer::archipelago
