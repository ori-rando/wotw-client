#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Linq::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ {
    IL2CPP_REGISTER_METHOD(0x02895170, void, ctor, (app::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ * this_ptr, app::IEnumerable_1_System_Int32Enum_ * source, app::Func_2_Int32Enum_Boolean_ * predicate, app::Func_2_Int32Enum_Single_ * selector))
    IL2CPP_REGISTER_METHOD(0x028951E0, app::Enumerable_Iterator_1_System_Single_ *, Clone, (app::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02898920, void, Dispose, (app::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x028989E0, bool, MoveNext, (app::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02896570, app::IEnumerable_1_System_Single_ *, Where, (app::Enumerable_WhereSelectEnumerableIterator_2_System_Int32Enum_System_Single_ * this_ptr, app::Func_2_Single_Boolean_ * predicate))
}
