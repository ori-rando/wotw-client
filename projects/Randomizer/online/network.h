#pragma once

#include <string_view>
#include <utility>
#include <vector>

#include <ixwebsocket/IXWebSocket.h>
#include <ixwebsocket/IXWebSocketMessage.h>

#include <Common/event_bus.h>
#include <packets.pb.h>

#include <Modloader/udp_socket.h>

namespace randomizer::online {
    class NetworkClient {
    public:
        enum class State {
            Connected,
            Authenticating,
            Reconnecting,
            Closed,
        };

        enum class StatusType {
            WebsocketConnected,
            WebsocketClosedUnexpected,
            WebsocketClosed,
            WebsocketError,
            WebsocketSendError,

            UdpClosed,
            UdpError,
        };

        struct Status {
            StatusType type;
            std::string info;
        };

        using handler_callback = std::function<void(Network::Packet_PacketID, std::string)>;
        using status_callback = std::function<void(Status const&)>;

        NetworkClient();
        ~NetworkClient();

        void websocket_connect(std::string_view url);
        bool websocket_want_connection() const { return m_reconnect_websocket; }
        bool websocket_connected() const;
        bool websocket_send(Network::Packet const& packet);

        template <typename T>
        bool websocket_send(Network::Packet_PacketID id, T const& data) {
            Network::Packet packet;
            packet.set_id(id);
            packet.set_packet(data.SerializeAsString());
            return websocket_send(packet);
        }

        void udp_open(std::string_view server, int port);
        bool udp_is_open() const;
        void udp_send(Network::Packet const& packet);

        template <typename T>
        void udp_send(Network::Packet_PacketID id, T const& data) {
            Network::Packet packet;
            packet.set_id(id);
            packet.set_packet(data.SerializeAsString());
            udp_send(packet);
        }

        void disconnect();
        bool wants_connection() const { return m_reconnect_websocket; }

        void update();
        void register_handler(Network::Packet_PacketID type, handler_callback const& handler);

        template <typename T>
        void register_handler(Network::Packet_PacketID packet, std::function<void(std::shared_ptr<T> const&)> handler) {
            register_handler(packet, [handler](Network::Packet_PacketID, std::string data) {
                std::shared_ptr<T> message = std::make_shared<T>();
                message->ParseFromString(data);
                handler(message);
            });
        }

        void set_status_listener(status_callback callback) {
            m_status_listener = std::move(callback);
        }

        common::EventBus<State>& event_bus() { return m_event_bus; }

    private:
        void websocket_handle_message(ix::WebSocketMessagePtr const& msg);
        void udp_handle_message(std::vector<char> const& msg);
        void udp_handle_error(int error);
        void ping_udp();

        std::mutex m_packet_mutex;
        std::vector<Network::Packet> m_packets;
        std::unordered_map<Network::Packet_PacketID, std::vector<handler_callback>> m_callbacks;
        ix::WebSocket m_websocket;
        modloader::UDPSocket m_udp_socket;
        status_callback m_status_listener;
        common::EventBus<State> m_event_bus;

        bool m_reconnect_websocket;
        bool m_reopen_udp;

        int m_udp_id;
        std::vector<char> m_udp_key;
    };

    std::string get_jwt();
} // namespace randomizer::online
