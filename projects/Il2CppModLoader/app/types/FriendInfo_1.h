#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace FriendInfo_1 {
        namespace {
            app::FriendInfo_1__Class* type_info_ref = nullptr;
        }
        app::FriendInfo_1__Class** type_info = &type_info_ref;
        inline app::FriendInfo_1__Class* get_class() {
            return il2cpp::get_class<app::FriendInfo_1__Class>(type_info, "PlayFab.ServerModels", "FriendInfo");
        }
        inline app::FriendInfo_1* create() {
            return il2cpp::create_object<app::FriendInfo_1>(get_class());
        }
        inline app::FriendInfo_1__Array* create_array(int size) {
            return il2cpp::array_new<app::FriendInfo_1__Array>(get_class(), size);
        }
        inline app::FriendInfo_1__Array* create_array(const std::vector<app::FriendInfo_1*>& items) {
            return il2cpp::array_new<app::FriendInfo_1__Array>(get_class(), items);
        }
    } // namespace FriendInfo_1
} // namespace app::classes::types
