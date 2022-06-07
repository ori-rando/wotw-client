#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::FadeFromBlackAction {
    IL2CPP_REGISTER_METHOD(0x008A34C0, float, get_Duration, (app::FadeFromBlackAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x008A34D0, void, set_Duration, (app::FadeFromBlackAction * this_ptr, float value))
    IL2CPP_REGISTER_METHOD(0x0098F080, void, Perform, (app::FadeFromBlackAction * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, Stop, (app::FadeFromBlackAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0098F1A0, bool, get_IsPerforming, (app::FadeFromBlackAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0098F260, app::String *, GetNiceName, (app::FadeFromBlackAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0043BB90, void, ctor, (app::FadeFromBlackAction * this_ptr))
}
