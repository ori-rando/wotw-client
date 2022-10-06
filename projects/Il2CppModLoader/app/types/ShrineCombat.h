#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace ShrineCombat {
        extern IL2CPP_MODLOADER_DLLEXPORT app::ShrineCombat__Class** type_info;
        inline app::ShrineCombat__Class* get_class() {
            return il2cpp::get_class<app::ShrineCombat__Class>(type_info, "", "ShrineCombat");
        }
        inline app::ShrineCombat* create() {
            return il2cpp::create_object<app::ShrineCombat>(get_class());
        }
        inline app::ShrineCombat__Array* create_array(int size) {
            return il2cpp::array_new<app::ShrineCombat__Array>(get_class(), size);
        }
        inline app::ShrineCombat__Array* create_array(const std::vector<app::ShrineCombat*>& items) {
            return il2cpp::array_new<app::ShrineCombat__Array>(get_class(), items);
        }
    } // namespace ShrineCombat
} // namespace app::classes::types
