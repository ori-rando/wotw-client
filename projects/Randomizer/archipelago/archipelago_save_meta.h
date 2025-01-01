#pragma once

#include <Core/save_meta/save_meta.h>
#include <Randomizer/archipelago/archipelago_ids.h>

namespace randomizer::archipelago {
    class ArchipelagoSaveData final : public core::save_meta::JsonSaveMetaSerializable {
    public:
        int last_item_index{0};

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(ArchipelagoSaveData, last_item_index);

        nlohmann::json json_serialize() override;
        void json_deserialize(nlohmann::json& j) override;
    };
}; // namespace randomizer::archipelago
