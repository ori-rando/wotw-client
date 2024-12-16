#pragma once

#include <IXWebSocket.h>
#include <nlohmann/json.hpp>
#include <string>

#include "archipelago_protocol.h"

namespace randomizer::archipelago {
    // TODO:
    // - Add save meta slot for AP
    // - Keep track of received items from AP

    class ArchipelagoClient {
    public:
        ArchipelagoClient();
        void connect(std::string_view url, std::string_view slot_name, std::string_view password);
        void disconnect();
        bool is_connected() const;

    private:
        template<typename Jsonable>
        void send_message(const Jsonable& message) {
            const nlohmann::json json(message);
            m_websocket.send(json.dump());
        }

        void on_websocket_message(ix::WebSocketMessagePtr const& msg);
        void handle_server_message(messages::ap_server_message_t const& message);

        bool m_connected = false;
        bool m_should_connect = false;
        ix::WebSocket m_websocket;
        std::string m_slot_name;  // aka player name
        std::string m_password;
        int m_last_item_index = 0;
    };
} // namespace randomizer::archipelago
