#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace TentacleInterestPoint {
        namespace {
            app::TentacleInterestPoint__Class* type_info_ref = nullptr;
        }
        app::TentacleInterestPoint__Class** type_info = &type_info_ref;
        inline app::TentacleInterestPoint__Class* get_class() {
            return il2cpp::get_class<app::TentacleInterestPoint__Class>(type_info, "", "TentacleInterestPoint");
        }
        inline app::TentacleInterestPoint* create() {
            return il2cpp::create_object<app::TentacleInterestPoint>(get_class());
        }
        inline app::TentacleInterestPoint__Array* create_array(int size) {
            return il2cpp::array_new<app::TentacleInterestPoint__Array>(get_class(), size);
        }
        inline app::TentacleInterestPoint__Array* create_array(const std::vector<app::TentacleInterestPoint*>& items) {
            return il2cpp::array_new<app::TentacleInterestPoint__Array>(get_class(), items);
        }
    } // namespace TentacleInterestPoint
} // namespace app::classes::types
