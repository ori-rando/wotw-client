#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::LegacyEntityDamageReciever_ModifyDamageDelegate {
    IL2CPP_REGISTER_METHOD(0x00611810, void, ctor, (app::LegacyEntityDamageReciever_ModifyDamageDelegate * this_ptr, app::Object * object, void * method_1))
    IL2CPP_REGISTER_METHOD(0x00673B90, void, Invoke, (app::LegacyEntityDamageReciever_ModifyDamageDelegate * this_ptr, app::Damage * d))
    IL2CPP_REGISTER_METHOD(0x00674080, app::IAsyncResult *, BeginInvoke, (app::LegacyEntityDamageReciever_ModifyDamageDelegate * this_ptr, app::Damage * d, app::AsyncCallback * callback, app::Object * object))
    IL2CPP_REGISTER_METHOD(0x00611B40, void, EndInvoke, (app::LegacyEntityDamageReciever_ModifyDamageDelegate * this_ptr, app::IAsyncResult * result))
}
