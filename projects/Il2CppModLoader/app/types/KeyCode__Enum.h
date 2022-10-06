#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace KeyCode__Enum {
        extern IL2CPP_MODLOADER_DLLEXPORT app::KeyCode__Enum__Class** type_info;
        inline app::KeyCode__Enum__Class* get_class() {
            return il2cpp::get_class<app::KeyCode__Enum__Class>(type_info, "UnityEngine", "KeyCode");
        }
        inline app::KeyCode__Enum* create() {
            return il2cpp::create_object<app::KeyCode__Enum>(get_class());
        }
        inline app::KeyCode__Enum__Array* create_array(int size) {
            return il2cpp::array_new<app::KeyCode__Enum__Array>(get_class(), size);
        }
        inline app::KeyCode__Enum__Array* create_array(const std::vector<app::KeyCode__Enum__Boxed*>& items) {
            return il2cpp::array_new<app::KeyCode__Enum__Array>(get_class(), items);
        }
    } // namespace KeyCode__Enum
} // namespace app::classes::types
