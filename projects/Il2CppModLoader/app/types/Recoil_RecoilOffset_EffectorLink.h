#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace Recoil_RecoilOffset_EffectorLink {
        namespace {
            app::Recoil_RecoilOffset_EffectorLink__Class* type_info_ref = nullptr;
        }
        app::Recoil_RecoilOffset_EffectorLink__Class** type_info = &type_info_ref;
        inline app::Recoil_RecoilOffset_EffectorLink__Class* get_class() {
            return il2cpp::get_nested_class<app::Recoil_RecoilOffset_EffectorLink__Class>(type_info, "RootMotion.FinalIK", "Recoil+RecoilOffset", "EffectorLink");
        }
        inline app::Recoil_RecoilOffset_EffectorLink* create() {
            return il2cpp::create_object<app::Recoil_RecoilOffset_EffectorLink>(get_class());
        }
        inline app::Recoil_RecoilOffset_EffectorLink__Array* create_array(int size) {
            return il2cpp::array_new<app::Recoil_RecoilOffset_EffectorLink__Array>(get_class(), size);
        }
        inline app::Recoil_RecoilOffset_EffectorLink__Array* create_array(const std::vector<app::Recoil_RecoilOffset_EffectorLink*>& items) {
            return il2cpp::array_new<app::Recoil_RecoilOffset_EffectorLink__Array>(get_class(), items);
        }
    } // namespace Recoil_RecoilOffset_EffectorLink
} // namespace app::classes::types
