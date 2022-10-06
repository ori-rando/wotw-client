#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace UserDataRecord_1 {
        namespace {
            app::UserDataRecord_1__Class* type_info_ref = nullptr;
        }
        app::UserDataRecord_1__Class** type_info = &type_info_ref;
        inline app::UserDataRecord_1__Class* get_class() {
            return il2cpp::get_class<app::UserDataRecord_1__Class>(type_info, "PlayFab.ServerModels", "UserDataRecord");
        }
        inline app::UserDataRecord_1* create() {
            return il2cpp::create_object<app::UserDataRecord_1>(get_class());
        }
        inline app::UserDataRecord_1__Array* create_array(int size) {
            return il2cpp::array_new<app::UserDataRecord_1__Array>(get_class(), size);
        }
        inline app::UserDataRecord_1__Array* create_array(const std::vector<app::UserDataRecord_1*>& items) {
            return il2cpp::array_new<app::UserDataRecord_1__Array>(get_class(), items);
        }
    } // namespace UserDataRecord_1
} // namespace app::classes::types
