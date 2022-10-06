#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace InputField_ContentType__Enum {
        namespace {
            app::InputField_ContentType__Enum__Class* type_info_ref = nullptr;
        }
        app::InputField_ContentType__Enum__Class** type_info = &type_info_ref;
        inline app::InputField_ContentType__Enum__Class* get_class() {
            return il2cpp::get_nested_class<app::InputField_ContentType__Enum__Class>(type_info, "UnityEngine.UI", "InputField", "ContentType");
        }
        inline app::InputField_ContentType__Enum* create() {
            return il2cpp::create_object<app::InputField_ContentType__Enum>(get_class());
        }
        inline app::InputField_ContentType__Enum__Array* create_array(int size) {
            return il2cpp::array_new<app::InputField_ContentType__Enum__Array>(get_class(), size);
        }
        inline app::InputField_ContentType__Enum__Array* create_array(const std::vector<app::InputField_ContentType__Enum__Boxed*>& items) {
            return il2cpp::array_new<app::InputField_ContentType__Enum__Array>(get_class(), items);
        }
    } // namespace InputField_ContentType__Enum
} // namespace app::classes::types
