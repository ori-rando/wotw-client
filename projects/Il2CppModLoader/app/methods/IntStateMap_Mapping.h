#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::IntStateMap_Mapping {
    IL2CPP_REGISTER_METHOD(0x0010E170, int32_t, get_Index, (app::IntStateMap_Mapping__Boxed * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0010DB80, void, set_Index, (app::IntStateMap_Mapping__Boxed * this_ptr, int32_t value))
    IL2CPP_REGISTER_METHOD(0x001C0330, bool, Matches, (app::IntStateMap_Mapping__Boxed * this_ptr, app::IUberState * state))
}
