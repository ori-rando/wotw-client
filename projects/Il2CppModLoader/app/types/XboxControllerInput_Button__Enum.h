#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace XboxControllerInput_Button__Enum {
        extern IL2CPP_MODLOADER_DLLEXPORT app::XboxControllerInput_Button__Enum__Class** type_info;
        inline app::XboxControllerInput_Button__Enum__Class* get_class() {
            return il2cpp::get_nested_class<app::XboxControllerInput_Button__Enum__Class>(type_info, "SmartInput", "XboxControllerInput", "Button");
        }
        inline app::XboxControllerInput_Button__Enum* create() {
            return il2cpp::create_object<app::XboxControllerInput_Button__Enum>(get_class());
        }
        inline app::XboxControllerInput_Button__Enum__Array* create_array(int size) {
            return il2cpp::array_new<app::XboxControllerInput_Button__Enum__Array>(get_class(), size);
        }
        inline app::XboxControllerInput_Button__Enum__Array* create_array(const std::vector<app::XboxControllerInput_Button__Enum__Boxed*>& items) {
            return il2cpp::array_new<app::XboxControllerInput_Button__Enum__Array>(get_class(), items);
        }
    } // namespace XboxControllerInput_Button__Enum
} // namespace app::classes::types
