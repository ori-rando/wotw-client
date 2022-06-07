#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::CollisionContext {
    IL2CPP_REGISTER_METHOD(0x0058DA40, void, ctor, (app::CollisionContext * this_ptr, app::Collision * collision, app::Collider * collision_reciever))
    IL2CPP_REGISTER_METHOD(0x002FA280, app::Collision *, get_Collision, (app::CollisionContext * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FA490, void, set_Collision, (app::CollisionContext * this_ptr, app::Collision * value))
    IL2CPP_REGISTER_METHOD(0x002FB930, app::Collider *, get_CollisionReciever, (app::CollisionContext * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FB940, void, set_CollisionReciever, (app::CollisionContext * this_ptr, app::Collider * value))
}
