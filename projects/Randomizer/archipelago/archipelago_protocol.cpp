#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago_protocol.h>
#include <nlohmann/json.hpp>

namespace randomizer::archipelago::messages {
    std::optional<ap_server_message_t> parse_server_message(const nlohmann::json& message) {
        const auto command = message.at("cmd").get<std::string>();

        if (command == "Connected") {
            return message.get<Connected>();
        }

        if (command == "ConnectionRefused") {
            return message.get<ConnectionRefused>();
        }

        if (command == "RoomInfo") {
            return message.get<RoomInfo>();
        }

        if (command == "ReceivedItem") {
            return message.get<ReceivedItem>();
        }

        if (command == "LocationInfo") {
        return message.get<LocationInfo>();
        }

        if (command == "RoomUpdate") {
        return message.get<RoomUpdate>();
        }

        if (command == "PrintJSON") {
        return message.get<PrintJSON>();
        }

        if (command == "InvalidPacket") {
        return message.get<InvalidPacket>();
        }

        modloader::warn("archipelago", std::format("Failed to parse server message: Unknown command {}", command));

        return std::nullopt;
    }
} // namespace randomizer::archipelago::messages
