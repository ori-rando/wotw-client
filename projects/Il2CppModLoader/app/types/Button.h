#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace Button {
        namespace {
            app::Button__Class* type_info_ref = nullptr;
        }
        app::Button__Class** type_info = &type_info_ref;
        inline app::Button__Class* get_class() {
            return il2cpp::get_class<app::Button__Class>(type_info, "UnityEngine.UI", "Button");
        }
        inline app::Button* create() {
            return il2cpp::create_object<app::Button>(get_class());
        }
        inline app::Button__Array* create_array(int size) {
            return il2cpp::array_new<app::Button__Array>(get_class(), size);
        }
        inline app::Button__Array* create_array(const std::vector<app::Button*>& items) {
            return il2cpp::array_new<app::Button__Array>(get_class(), items);
        }
    } // namespace Button
} // namespace app::classes::types
