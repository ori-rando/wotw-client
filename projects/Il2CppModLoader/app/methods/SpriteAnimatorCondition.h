#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::SpriteAnimatorCondition {
    IL2CPP_REGISTER_METHOD(0x009AC3D0, bool, Validate, (app::SpriteAnimatorCondition * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x009AC410, app::String *, GetNiceName, (app::SpriteAnimatorCondition * this_ptr))
    IL2CPP_REGISTER_METHOD(0x003F8A60, void, ctor, (app::SpriteAnimatorCondition * this_ptr))
}
