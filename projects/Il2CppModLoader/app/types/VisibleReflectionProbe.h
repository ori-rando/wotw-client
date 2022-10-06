#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace VisibleReflectionProbe {
        extern IL2CPP_MODLOADER_DLLEXPORT app::VisibleReflectionProbe__Class** type_info;
        inline app::VisibleReflectionProbe__Class* get_class() {
            return il2cpp::get_class<app::VisibleReflectionProbe__Class>(type_info, "UnityEngine.Experimental.Rendering", "VisibleReflectionProbe");
        }
        inline app::VisibleReflectionProbe* create() {
            return il2cpp::create_object<app::VisibleReflectionProbe>(get_class());
        }
        inline app::VisibleReflectionProbe__Boxed* box(app::VisibleReflectionProbe value) {
            return il2cpp::box_value<app::VisibleReflectionProbe__Boxed>(get_class(), value);
        }
        inline app::VisibleReflectionProbe__Array* create_array(int size) {
            return il2cpp::array_new<app::VisibleReflectionProbe__Array>(get_class(), size);
        }
        inline app::VisibleReflectionProbe__Array* create_array(const std::vector<app::VisibleReflectionProbe__Boxed>& items) {
            return il2cpp::array_new<app::VisibleReflectionProbe__Array>(get_class(), items);
        }
    } // namespace VisibleReflectionProbe
} // namespace app::classes::types
