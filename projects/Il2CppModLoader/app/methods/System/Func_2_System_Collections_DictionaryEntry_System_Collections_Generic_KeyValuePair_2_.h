#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Func_2_System_Collections_DictionaryEntry_System_Collections_Generic_KeyValuePair_2_ {
    IL2CPP_REGISTER_METHOD(0x00611810, void, ctor, (app::Func_2_System_Collections_DictionaryEntry_System_Collections_Generic_KeyValuePair_2_ * this_ptr, app::Object * object, void * method_1))
    IL2CPP_REGISTER_METHOD(0x028867C0, app::KeyValuePair_2_System_Object_System_Object_, Invoke, (app::Func_2_System_Collections_DictionaryEntry_System_Collections_Generic_KeyValuePair_2_ * this_ptr, app::DictionaryEntry arg))
    IL2CPP_REGISTER_METHOD(0x02F9DDD0, app::IAsyncResult *, BeginInvoke, (app::Func_2_System_Collections_DictionaryEntry_System_Collections_Generic_KeyValuePair_2_ * this_ptr, app::DictionaryEntry arg, app::AsyncCallback * callback, app::Object * object))
    IL2CPP_REGISTER_METHOD(0x01C7A680, app::KeyValuePair_2_System_Object_System_Object_, EndInvoke, (app::Func_2_System_Collections_DictionaryEntry_System_Collections_Generic_KeyValuePair_2_ * this_ptr, app::IAsyncResult * result))
}
