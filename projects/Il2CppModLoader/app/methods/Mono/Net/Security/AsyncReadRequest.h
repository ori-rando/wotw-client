#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Mono::Net::Security::AsyncReadRequest {
    IL2CPP_REGISTER_METHOD(0x0217C520, void, ctor, (app::AsyncReadRequest * this_ptr, app::MobileAuthenticatedStream * parent, bool sync, app::Byte__Array * buffer, int32_t offset, int32_t size))
    IL2CPP_REGISTER_METHOD(0x0217C530, app::AsyncOperationStatus__Enum, Run, (app::AsyncReadRequest * this_ptr, app::AsyncOperationStatus__Enum status))
}
