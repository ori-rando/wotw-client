#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RotatingRoomController {
    IL2CPP_REGISTER_METHOD(0x01370840, void, FixedUpdate, (app::RotatingRoomController * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01370A10, void, Serialize, (app::RotatingRoomController * this_ptr, app::Archive * ar))
    IL2CPP_REGISTER_METHOD(0x0044C850, void, ctor, (app::RotatingRoomController * this_ptr))
}
