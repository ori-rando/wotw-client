#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::ShowSeinUIAction {
    IL2CPP_REGISTER_METHOD(0x00737200, void, Perform, (app::ShowSeinUIAction * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x00737330, app::String *, GetNiceName, (app::ShowSeinUIAction * this_ptr))
    IL2CPP_REGISTER_METHOD(0x004C87A0, void, ctor, (app::ShowSeinUIAction * this_ptr))
}
