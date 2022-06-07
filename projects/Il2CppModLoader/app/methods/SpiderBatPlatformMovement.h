#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::SpiderBatPlatformMovement {
    IL2CPP_REGISTER_METHOD(0x0095DF10, void, set_IsDeathFalling, (app::SpiderBatPlatformMovement * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x0095DF20, bool, get_IsSuspended, (app::SpiderBatPlatformMovement * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0095DF30, void, set_IsSuspended, (app::SpiderBatPlatformMovement * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x0095E220, bool, OnUpdate, (app::SpiderBatPlatformMovement * this_ptr, float delta_time))
    IL2CPP_REGISTER_METHOD(0x0095E240, void, OnSuspend, (app::SpiderBatPlatformMovement * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0095E3C0, void, OnResume, (app::SpiderBatPlatformMovement * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0095E530, void, ctor, (app::SpiderBatPlatformMovement * this_ptr))
}
