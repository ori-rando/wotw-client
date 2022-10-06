#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace SqlBoolean {
        extern IL2CPP_MODLOADER_DLLEXPORT app::SqlBoolean__Class** type_info;
        inline app::SqlBoolean__Class* get_class() {
            return il2cpp::get_class<app::SqlBoolean__Class>(type_info, "System.Data.SqlTypes", "SqlBoolean");
        }
        inline app::SqlBoolean* create() {
            return il2cpp::create_object<app::SqlBoolean>(get_class());
        }
        inline app::SqlBoolean__Boxed* box(app::SqlBoolean value) {
            return il2cpp::box_value<app::SqlBoolean__Boxed>(get_class(), value);
        }
        inline app::SqlBoolean__Array* create_array(int size) {
            return il2cpp::array_new<app::SqlBoolean__Array>(get_class(), size);
        }
        inline app::SqlBoolean__Array* create_array(const std::vector<app::SqlBoolean__Boxed>& items) {
            return il2cpp::array_new<app::SqlBoolean__Array>(get_class(), items);
        }
    } // namespace SqlBoolean
} // namespace app::classes::types
