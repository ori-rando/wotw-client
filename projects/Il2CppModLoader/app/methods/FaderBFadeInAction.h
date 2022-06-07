#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::FaderBFadeInAction {
    IL2CPP_REGISTER_METHOD(0x00449EA0, float, get_Duration, (app::FaderBFadeInAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00449EB0, void, set_Duration, (app::FaderBFadeInAction * this_ptr, float value))
    IL2CPP_REGISTER_METHOD(0x00993C80, void, Perform, (app::FaderBFadeInAction * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, Stop, (app::FaderBFadeInAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00993DF0, bool, get_IsPerforming, (app::FaderBFadeInAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00993EB0, app::String *, GetNiceName, (app::FaderBFadeInAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00993F70, void, ctor, (app::FaderBFadeInAction * this_ptr))
}
