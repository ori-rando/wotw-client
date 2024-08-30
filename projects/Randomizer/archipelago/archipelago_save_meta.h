#pragma once

#include <Core/save_meta/save_meta.h>
#include <Randomizer/archipelago/archipelago_ids.h>

namespace randomizer::archipelago {
    class ArchipelagoSaveData final : public core::save_meta::JsonSaveMetaSerializable {
    public:
        std::vector<ids::archipelago_id_t> received_items;

        NLOHMANN_DEFINE_TYPE_INTRUSIVE_WITH_DEFAULT(
            ArchipelagoSaveData,
            received_items
        );

        nlohmann::json json_serialize() override;
        void json_deserialize(nlohmann::json& j) override;
    };
};
