#pragma once

#include "seed_source.h"


#include <Core/api/uber_states/uber_state_condition.h>
#include <Core/enums/game_areas.h>
#include <Core/property.h>

#include <Randomizer/location_data/location_collection.h>
#include <Randomizer/seed/item_data.h>
#include <Randomizer/seed/relics.h>

#include <Core/save_meta/save_meta.h>
#include <Modloader/app/structs/GameController_GameDifficultyModes__Enum.h>
#include <semver.hpp>
#include <nlohmann/json.hpp>
#include <unordered_map>

template<typename T>
struct nlohmann::adl_serializer<std::optional<T>> {
    static void from_json(const json& j, std::optional<T>& opt) {
        if (j.is_null()) {
            opt = std::nullopt;
        } else {
            opt = j.get<T>();
        }
    }
    static void to_json(json& json, std::optional<T> t) {
        if (t) {
            json = *t;
        } else {
            json = nullptr;
        }
    }
};

namespace randomizer::seed {
    class Seed {
    public:
        using inner_location_entry = core::api::uber_states::UberStateCondition;
        using inner_location_entries = std::unordered_map<inner_location_entry, ItemData>;
        using location_entry = core::api::uber_states::UberState;

        enum class GameDifficultySetting {
            Allow,
            Warn,
            Deny,
        };

        struct GameDifficultySettings {
            GameDifficultySetting easy = GameDifficultySetting::Warn;
            GameDifficultySetting normal = GameDifficultySetting::Warn;
            GameDifficultySetting hard = GameDifficultySetting::Warn;

            GameDifficultySetting get_for_game_difficulty(app::GameController_GameDifficultyModes__Enum difficulty) const {
                switch (difficulty) {
                    case app::GameController_GameDifficultyModes__Enum::Easy:
                        return easy;
                    case app::GameController_GameDifficultyModes__Enum::Normal:
                        return normal;
                    case app::GameController_GameDifficultyModes__Enum::Hard:
                        return hard;
                }

                throw std::exception("Invalid difficulty given");
            }

            std::optional<app::GameController_GameDifficultyModes__Enum> get_lowest_allowed_difficulty() const {
                if (easy == GameDifficultySetting::Allow) {
                    return app::GameController_GameDifficultyModes__Enum::Easy;
                }

                if (normal == GameDifficultySetting::Allow) {
                    return app::GameController_GameDifficultyModes__Enum::Normal;
                }

                if (hard == GameDifficultySetting::Allow) {
                    return app::GameController_GameDifficultyModes__Enum::Hard;
                }

                return std::nullopt;
            }
        };

        struct SeedMetaData {
            semver::version version = semver::version(0, 0, 0);
            std::vector<std::string> flags;
            app::Vector3 start_position = {-798.797058f, -4310.119141f, 0.f};
            std::string slug;
            int world_index = 0;
            bool race_mode = false;
            GameDifficultySettings game_difficulties;
            std::optional<std::string> archipelago_slot_name = std::nullopt;
        };

        struct SeedInfo {
            SeedMetaData meta;

            std::string parser_error;

            int total_pickups = 0;
            std::unordered_map<GameArea, int> pickup_count_by_area;

            std::string content;
            std::string areas;
            std::string locations;
            std::string states;
        };

        struct Timer {
            core::api::uber_states::UberState toggle;
            core::api::uber_states::UberState value;
        };

        struct Data {
            SeedInfo info;
            Relics relics;
            std::unordered_map<location_entry, inner_location_entries> locations;
            std::unordered_map<int, ItemData> procedures;
            std::vector<Timer> timers;
        };

        using seed_parser = bool (*)(const std::string_view content, location_data::LocationCollection const& location_data, std::shared_ptr<Data> data);

        Seed(location_data::LocationCollection const& location_data);

        void read(const std::string& seed_content, const seed_parser parser, const bool show_message = true);
        void show_flags_message() const;
        void reload(const bool show_message = true);
        void clear() const;

        MapIcon icon(const inner_location_entry& location) const;
        std::string text(const inner_location_entry& location) const;
        void grant(location_entry location, double previous_value);
        void procedure_call(int id);
        std::optional<ItemData> procedure_data(int id);

        SeedInfo const& info() const { return m_data->info; }
        int total_pickups() const { return m_data->info.total_pickups; }

        Relics const& relics() const { return m_data->relics; }
        bool finished_goals() const;

        void prevent_grants(const std::function<bool()>& callback) { m_prevent_grant_callbacks.push_back(callback); }

        void process_timers(float delta_time) const;

    private:
        location_data::LocationCollection const& m_location_data;
        seed_parser m_last_parser = nullptr;
        std::string m_seed_content;
        std::shared_ptr<Data> m_data = std::make_shared<Data>();
        std::vector<std::function<bool()>> m_prevent_grant_callbacks;
    };


    class SaveSlotSeedMetaData final : public core::save_meta::JsonSaveMetaSerializable {
    public:
        /** The seed source string that was used when this save file was created. (see parse_source_string) */
        std::string seed_source_string;

        /** The Seed file content. */
        std::string seed_content;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
            SaveSlotSeedMetaData,
            seed_source_string,
            seed_content
        );

        nlohmann::json json_serialize() override;
        void json_deserialize(nlohmann::json& j) override;

        std::shared_ptr<SeedSource> get_source() const;
    };
} // namespace randomizer::seed
