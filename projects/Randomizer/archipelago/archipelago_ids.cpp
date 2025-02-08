#include <Modloader/app/types/UberStateCollection.h>
#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago_ids.h>
#include <Randomizer/randomizer.h>

using namespace app::classes;

namespace randomizer::archipelago::ids {
    /**
     * Since locations store only the first 8 bits of the uber group, we need to keep a
     * mapping of the Archipelago IDs to the actual locations.
     */

    std::unordered_map<archipelago_id_t, location_data::Location> location_map;

    [[maybe_unused]] auto on_location_collection_loading = event_bus().register_handler(
        RandomizerEvent::LocationCollectionLoaded,
        EventTiming::Before,
        [](auto, auto) { location_map.clear(); }
    );

    [[maybe_unused]] auto on_location_collection_loaded = event_bus().register_handler(
        RandomizerEvent::LocationCollectionLoaded,
        EventTiming::After,
        [](auto, auto) {
            for (const auto& location: location_collection().locations()) {
                const auto location_id = get_location_id(location);

                auto existing_it = location_map.find(location_id);
                if (existing_it != location_map.end()) {
                    modloader::warn(
                        "archipelago",
                        std::format(
                            "Location {} overlaps location {} when converted to an Archipelago ID and thus cannot be used in Archipelago",
                            location.name,
                            existing_it->second.name
                        )
                    );
                    continue;
                }

                location_map.emplace(location_id, location);
            }

            modloader::info("archipelago", "Built location map");
        }
    );

    archipelago_id_t get_boolean_item_id(int uber_group, int uber_state) {
        assert(uber_group <= 0b11111111'11111111);
        assert(uber_state <= 0b11111111'11111111);

        return BASE_ID + (static_cast<archipelago_id_t>(IdType::BooleanItem) << 32) + (uber_group << 16) + uber_state;
    }

    archipelago_id_t get_upgrade_item_id(int uber_group, int uber_state) {
        assert(uber_group <= 0b11111111'11111111);
        assert(uber_state <= 0b11111111'11111111);

        return BASE_ID + (static_cast<archipelago_id_t>(IdType::UpgradeItem) << 32) + (uber_group << 16) + uber_state;
    }

    archipelago_id_t get_resource_item_id(ResourceType type, int16_t value) {
        return BASE_ID + (static_cast<archipelago_id_t>(IdType::ResourceItem) << 32) + (static_cast<archipelago_id_t>(type) << 16) + value;
    }

    archipelago_id_t get_location_id(const location_data::Location& location) {
        assert(location.condition.value <= 0b11111111);
        assert(location.condition.state.state() <= 0b11111111'11111111);

        const archipelago_id_t group = static_cast<uint32_t>((location.condition.state.group_int() & 0b11111111) << 24);
        const archipelago_id_t state = static_cast<uint32_t>((location.condition.state.state() & 0b11111111'11111111) << 8);
        const auto value = static_cast<archipelago_id_t>(location.condition.value);

        return BASE_ID + (static_cast<archipelago_id_t>(IdType::Location) << 32) + group + state + value;
    }

    std::variant<Location, BooleanItem, ResourceItem, UpgradeItem> get_item(archipelago_id_t id) {
        switch (static_cast<IdType>((id >> 32) % 4)) {
            case IdType::Location: {
                return Location{
                    static_cast<uint8_t>(id >> 24),
                    static_cast<uint16_t>(id >> 8),
                    static_cast<uint8_t>(id),
                };
                case IdType::BooleanItem:
                    return BooleanItem{
                        static_cast<uint16_t>(id >> 16),
                        static_cast<uint16_t>(id),
                    };
                case IdType::ResourceItem:
                    return ResourceItem{
                        static_cast<ResourceType>(id >> 16),
                        static_cast<uint16_t>(id),
                    };
                case IdType::UpgradeItem:
                    return UpgradeItem{
                        static_cast<uint16_t>(id >> 16),
                        static_cast<uint16_t>(id),
                    };
                default: // Should never happen because of modulo 4, but it prevents a warning from the compiler
                    throw std::runtime_error(std::format("Could not process archipelago id {}", id));
            }
        }
    }
    location_data::Location get_location_from_id(archipelago_id_t location_id) { return location_map[location_id]; }
} // namespace randomizer::archipelago::ids
