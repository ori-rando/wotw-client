#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RootMotion::Demos::KissingRig_Partner {
    IL2CPP_REGISTER_METHOD(0x02053D20, void, Initiate, (app::KissingRig_Partner * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02221D30, void, Update, (app::KissingRig_Partner * this_ptr, float weight))
    IL2CPP_REGISTER_METHOD(0x02222AE0, app::Transform *, get_neck, (app::KissingRig_Partner * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02222B70, void, InverseTransformEffector, (app::KissingRig_Partner * this_ptr, app::FullBodyBipedEffector__Enum effector, app::Transform * target, app::Vector3 target_position, float weight))
    IL2CPP_REGISTER_METHOD(0x02222F80, void, ctor, (app::KissingRig_Partner * this_ptr))
}
