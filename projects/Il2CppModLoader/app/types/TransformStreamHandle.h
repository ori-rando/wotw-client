#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace TransformStreamHandle {
        namespace {
            app::TransformStreamHandle__Class* type_info_ref = nullptr;
        }
        app::TransformStreamHandle__Class** type_info = &type_info_ref;
        inline app::TransformStreamHandle__Class* get_class() {
            return il2cpp::get_class<app::TransformStreamHandle__Class>(type_info, "UnityEngine.Experimental.Animations", "TransformStreamHandle");
        }
        inline app::TransformStreamHandle* create() {
            return il2cpp::create_object<app::TransformStreamHandle>(get_class());
        }
        inline app::TransformStreamHandle__Boxed* box(app::TransformStreamHandle value) {
            return il2cpp::box_value<app::TransformStreamHandle__Boxed>(get_class(), value);
        }
        inline app::TransformStreamHandle__Array* create_array(int size) {
            return il2cpp::array_new<app::TransformStreamHandle__Array>(get_class(), size);
        }
        inline app::TransformStreamHandle__Array* create_array(const std::vector<app::TransformStreamHandle__Boxed>& items) {
            return il2cpp::array_new<app::TransformStreamHandle__Array>(get_class(), items);
        }
    } // namespace TransformStreamHandle
} // namespace app::classes::types
