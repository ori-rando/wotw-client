#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RootMotion::FinalIK::HitReaction_HitPointEffector {
    IL2CPP_REGISTER_METHOD(0x02077210, float, GetLength, (app::HitReaction_HitPointEffector * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02077590, void, CrossFadeStart, (app::HitReaction_HitPointEffector * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02077600, void, OnApply, (app::HitReaction_HitPointEffector * this_ptr, app::IKSolverFullBodyBiped * solver, float weight))
    IL2CPP_REGISTER_METHOD(0x02076780, void, ctor, (app::HitReaction_HitPointEffector * this_ptr))
}
