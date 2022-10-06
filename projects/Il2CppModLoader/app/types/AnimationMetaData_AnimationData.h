#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace AnimationMetaData_AnimationData {
        extern IL2CPP_MODLOADER_DLLEXPORT app::AnimationMetaData_AnimationData__Class** type_info;
        inline app::AnimationMetaData_AnimationData__Class* get_class() {
            return il2cpp::get_nested_class<app::AnimationMetaData_AnimationData__Class>(type_info, "", "AnimationMetaData", "AnimationData");
        }
        inline app::AnimationMetaData_AnimationData* create() {
            return il2cpp::create_object<app::AnimationMetaData_AnimationData>(get_class());
        }
        inline app::AnimationMetaData_AnimationData__Array* create_array(int size) {
            return il2cpp::array_new<app::AnimationMetaData_AnimationData__Array>(get_class(), size);
        }
        inline app::AnimationMetaData_AnimationData__Array* create_array(const std::vector<app::AnimationMetaData_AnimationData*>& items) {
            return il2cpp::array_new<app::AnimationMetaData_AnimationData__Array>(get_class(), items);
        }
    } // namespace AnimationMetaData_AnimationData
} // namespace app::classes::types
