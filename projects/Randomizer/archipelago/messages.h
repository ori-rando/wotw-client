#pragma once

#include <nlohmann/json.hpp>

namespace randomizer::archipelago::messages {
  struct NetworkVersion {
    int major;
    int minor;
    int patch;
  };

  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(NetworkVersion, major, minor, patch);

  struct Connect {
    std::string password;
    std::string game;
    std::string name;
    std::string uuid;
    NetworkVersion version;
    int items_handling;
    std::vector<std::string> tags;
    bool slot_data;
  };

  NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(Connect, password, game, name, uuid, version, items_handling, tags, slot_data);
}
