#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::UnityEngine::Experimental::Animations::ProcessAnimationJobStruct_1_Moon_Animation_DelayJointPostprocessJob_ {
    IL2CPP_REGISTER_METHOD(0x02ACAFD0, void *, GetJobReflectionData, ())
    IL2CPP_REGISTER_METHOD(0x02ACB5A0, void, ExecuteProcessAnimation, (app::DelayJointPostprocessJob * data, void * animation_stream_ptr, void * unused_ptr, app::JobRanges * ranges, int32_t job_index))
    IL2CPP_REGISTER_METHOD(0x02ACB660, void, ExecuteProcessRootMotion, (app::DelayJointPostprocessJob * data, void * animation_stream_ptr, void * unused_ptr, app::JobRanges * ranges, int32_t job_index))
}
