#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace PhysicsSystemPointSet_PhysicsSystemPoint {
        extern IL2CPP_MODLOADER_DLLEXPORT app::PhysicsSystemPointSet_PhysicsSystemPoint__Class** type_info;
        inline app::PhysicsSystemPointSet_PhysicsSystemPoint__Class* get_class() {
            return il2cpp::get_nested_class<app::PhysicsSystemPointSet_PhysicsSystemPoint__Class>(type_info, "", "PhysicsSystemPointSet", "PhysicsSystemPoint");
        }
        inline app::PhysicsSystemPointSet_PhysicsSystemPoint* create() {
            return il2cpp::create_object<app::PhysicsSystemPointSet_PhysicsSystemPoint>(get_class());
        }
        inline app::PhysicsSystemPointSet_PhysicsSystemPoint__Array* create_array(int size) {
            return il2cpp::array_new<app::PhysicsSystemPointSet_PhysicsSystemPoint__Array>(get_class(), size);
        }
        inline app::PhysicsSystemPointSet_PhysicsSystemPoint__Array* create_array(const std::vector<app::PhysicsSystemPointSet_PhysicsSystemPoint*>& items) {
            return il2cpp::array_new<app::PhysicsSystemPointSet_PhysicsSystemPoint__Array>(get_class(), items);
        }
    } // namespace PhysicsSystemPointSet_PhysicsSystemPoint
} // namespace app::classes::types
