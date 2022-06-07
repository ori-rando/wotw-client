#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::Timeline::EventTriggerGameplayAnimator {
    IL2CPP_REGISTER_METHOD(0x01BBD9E0, app::List_1_Moon_Timeline_EventTriggerGameplayAnimator_ *, FindInTimeline, (app::MoonTimeline * timeline, app::EventTriggerGameplayAnimator_Type__Enum type))
    IL2CPP_REGISTER_METHOD(0x01BBDD50, void, SynchronizeData, (app::EventTriggerGameplayAnimator * this_ptr, app::MoonTimeline * timeline, app::TimelineEntityRecord * record))
    IL2CPP_REGISTER_METHOD(0x01BBDEC0, void, ctor, (app::EventTriggerGameplayAnimator * this_ptr))
}
