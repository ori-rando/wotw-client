#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace CatalogItem_1 {
        namespace {
            app::CatalogItem_1__Class* type_info_ref = nullptr;
        }
        app::CatalogItem_1__Class** type_info = &type_info_ref;
        inline app::CatalogItem_1__Class* get_class() {
            return il2cpp::get_class<app::CatalogItem_1__Class>(type_info, "PlayFab.ServerModels", "CatalogItem");
        }
        inline app::CatalogItem_1* create() {
            return il2cpp::create_object<app::CatalogItem_1>(get_class());
        }
        inline app::CatalogItem_1__Array* create_array(int size) {
            return il2cpp::array_new<app::CatalogItem_1__Array>(get_class(), size);
        }
        inline app::CatalogItem_1__Array* create_array(const std::vector<app::CatalogItem_1*>& items) {
            return il2cpp::array_new<app::CatalogItem_1__Array>(get_class(), items);
        }
    } // namespace CatalogItem_1
} // namespace app::classes::types
