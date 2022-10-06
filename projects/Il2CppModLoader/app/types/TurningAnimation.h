#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace TurningAnimation {
        namespace {
            app::TurningAnimation__Class* type_info_ref = nullptr;
        }
        app::TurningAnimation__Class** type_info = &type_info_ref;
        inline app::TurningAnimation__Class* get_class() {
            return il2cpp::get_class<app::TurningAnimation__Class>(type_info, "Moon", "TurningAnimation");
        }
        inline app::TurningAnimation* create() {
            return il2cpp::create_object<app::TurningAnimation>(get_class());
        }
        inline app::TurningAnimation__Array* create_array(int size) {
            return il2cpp::array_new<app::TurningAnimation__Array>(get_class(), size);
        }
        inline app::TurningAnimation__Array* create_array(const std::vector<app::TurningAnimation*>& items) {
            return il2cpp::array_new<app::TurningAnimation__Array>(get_class(), items);
        }
    } // namespace TurningAnimation
} // namespace app::classes::types
