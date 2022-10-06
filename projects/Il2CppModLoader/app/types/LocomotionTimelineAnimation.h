#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace LocomotionTimelineAnimation {
        namespace {
            app::LocomotionTimelineAnimation__Class* type_info_ref = nullptr;
        }
        app::LocomotionTimelineAnimation__Class** type_info = &type_info_ref;
        inline app::LocomotionTimelineAnimation__Class* get_class() {
            return il2cpp::get_class<app::LocomotionTimelineAnimation__Class>(type_info, "Moon", "LocomotionTimelineAnimation");
        }
        inline app::LocomotionTimelineAnimation* create() {
            return il2cpp::create_object<app::LocomotionTimelineAnimation>(get_class());
        }
        inline app::LocomotionTimelineAnimation__Array* create_array(int size) {
            return il2cpp::array_new<app::LocomotionTimelineAnimation__Array>(get_class(), size);
        }
        inline app::LocomotionTimelineAnimation__Array* create_array(const std::vector<app::LocomotionTimelineAnimation*>& items) {
            return il2cpp::array_new<app::LocomotionTimelineAnimation__Array>(get_class(), items);
        }
    } // namespace LocomotionTimelineAnimation
} // namespace app::classes::types
