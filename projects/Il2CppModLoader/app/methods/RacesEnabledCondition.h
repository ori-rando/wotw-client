#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RacesEnabledCondition {
    IL2CPP_REGISTER_METHOD(0x00724960, bool, Validate, (app::RacesEnabledCondition * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x003F8A60, void, ctor, (app::RacesEnabledCondition * this_ptr))
}
