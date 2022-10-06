#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace IAnimatedValueListener {
        extern IL2CPP_MODLOADER_DLLEXPORT app::IAnimatedValueListener__Class** type_info;
        inline app::IAnimatedValueListener__Class* get_class() {
            return il2cpp::get_class<app::IAnimatedValueListener__Class>(type_info, "Moon", "IAnimatedValueListener");
        }
        inline app::IAnimatedValueListener__Array* create_array(int size) {
            return il2cpp::array_new<app::IAnimatedValueListener__Array>(get_class(), size);
        }
        inline app::IAnimatedValueListener__Array* create_array(const std::vector<app::IAnimatedValueListener*>& items) {
            return il2cpp::array_new<app::IAnimatedValueListener__Array>(get_class(), items);
        }
    } // namespace IAnimatedValueListener
} // namespace app::classes::types
