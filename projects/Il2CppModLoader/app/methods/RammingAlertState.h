#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RammingAlertState {
    IL2CPP_REGISTER_METHOD(0x004C1E90, void, ctor, (app::RammingAlertState * this_ptr, app::RammingEnemy * ground_enemy))
    IL2CPP_REGISTER_METHOD(0x00728700, void, OnEnter, (app::RammingAlertState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, OnExit, (app::RammingAlertState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00728810, void, UpdateState, (app::RammingAlertState * this_ptr))
}
