#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace ModifierDataModel {
        namespace {
            app::ModifierDataModel__Class* type_info_ref = nullptr;
        }
        app::ModifierDataModel__Class** type_info = &type_info_ref;
        inline app::ModifierDataModel__Class* get_class() {
            return il2cpp::get_class<app::ModifierDataModel__Class>(type_info, "Moon.ArtOptimization", "ModifierDataModel");
        }
        inline app::ModifierDataModel* create() {
            return il2cpp::create_object<app::ModifierDataModel>(get_class());
        }
        inline app::ModifierDataModel__Array* create_array(int size) {
            return il2cpp::array_new<app::ModifierDataModel__Array>(get_class(), size);
        }
        inline app::ModifierDataModel__Array* create_array(const std::vector<app::ModifierDataModel*>& items) {
            return il2cpp::array_new<app::ModifierDataModel__Array>(get_class(), items);
        }
    } // namespace ModifierDataModel
} // namespace app::classes::types
