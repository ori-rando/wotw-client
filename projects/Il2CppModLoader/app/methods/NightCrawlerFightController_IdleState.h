#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::NightCrawlerFightController_IdleState {
    IL2CPP_REGISTER_METHOD(0x002FA490, void, ctor, (app::NightCrawlerFightController_IdleState * this_ptr, app::NightCrawlerFightController * controller))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, IsRightSide, (app::NightCrawlerFightController_IdleState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00607D40, void, OnEnter, (app::NightCrawlerFightController_IdleState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00607FC0, void, OnExit, (app::NightCrawlerFightController_IdleState * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00607FE0, void, UpdateState, (app::NightCrawlerFightController_IdleState * this_ptr))
}
