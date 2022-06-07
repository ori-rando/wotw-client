#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::GhostParsingHelper {
    IL2CPP_REGISTER_METHOD(0x007DB4E0, app::GameObject *, CreatePlaybackInstance, (app::GameObject * prefab, app::Vector3 position, app::Quaternion rotation, app::Transform * parent))
    IL2CPP_REGISTER_METHOD(0x007DB720, float, FrameToSeconds, (int32_t frame))
    IL2CPP_REGISTER_METHOD(0x007DB730, float, FrameToSecondsGlobal, (int32_t frame, app::List_1_System_Single_ * time_per_frame))
    IL2CPP_REGISTER_METHOD(0x007DB820, float, FrameToSecondsLocal, (int32_t frame, app::List_1_System_Single_ * time_per_frame, int32_t global_start_frame))
    IL2CPP_REGISTER_METHOD(0x007DB900, float, SnapTimeToFrameTime, (float time))
    IL2CPP_REGISTER_METHOD(0x007DBA10, void, AddTimelineEntity, (app::MoonTimeline * parent, app::ITimelineEntity * child, float start_time, float duration))
    IL2CPP_REGISTER_METHOD(0x007DBDC0, void, RemoveTimelineEntity, (app::MoonTimeline * parent, app::EntityId child_i_d))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor, (app::GhostParsingHelper * this_ptr))
    IL2CPP_REGISTER_METHOD(0x007DBDE0, void, cctor, ())
    IL2CPP_REGISTER_METHOD(0x015E9D90, app::Object *, CreateAnimator, (app::Transform * parent, app::String * name))
    IL2CPP_REGISTER_METHOD(0x015E9FA0, app::Object *, GetOrCreateAnimator, (app::Transform * parent, app::String * name, int32_t i_d, app::Dictionary_2_System_Int32_UnityEngine_Component_ * parsing_groups_cache))
    IL2CPP_REGISTER_METHOD(0x015E9C30, app::Object *, AddTimelineChildren, (app::MoonTimeline * parent, float start_time, float duration))
}
