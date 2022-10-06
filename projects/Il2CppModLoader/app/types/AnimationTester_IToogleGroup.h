#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace AnimationTester_IToogleGroup {
        extern IL2CPP_MODLOADER_DLLEXPORT app::AnimationTester_IToogleGroup__Class** type_info;
        inline app::AnimationTester_IToogleGroup__Class* get_class() {
            return il2cpp::get_nested_class<app::AnimationTester_IToogleGroup__Class>(type_info, "", "AnimationTester", "IToogleGroup");
        }
        inline app::AnimationTester_IToogleGroup__Array* create_array(int size) {
            return il2cpp::array_new<app::AnimationTester_IToogleGroup__Array>(get_class(), size);
        }
        inline app::AnimationTester_IToogleGroup__Array* create_array(const std::vector<app::AnimationTester_IToogleGroup*>& items) {
            return il2cpp::array_new<app::AnimationTester_IToogleGroup__Array>(get_class(), items);
        }
    } // namespace AnimationTester_IToogleGroup
} // namespace app::classes::types
