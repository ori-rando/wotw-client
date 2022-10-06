#pragma once
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/macros.h>

namespace app::classes::types {
    namespace GameCertificateReferenceParams {
        namespace {
            app::GameCertificateReferenceParams__Class* type_info_ref = nullptr;
        }
        app::GameCertificateReferenceParams__Class** type_info = &type_info_ref;
        inline app::GameCertificateReferenceParams__Class* get_class() {
            return il2cpp::get_class<app::GameCertificateReferenceParams__Class>(type_info, "PlayFab.MultiplayerModels", "GameCertificateReferenceParams");
        }
        inline app::GameCertificateReferenceParams* create() {
            return il2cpp::create_object<app::GameCertificateReferenceParams>(get_class());
        }
        inline app::GameCertificateReferenceParams__Array* create_array(int size) {
            return il2cpp::array_new<app::GameCertificateReferenceParams__Array>(get_class(), size);
        }
        inline app::GameCertificateReferenceParams__Array* create_array(const std::vector<app::GameCertificateReferenceParams*>& items) {
            return il2cpp::array_new<app::GameCertificateReferenceParams__Array>(get_class(), items);
        }
    } // namespace GameCertificateReferenceParams
} // namespace app::classes::types
