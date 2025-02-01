#pragma once

#include <Modloader/modloader.h>
#include <IXWebSocket.h>
#include <filesystem>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>
#include <unordered_set>


#include <Randomizer/archipelago/archipelago_ids.h>
#include <Randomizer/archipelago/archipelago_protocol.h>

namespace randomizer::archipelago {
    void apply_states();
    void apply_resources();

    class ArchipelagoClient {
    public:
        ArchipelagoClient();
        void connect(std::string_view url, std::string_view slot_name, std::string_view password);
        void disconnect();
        bool is_connected() const;
        void location_handler(auto& params);
        void game_finished_handler();
        void ask_resync();
        void event_uber_states();
        void event_resource();

    private:
        template<typename Jsonable>
        void send_message(const Jsonable& message) {
            const nlohmann::json json(message);
            m_websocket.send("[" + json.dump() + "]");  // Not very good style, maybe improve it
        }

        using IdToName = std::unordered_map<ids::archipelago_id_t, std::string>;

        void give_item(archipelago::messages::NetworkItem const& net_item);
        void collect_location(ids::archipelago_id_t location_id);
        void on_websocket_message(ix::WebSocketMessagePtr const& msg);
        void handle_server_message(messages::ap_server_message_t const& message);
        void update_data_package(const std::unordered_map<std::string, messages::GameData>& new_data);
        IdToName parse_data_package(const std::unordered_map<std::string, ids::archipelago_id_t>& data);
        std::string get_item_name(const archipelago::messages::NetworkItem& item, bool is_local);
        std::string get_player_name(int player);
        std::string get_location_name(ids::archipelago_id_t id, const std::string& game);
        void write_file(const nlohmann::json& data, const std::string& file_name);
        void read_data_package(const std::string& file_name, auto& data);

        bool m_should_connect = false;
        ix::WebSocket m_websocket;
        std::string m_slot_name; // aka player name
        std::string m_password;
        std::unordered_set<ids::archipelago_id_t> m_cached_locations;
        std::unordered_map<std::string, archipelago::messages::NetworkSlot> m_slots;
        std::unordered_map<std::string, messages::GameData> m_data_package_cache;
        std::filesystem::path m_data_package_path = "./archipelago/";
        std::unordered_map<int, messages::NetworkPlayer> m_player_map;
        std::vector<core::api::uber_states::UberStateCondition> m_state_cache;
        std::vector<ids::ResourceItem> m_resource_cache;
        std::unordered_map<std::string, IdToName> m_item_id_to_name;
        std::unordered_map<std::string, IdToName> m_location_id_to_name;
        std::mutex m_packet_mutex;
        std::vector<nlohmann::basic_json<>> m_packets;
    };
} // namespace randomizer::archipelago
