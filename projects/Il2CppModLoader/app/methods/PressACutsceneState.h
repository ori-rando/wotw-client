#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::PressACutsceneState {
    IL2CPP_REGISTER_METHOD(0x00C6F800, app::CharacterAnimationSystem *, get_Animation, (app::PressACutsceneState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00C6F8D0, app::SeinCutsceneBlocked *, get_CutsceneBlocked, (app::PressACutsceneState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00C6F970, void, OnEnter, (app::PressACutsceneState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00C6F9C0, void, OnUpdate, (app::PressACutsceneState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00C6FD50, void, ctor, (app::PressACutsceneState * this_ptr))
}
