#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Collections::Generic::List_1_System_Type_ {
    IL2CPP_REGISTER_METHOD(0x025E8100, void, ctor_1, (app::List_1_System_Type_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0474EA80, List_1_System_Type___ctor__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02FE8D00, bool, Contains, (app::List_1_System_Type_ * this_ptr, app::Type * item))
    IL2CPP_REGISTER_METHODINFO(0x047223D0, List_1_System_Type__Contains__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F1E150, void, Add, (app::List_1_System_Type_ * this_ptr, app::Type * item))
    IL2CPP_REGISTER_METHODINFO(0x04782920, List_1_System_Type__Add__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025E81E0, void, ctor_2, (app::List_1_System_Type_ * this_ptr, int32_t capacity))
    IL2CPP_REGISTER_METHODINFO(0x04739E18, List_1_System_Type___ctor_1__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025EFC50, app::Type *, get_Item, (app::List_1_System_Type_ * this_ptr, int32_t index))
    IL2CPP_REGISTER_METHODINFO(0x0473E1B0, List_1_System_Type__get_Item__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025EAEF0, app::Type__Array *, ToArray, (app::List_1_System_Type_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04722DF0, List_1_System_Type__ToArray__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025F0B10, app::List_1_T_Enumerator_System_Type_, GetEnumerator, (app::List_1_System_Type_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x047666E8, List_1_System_Type__GetEnumerator__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025EAC80, void, Reverse, (app::List_1_System_Type_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0476C4F8, List_1_System_Type__Reverse__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025F0BE0, int32_t, IndexOf, (app::List_1_System_Type_ * this_ptr, app::Type * item))
    IL2CPP_REGISTER_METHODINFO(0x04769A60, List_1_System_Type__IndexOf__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02FE8360, void, ctor_3, (app::List_1_System_Type_ * this_ptr, app::IEnumerable_1_System_Type_ * collection))
    IL2CPP_REGISTER_METHODINFO(0x04784BE8, List_1_System_Type___ctor_2__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025F12F0, bool, Remove, (app::List_1_System_Type_ * this_ptr, app::Type * item))
    IL2CPP_REGISTER_METHODINFO(0x04725250, List_1_System_Type__Remove__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x00529FF0, int32_t, get_Count, (app::List_1_System_Type_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0473FC28, List_1_System_Type__get_Count__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x025EABD0, void, RemoveRange, (app::List_1_System_Type_ * this_ptr, int32_t index, int32_t count))
    IL2CPP_REGISTER_METHODINFO(0x04728290, List_1_System_Type__RemoveRange__MethodInfo)
}
