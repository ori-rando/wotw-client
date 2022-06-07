#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::UnityEngine::Networking::CertificateHandler {
    IL2CPP_REGISTER_METHOD(0x0317DB70, void, Release, (app::CertificateHandler * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0317DBC0, void, Finalize, (app::CertificateHandler * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00B1B670, bool, ValidateCertificate, (app::CertificateHandler * this_ptr, app::Byte__Array * certificate_data))
    IL2CPP_REGISTER_METHOD(0x0317DC50, bool, ValidateCertificateNative, (app::CertificateHandler * this_ptr, app::Byte__Array * certificate_data))
    IL2CPP_REGISTER_METHOD(0x0317DC70, void, Dispose, (app::CertificateHandler * this_ptr))
}
