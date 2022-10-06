#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace ModifierWrapper {
        extern IL2CPP_MODLOADER_DLLEXPORT app::ModifierWrapper__Class** type_info;
        inline app::ModifierWrapper__Class* get_class() {
            return il2cpp::get_class<app::ModifierWrapper__Class>(type_info, "Moon.ArtOptimization", "ModifierWrapper");
        }
        inline app::ModifierWrapper* create() {
            return il2cpp::create_object<app::ModifierWrapper>(get_class());
        }
        inline app::ModifierWrapper__Array* create_array(int size) {
            return il2cpp::array_new<app::ModifierWrapper__Array>(get_class(), size);
        }
        inline app::ModifierWrapper__Array* create_array(const std::vector<app::ModifierWrapper*>& items) {
            return il2cpp::array_new<app::ModifierWrapper__Array>(get_class(), items);
        }
    } // namespace ModifierWrapper
} // namespace app::classes::types
