#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::ResetTriggerOnCheckpoint {
    IL2CPP_REGISTER_METHOD(0x00905430, void, Awake, (app::ResetTriggerOnCheckpoint * this_ptr))
    IL2CPP_REGISTER_METHOD(0x009055D0, void, Start, (app::ResetTriggerOnCheckpoint * this_ptr))
    IL2CPP_REGISTER_METHOD(0x009056A0, void, OnEnable, (app::ResetTriggerOnCheckpoint * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00905770, void, OnDestroy, (app::ResetTriggerOnCheckpoint * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00905910, void, OnRestoreCheckpoint, (app::ResetTriggerOnCheckpoint * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04776C80, ResetTriggerOnCheckpoint_OnRestoreCheckpoint__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x003F8A60, void, ctor, (app::ResetTriggerOnCheckpoint * this_ptr))
}
