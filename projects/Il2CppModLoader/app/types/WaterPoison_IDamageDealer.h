#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace WaterPoison_IDamageDealer {
        extern IL2CPP_MODLOADER_DLLEXPORT app::WaterPoison_IDamageDealer__Class** type_info;
        inline app::WaterPoison_IDamageDealer__Class* get_class() {
            return il2cpp::get_nested_class<app::WaterPoison_IDamageDealer__Class>(type_info, "", "WaterPoison", "IDamageDealer");
        }
        inline app::WaterPoison_IDamageDealer__Array* create_array(int size) {
            return il2cpp::array_new<app::WaterPoison_IDamageDealer__Array>(get_class(), size);
        }
        inline app::WaterPoison_IDamageDealer__Array* create_array(const std::vector<app::WaterPoison_IDamageDealer*>& items) {
            return il2cpp::array_new<app::WaterPoison_IDamageDealer__Array>(get_class(), items);
        }
    } // namespace WaterPoison_IDamageDealer
} // namespace app::classes::types
