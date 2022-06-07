#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Security::SecurityDocument {
    IL2CPP_REGISTER_METHOD(0x01E1DF90, void, ctor, (app::SecurityDocument * this_ptr, int32_t num_data))
    IL2CPP_REGISTER_METHOD(0x01E1E030, void, GuaranteeSize, (app::SecurityDocument * this_ptr, int32_t size))
    IL2CPP_REGISTER_METHOD(0x01E1E120, void, AddString, (app::SecurityDocument * this_ptr, app::String * str, int32_t * position))
    IL2CPP_REGISTER_METHOD(0x01E1E2C0, void, AppendString, (app::SecurityDocument * this_ptr, app::String * str, int32_t * position))
    IL2CPP_REGISTER_METHODINFO(0x04730B38, SecurityDocument_AppendString__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01E1E400, int32_t, EncodedStringSize, (app::String * str))
    IL2CPP_REGISTER_METHOD(0x01E1E420, app::String *, GetString, (app::SecurityDocument * this_ptr, int32_t * position, bool b_create))
    IL2CPP_REGISTER_METHOD(0x01E1E8A0, void, AddToken, (app::SecurityDocument * this_ptr, uint8_t b, int32_t * position))
    IL2CPP_REGISTER_METHOD(0x01E1E910, app::SecurityElement *, GetRootElement, (app::SecurityDocument * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01E1E940, app::SecurityElement *, GetElement, (app::SecurityDocument * this_ptr, int32_t position, bool b_create))
    IL2CPP_REGISTER_METHOD(0x01E1E960, app::SecurityElement *, InternalGetElement, (app::SecurityDocument * this_ptr, int32_t * position, bool b_create))
    IL2CPP_REGISTER_METHODINFO(0x04724DA8, SecurityDocument_InternalGetElement__MethodInfo)
}
