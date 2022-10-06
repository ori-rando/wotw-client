#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace FacebookInstantGamesPlayFabIdPair_1 {
        namespace {
            app::FacebookInstantGamesPlayFabIdPair_1__Class* type_info_ref = nullptr;
        }
        app::FacebookInstantGamesPlayFabIdPair_1__Class** type_info = &type_info_ref;
        inline app::FacebookInstantGamesPlayFabIdPair_1__Class* get_class() {
            return il2cpp::get_class<app::FacebookInstantGamesPlayFabIdPair_1__Class>(type_info, "PlayFab.ServerModels", "FacebookInstantGamesPlayFabIdPair");
        }
        inline app::FacebookInstantGamesPlayFabIdPair_1* create() {
            return il2cpp::create_object<app::FacebookInstantGamesPlayFabIdPair_1>(get_class());
        }
        inline app::FacebookInstantGamesPlayFabIdPair_1__Array* create_array(int size) {
            return il2cpp::array_new<app::FacebookInstantGamesPlayFabIdPair_1__Array>(get_class(), size);
        }
        inline app::FacebookInstantGamesPlayFabIdPair_1__Array* create_array(const std::vector<app::FacebookInstantGamesPlayFabIdPair_1*>& items) {
            return il2cpp::array_new<app::FacebookInstantGamesPlayFabIdPair_1__Array>(get_class(), items);
        }
    } // namespace FacebookInstantGamesPlayFabIdPair_1
} // namespace app::classes::types
