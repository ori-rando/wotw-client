#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::LizardSpawnTask {
    IL2CPP_REGISTER_METHOD(0x00FB24F0, void, OnEnterTask, (app::LizardSpawnTask * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x00420EE0, app::BehaviourStatus__Enum, OnExecuteTask, (app::LizardSpawnTask * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x00FB2660, void, StartSpawnTimeline, (app::LizardSpawnTask * this_ptr, app::MoonTimeline * timeline))
    IL2CPP_REGISTER_METHOD(0x006B38C0, void, OnSpawningFinnished, (app::LizardSpawnTask * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0470BD90, LizardSpawnTask_OnSpawningFinnished__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x003FFDF0, bool, ShouldPauseLocomotion, (app::LizardSpawnTask * this_ptr))
    IL2CPP_REGISTER_METHOD(0x006B38D0, void, ctor, (app::LizardSpawnTask * this_ptr))
}
