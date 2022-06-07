#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Tuple_2_Object_Object_ {
    IL2CPP_REGISTER_METHOD(0x002FA280, app::Object *, get_Item1, (app::Tuple_2_Object_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FB930, app::Object *, get_Item2, (app::Tuple_2_Object_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x019E0910, void, ctor, (app::Tuple_2_Object_Object_ * this_ptr, app::Object * item1, app::Object * item2))
    IL2CPP_REGISTER_METHOD(0x02A677B0, bool, Equals, (app::Tuple_2_Object_Object_ * this_ptr, app::Object * obj))
    IL2CPP_REGISTER_METHOD(0x02A67890, bool, IStructuralEquatable_Equals, (app::Tuple_2_Object_Object_ * this_ptr, app::Object * other, app::IEqualityComparer * comparer))
    IL2CPP_REGISTER_METHOD(0x02A679B0, int32_t, IComparable_CompareTo, (app::Tuple_2_Object_Object_ * this_ptr, app::Object * obj))
    IL2CPP_REGISTER_METHOD(0x02A67A90, int32_t, IStructuralComparable_CompareTo, (app::Tuple_2_Object_Object_ * this_ptr, app::Object * other, app::IComparer * comparer))
    IL2CPP_REGISTER_METHODINFO(0x0477E1E8, Tuple_2_Object_Object__System_Collections_IStructuralComparable_CompareTo__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02A67C30, int32_t, GetHashCode, (app::Tuple_2_Object_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02A67D00, int32_t, IStructuralEquatable_GetHashCode, (app::Tuple_2_Object_Object_ * this_ptr, app::IEqualityComparer * comparer))
    IL2CPP_REGISTER_METHOD(0x02A67DD0, app::String *, ToString, (app::Tuple_2_Object_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02A67F50, app::String *, ITupleInternal_ToString, (app::Tuple_2_Object_Object_ * this_ptr, app::StringBuilder * sb))
}
