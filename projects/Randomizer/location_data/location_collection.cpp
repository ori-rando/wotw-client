#include <Randomizer/location_data/location_collection.h>

#include <utility>
#include <algorithm>

namespace randomizer::location_data {
    std::string unknown_area = "Unknown";
    std::unordered_map<GameArea, std::string> area_to_name_map{
        {GameArea::Inkwater,   "Inkwater Marsh"   },
        {GameArea::Hollow,     "Kwoloks Hollow"   },
        {GameArea::Glades,     "Wellspring Glades"},
        {GameArea::Wellspring, "The Wellspring"   },
        {GameArea::Luma,       "Luma Pools"       },
        {GameArea::Burrows,    "Midnight Burrows" },
        {GameArea::Reach,      "Baurs Reach"      },
        {GameArea::Woods,      "Silent Woods"     },
        {GameArea::Depths,     "Mouldwood Depths" },
        {GameArea::Wastes,     "Windswept Wastes" },
        {GameArea::Ruins,      "Windtorn Ruins"   },
        {GameArea::Willow,     "Willows End"      },
        {GameArea::Shop,       "Shop"             },
        {GameArea::Void,       "Void"             },
    };

    std::unordered_map<std::string, GameArea> name_to_area_map{
        {"Inkwater Marsh",    GameArea::Inkwater  },
        {"Kwoloks Hollow",    GameArea::Hollow    },
        {"Wellspring Glades", GameArea::Glades    },
        {"The Wellspring",    GameArea::Wellspring},
        {"Luma Pools",        GameArea::Luma      },
        {"Midnight Burrows",  GameArea::Burrows   },
        {"Baurs Reach",       GameArea::Reach     },
        {"Silent Woods",      GameArea::Woods     },
        {"Mouldwood Depths",  GameArea::Depths    },
        {"Windswept Wastes",  GameArea::Wastes    },
        {"Windtorn Ruins",    GameArea::Ruins     },
        {"Willows End",       GameArea::Willow    },
        {"Shop",              GameArea::Shop      },
        {"Void",              GameArea::Void      },
    };

    std::unordered_map<GameArea, std::string> area_to_short_name_map{
        {GameArea::Inkwater,   "Inkwater"  },
        {GameArea::Hollow,     "Hollow"    },
        {GameArea::Glades,     "Glades"    },
        {GameArea::Wellspring, "Wellspring"},
        {GameArea::Luma,       "Luma"      },
        {GameArea::Burrows,    "Burrows"   },
        {GameArea::Reach,      "Reach"     },
        {GameArea::Woods,      "Woods"     },
        {GameArea::Depths,     "Depths"    },
        {GameArea::Wastes,     "Wastes"    },
        {GameArea::Ruins,      "Ruins"     },
        {GameArea::Willow,     "Willow"    },
        {GameArea::Shop,       "Shop"      },
        {GameArea::Void,       "Void"      },
    };

    std::string_view area_to_name(const GameArea area) {
        const auto it = area_to_name_map.find(area);
        return it != area_to_name_map.end() ? it->second : unknown_area;
    }

    std::string_view area_to_short_name(const GameArea area) {
        const auto it = area_to_short_name_map.find(area);
        return it != area_to_short_name_map.end() ? it->second : unknown_area;
    }

    GameArea name_to_area(std::string const& name) {
        auto it = name_to_area_map.find(name);
        return it != name_to_area_map.end() ? it->second : GameArea::TOTAL;
    }

    void LocationCollection::read(std::filesystem::path path, location_data_parser parser) {
        for (auto i = 0; i < static_cast<int>(GameArea::TOTAL); ++i) {
            m_area_to_location_indexes[static_cast<GameArea>(i)] = {};
        }

        parser(std::move(path), [this](const Location& location) {
            m_locations.push_back(location);
        });

        for (auto i = 0; i < m_locations.size(); ++i) {
            auto const& location = m_locations.at(i);
            m_id_to_location_index[location.condition] = i;
            m_name_to_location_index[location.name] = i;
            m_area_to_location_indexes[location.area].push_back(i);
        }
    }

    GameArea LocationCollection::area(location_id const& id) const {
        const auto loc = location(id);
        return loc.has_value() ? loc.value().area : GameArea::Void;
    }

    GameArea LocationCollection::area(std::string const& name) const {
        const auto loc = location(name);
        return loc.has_value() ? loc.value().area : GameArea::Void;
    }

    std::optional<Location> LocationCollection::location(location_id const& id) const {
        const auto location_index = m_id_to_location_index.find(id);
        return location_index != m_id_to_location_index.end()
            ? std::optional(m_locations.at(location_index->second))
            : std::nullopt;
    }

    std::optional<Location> LocationCollection::location(std::string const& name) const {
        const auto location_index = m_name_to_location_index.find(name);
        return location_index != m_name_to_location_index.end()
            ? std::optional(m_locations.at(location_index->second))
            : std::nullopt;
    }

    std::vector<Location> LocationCollection::locations(const GameArea area) const {
        std::vector<Location> result;

        for (const int index: m_area_to_location_indexes.find(area)->second) {
            result.emplace_back(m_locations.at(index));
        }

        return result;
    }

    std::vector<Location> const& LocationCollection::locations() const {
        return m_locations;
    }
} // namespace randomizer::location_data
