#pragma once

#include <nlohmann/json.hpp>
#include <openssl/bio.h>
#include <unordered_map>
#include <variant>

namespace randomizer::archipelago::messages {
    struct NetworkVersion {
        int major;
        int minor;
        int patch;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NetworkVersion, major, minor, patch);
    };

    struct Connect {
        std::string password;
        std::string game;
        std::string name;
        std::string uuid;
        NetworkVersion version;
        int items_handling;
        std::vector<std::string> tags;
        bool slot_data;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Connect, password, game, name, uuid, version, items_handling, tags, slot_data);
    };

    enum SlotType {
        Spectator = 0b00,
        Player = 0b01,
        Group = 0b10,
    };

    struct NetworkSlot {
        std::string name;
        std::string game;
        SlotType type;
        std::vector<int> group_members;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NetworkSlot, name, game, type, group_members);
    };

    struct NetworkPlayer {
        int team;
        int slot;
        std::string alias;
        std::string name;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NetworkPlayer, team, slot, alias, name);
    };

    struct Connected {
        int team;
        int slot;
        std::vector<NetworkPlayer> players;
        std::vector<int> missing_locations;
        std::vector<int> checked_locations;
        // slot_data
        std::unordered_map<std::string, NetworkSlot> slot_info;
        int hint_points;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Connected, team, slot, players, missing_locations, checked_locations, slot_info, hint_points);
    };

    struct ConnectionRefused {
        std::vector<std::string> errors;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ConnectionRefused, errors);
    };

    struct RoomInfo {
        NetworkVersion version;
        NetworkVersion generator_version;
        std::vector<std::string> tags;
        bool password;
		// permissions
        int hint_cost;
        int location_check_points;
        std::vector<std::string> games;
        std::unordered_map<std::string, std::string> datapackage_checksums;
        std::string seed_name;
        float time;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(RoomInfo, version, generator_version, tags, password, hint_cost, location_check_points, games, datapackage_checksums, seed_name, time);
    };

    struct NetworkItem {
        int item;
        int location;
        int player;
        int flags;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NetworkItem, item, location, player, flags);
    };

    struct ReceivedItem {
        int index;
        std::vector<NetworkItem> items;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ReceivedItem, index, items);
    };

    using ap_server_message_t = std::variant<
        Connected,
        ConnectionRefused,
        RoomInfo,
        ReceivedItem
    >;

    std::optional<ap_server_message_t> parse_server_message(const nlohmann::json& message);
} // namespace randomizer::archipelago::messages
