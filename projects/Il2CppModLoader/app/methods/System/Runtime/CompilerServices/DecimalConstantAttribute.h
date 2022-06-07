#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Runtime::CompilerServices::DecimalConstantAttribute {
    IL2CPP_REGISTER_METHOD(0x01A921F0, void, ctor, (app::DecimalConstantAttribute * this_ptr, uint8_t scale, uint8_t sign, uint32_t hi, uint32_t mid, uint32_t low))
    IL2CPP_REGISTER_METHOD(0x01349560, app::Decimal, get_Value, (app::DecimalConstantAttribute * this_ptr))
}
