#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Mono::Security::Interface::CertificateValidationHelper {
    IL2CPP_REGISTER_METHOD(0x02A46150, void, cctor, ())
    IL2CPP_REGISTER_METHOD(0x02A46210, bool, get_SupportsX509Chain, ())
    IL2CPP_REGISTER_METHOD(0x02A462B0, app::ICertificateValidator2 *, GetInternalValidator, (app::MonoTlsSettings * settings, app::MonoTlsProvider * provider))
}
