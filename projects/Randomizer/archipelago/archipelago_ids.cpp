#include <Randomizer/archipelago/archipelago_ids.h>

namespace randomizer::archipelago::ids {
    archipelago_id_t get_boolean_item_id(int uber_group, int uber_state) {
        assert(uber_group <= 0b11111111'11111111);
        assert(uber_state <= 0b11111111'11111111);

        return BASE_ID
            + (static_cast<archipelago_id_t>(IdType::BooleanItem) << 32)
            + (uber_group << 16)
            + uber_state;
    }

    archipelago_id_t get_resource_item_id(ResourceType type, int16_t value) {
        return BASE_ID
            + (static_cast<archipelago_id_t>(IdType::ResourceItem) << 32)
            + (static_cast<archipelago_id_t>(type) << 16)
            + value;
    }

    archipelago_id_t get_location_id(const location_data::Location& location) {
        assert(location.condition.value <= 0b11111111);
        assert(location.condition.state.state() <= 0b11111111'11111111);

        const archipelago_id_t group = (location.condition.state.group_int() & 0b11111111) << 24;
        const archipelago_id_t state = (location.condition.state.state() & 0b11111111'11111111) << 8;
        const archipelago_id_t value = static_cast<archipelago_id_t>(location.condition.value);

        return BASE_ID + (static_cast<archipelago_id_t>(IdType::Location) << 32) + group + state + value;
    }

    std::variant<Location, BooleanItem, ResourceItem> get_item(archipelago_id_t id) {
        const auto id_type = static_cast<IdType>(id >> 32);

        switch (id_type) {
            case IdType::Location:
                return Location {
                    static_cast<int8_t>(id >> 24),
                    static_cast<int16_t>(id >> 8),
                    static_cast<int8_t>(id),
                };
            case IdType::BooleanItem:
                return BooleanItem {
                    static_cast<int16_t>(id >> 16),
                    static_cast<int16_t>(id),
                };
            case IdType::ResourceItem:
                return ResourceItem {
                    static_cast<ResourceType>(id >> 16),
                    static_cast<int16_t>(id),
                };
        }

        throw std::runtime_error(std::format("Could not process archipelago id {}", id));
    }
} // namespace randomizer::archipelago::ids
