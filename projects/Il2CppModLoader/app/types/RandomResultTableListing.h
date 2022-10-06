#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace RandomResultTableListing {
        namespace {
            app::RandomResultTableListing__Class* type_info_ref = nullptr;
        }
        app::RandomResultTableListing__Class** type_info = &type_info_ref;
        inline app::RandomResultTableListing__Class* get_class() {
            return il2cpp::get_class<app::RandomResultTableListing__Class>(type_info, "PlayFab.ServerModels", "RandomResultTableListing");
        }
        inline app::RandomResultTableListing* create() {
            return il2cpp::create_object<app::RandomResultTableListing>(get_class());
        }
        inline app::RandomResultTableListing__Array* create_array(int size) {
            return il2cpp::array_new<app::RandomResultTableListing__Array>(get_class(), size);
        }
        inline app::RandomResultTableListing__Array* create_array(const std::vector<app::RandomResultTableListing*>& items) {
            return il2cpp::array_new<app::RandomResultTableListing__Array>(get_class(), items);
        }
    } // namespace RandomResultTableListing
} // namespace app::classes::types
