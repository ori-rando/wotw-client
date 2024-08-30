#include <Randomizer/archipelago/archipelago_save_meta.h>

namespace randomizer::archipelago {
    nlohmann::json ArchipelagoSaveData::json_serialize() {
        nlohmann::json j = *this;
        return j;
    }

    void ArchipelagoSaveData::json_deserialize(nlohmann::json& j) {
        j.get_to(*this);
    }
};
