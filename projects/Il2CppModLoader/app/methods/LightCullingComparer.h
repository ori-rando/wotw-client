#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::LightCullingComparer {
    IL2CPP_REGISTER_METHOD(0x0114B0B0, int32_t, Compare, (app::LightCullingComparer * this_ptr, app::PointLightMaskModifier * x, app::PointLightMaskModifier * y))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor, (app::LightCullingComparer * this_ptr))
}
