#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::Telemetry::Performance::Settings::GodRaysProfilingSetting {
    IL2CPP_REGISTER_METHOD(0x007E3F10, app::ProfilingSettings_SettingType__Enum, get_SettingType, (app::GodRaysProfilingSetting * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00E3D410, app::RenderScope__Enum *, GetScope, (app::GodRaysProfilingSetting * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor, (app::GodRaysProfilingSetting * this_ptr))
}
