#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Colorful::CLib {
    IL2CPP_REGISTER_METHOD(0x0303FD10, float, Frac, (float f))
    IL2CPP_REGISTER_METHOD(0x0303FDC0, bool, IsLinearColorSpace, ())
    IL2CPP_REGISTER_METHOD(0x0303FE10, bool, Approximately, (float source, float about, float range))
}
