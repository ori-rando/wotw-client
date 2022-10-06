#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace Uri {
        extern IL2CPP_MODLOADER_DLLEXPORT app::Uri__Class** type_info;
        inline app::Uri__Class* get_class() {
            return il2cpp::get_class<app::Uri__Class>(type_info, "System", "Uri");
        }
        inline app::Uri* create() {
            return il2cpp::create_object<app::Uri>(get_class());
        }
        inline app::Uri__Array* create_array(int size) {
            return il2cpp::array_new<app::Uri__Array>(get_class(), size);
        }
        inline app::Uri__Array* create_array(const std::vector<app::Uri*>& items) {
            return il2cpp::array_new<app::Uri__Array>(get_class(), items);
        }
    } // namespace Uri
} // namespace app::classes::types
