#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::KwolokBossSludgeLaserBehaviour {
    IL2CPP_REGISTER_METHOD(0x012EA390, bool, get_IsInShootinWindow, (app::KwolokBossSludgeLaserBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x012EA470, void, OnEnter, (app::KwolokBossSludgeLaserBehaviour * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x012EA820, app::BehaviourStatus__Enum, OnExecute, (app::KwolokBossSludgeLaserBehaviour * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x012EB340, void, OnExit, (app::KwolokBossSludgeLaserBehaviour * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x012EB510, float, ComputeUtility, (app::KwolokBossSludgeLaserBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x012E9180, void, InitializeHitReactionController, (app::KwolokBossSludgeLaserBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x012EB630, void, ModifyLookAngleChangeSpeed, (app::KwolokBossSludgeLaserBehaviour * this_ptr, float * speed))
    IL2CPP_REGISTER_METHODINFO(0x0470F900, KwolokBossSludgeLaserBehaviour_ModifyLookAngleChangeSpeed__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x012EB650, void, ctor, (app::KwolokBossSludgeLaserBehaviour * this_ptr))
}
