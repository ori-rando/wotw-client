#pragma once

#include <Randomizer/archipelago/archipelago_ids.h>
#include <nlohmann/json.hpp>
#include <openssl/bio.h>
#include <unordered_map>
#include <unordered_set>
#include <variant>


namespace randomizer::archipelago::messages {
    struct NetworkVersion {
        int major;
        int minor;
        int build;
        std::string version_class;

        // The macro cannot be used, because an argument is called class.
        template<typename BasicJsonType>
        friend void to_json(BasicJsonType& nlohmann_json_j, const NetworkVersion& nlohmann_json_t)
        {
            nlohmann_json_j["major"] = nlohmann_json_t.major;
            nlohmann_json_j["minor"] = nlohmann_json_t.minor;
            nlohmann_json_j["build"] = nlohmann_json_t.build;
            nlohmann_json_j["class"] = nlohmann_json_t.version_class;
        }

        template<typename BasicJsonType>
        friend void from_json(const BasicJsonType& nlohmann_json_j, NetworkVersion& nlohmann_json_t)
        {
            nlohmann_json_t.major = nlohmann_json_j.at("major");
            nlohmann_json_t.minor = nlohmann_json_j.at("minor");
            nlohmann_json_t.build = nlohmann_json_j.at("build");
            nlohmann_json_t.version_class = nlohmann_json_j.at("class");
        }
    };

    enum SlotType {
        Spectator = 0b00,
        Player = 0b01,
        Group = 0b10,
    };

    enum ClientStatus {
        ClientUnknown = 0,
        ClientConnected = 5,
        ClientReady = 10,
        ClientPlaying = 20,
        ClientGoal = 30,
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

    struct NetworkItem {
        ids::archipelago_id_t item;
        ids::archipelago_id_t location;
        int player;
        int flags;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(NetworkItem, item, location, player, flags);
    };

    struct GameData {
        std::unordered_map<std::string, ids::archipelago_id_t> item_name_to_id;
        std::unordered_map<std::string, ids::archipelago_id_t> location_name_to_id;
        std::string checksum;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameData, item_name_to_id, location_name_to_id, checksum);
    };

    struct DataPack {
        std::unordered_map<std::string, GameData> games;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataPack, games);
    };

    struct JSONMessage {
        std::string text;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(JSONMessage, text);
    };

    // Messages client -> server
    struct Connect {
        std::string password;
        std::string game;
        std::string name;
        std::string uuid;
        NetworkVersion version;
        int items_handling;
        std::vector<std::string> tags;
        bool slot_data;
        std::string cmd = "Connect";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Connect, cmd, password, game, name, uuid, version, items_handling, tags, slot_data);
    };

    struct LocationChecks {
        std::unordered_set<ids::archipelago_id_t> locations;
        std::string cmd = "LocationChecks";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LocationChecks, cmd, locations);
    };

    struct StatusUpdate {
        int status;
        std::string cmd = "StatusUpdate";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(StatusUpdate, cmd, status);
    };

    struct Sync {
        std::string cmd = "Sync";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(Sync, cmd);
    };

    struct GetDataPackage {
        std::vector<std::string> games;
        std::string cmd = "GetDataPackage";

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(GetDataPackage, cmd, games);
    };

    // Messages server -> client
    struct Connected {
        int team;
        int slot;
        std::vector<NetworkPlayer> players;
        std::vector<ids::archipelago_id_t> missing_locations;
        std::vector<ids::archipelago_id_t> checked_locations;
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

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(
            RoomInfo,
            version,
            generator_version,
            tags,
            password,
            hint_cost,
            location_check_points,
            games,
            datapackage_checksums,
            seed_name,
            time
        );
    };

    struct ReceivedItems {
        int index;
        std::vector<NetworkItem> items;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ReceivedItems, index, items);
    };

    struct LocationInfo {
        std::vector<NetworkItem> locations;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LocationInfo, locations);
    };

    struct RoomUpdate {
        std::vector<NetworkPlayer> players;
        std::vector<ids::archipelago_id_t> checked_locations;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(RoomUpdate, players, checked_locations);
    };

    struct PrintJSON {
        std::vector<JSONMessage> data;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(PrintJSON, data);
    };

    struct InvalidPacket {
        std::string type;
        std::string original_cmd;  // TODO can be null, which causes the parsing to fail
        std::string text;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(InvalidPacket, type, original_cmd, text);
    };

    struct DataPackage {
        DataPack data;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataPackage, data);
    };

    using ap_server_message_t = std::
        variant<Connected, ConnectionRefused, RoomInfo, ReceivedItems, LocationInfo, RoomUpdate, PrintJSON, InvalidPacket, DataPackage>;

    std::optional<ap_server_message_t> parse_server_message(const nlohmann::json& message);
} // namespace randomizer::archipelago::messages
