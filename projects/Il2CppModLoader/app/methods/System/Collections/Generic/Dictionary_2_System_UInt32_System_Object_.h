#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Collections::Generic::Dictionary_2_System_UInt32_System_Object_ {
    IL2CPP_REGISTER_METHOD(0x0283AC20, void, ctor_1, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02259DF0, void, ctor_2, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, int32_t capacity))
    IL2CPP_REGISTER_METHOD(0x0283AC50, void, ctor_3, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::IEqualityComparer_1_System_UInt32_ * comparer))
    IL2CPP_REGISTER_METHOD(0x02F02320, void, ctor_4, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, int32_t capacity, app::IEqualityComparer_1_System_UInt32_ * comparer))
    IL2CPP_REGISTER_METHODINFO(0x04722978, Dictionary_2_System_UInt32_System_Object___ctor_3__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0283ADC0, void, ctor_5, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::IDictionary_2_System_UInt32_System_Object_ * dictionary))
    IL2CPP_REGISTER_METHOD(0x02F02460, void, ctor_6, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::IDictionary_2_System_UInt32_System_Object_ * dictionary, app::IEqualityComparer_1_System_UInt32_ * comparer))
    IL2CPP_REGISTER_METHODINFO(0x0471E6F8, Dictionary_2_System_UInt32_System_Object___ctor_5__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F02820, void, ctor_7, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::SerializationInfo * info, app::StreamingContext context))
    IL2CPP_REGISTER_METHOD(0x002FB990, app::IEqualityComparer_1_System_UInt32_ *, get_Comparer, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B2A0, int32_t, get_Count, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B2B0, app::Dictionary_2_TKey_TValue_KeyCollection_System_UInt32_System_Object_ *, get_Keys, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B2B0, app::ICollection_1_System_UInt32_ *, System_Collections_Generic_IDictionary_TKey_TValue__get_Keys, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B2B0, app::IEnumerable_1_System_UInt32_ *, System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Keys, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B3E0, app::Dictionary_2_TKey_TValue_ValueCollection_System_UInt32_System_Object_ *, get_Values, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B3E0, app::ICollection_1_System_Object_ *, System_Collections_Generic_IDictionary_TKey_TValue__get_Values, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283B3E0, app::IEnumerable_1_System_Object_ *, System_Collections_Generic_IReadOnlyDictionary_TKey_TValue__get_Values, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02F028F0, app::Object *, get_Item, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key))
    IL2CPP_REGISTER_METHODINFO(0x0478A6E0, Dictionary_2_System_UInt32_System_Object__get_Item__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02BAC140, void, set_Item, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key, app::Object * value))
    IL2CPP_REGISTER_METHOD(0x02BAC170, void, Add, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key, app::Object * value))
    IL2CPP_REGISTER_METHOD(0x02BB8990, void, System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Add, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::KeyValuePair_2_System_UInt32_System_Object_ key_value_pair))
    IL2CPP_REGISTER_METHOD(0x02BB89C0, bool, System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Contains, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::KeyValuePair_2_System_UInt32_System_Object_ key_value_pair))
    IL2CPP_REGISTER_METHOD(0x02BB8AA0, bool, System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___Remove, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::KeyValuePair_2_System_UInt32_System_Object_ key_value_pair))
    IL2CPP_REGISTER_METHOD(0x0283B900, void, Clear, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02BA5090, bool, ContainsKey, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key))
    IL2CPP_REGISTER_METHOD(0x02BB8BA0, bool, ContainsValue, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * value))
    IL2CPP_REGISTER_METHOD(0x02F02A00, void, CopyTo, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::KeyValuePair_2_System_UInt32_System_Object___Array * array, int32_t index))
    IL2CPP_REGISTER_METHODINFO(0x04725A68, Dictionary_2_System_UInt32_System_Object__CopyTo__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02BA5400, app::Dictionary_2_TKey_TValue_Enumerator_System_UInt32_System_Object_, GetEnumerator, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02BA5450, app::IEnumerator_1_KeyValuePair_2_System_UInt32_System_Object_ *, System_Collections_Generic_IEnumerable_System_Collections_Generic_KeyValuePair_TKey_TValue___GetEnumerator, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02F02C50, void, GetObjectData, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::SerializationInfo * info, app::StreamingContext context))
    IL2CPP_REGISTER_METHODINFO(0x0474D790, Dictionary_2_System_UInt32_System_Object__GetObjectData__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F02E90, int32_t, FindEntry, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key))
    IL2CPP_REGISTER_METHODINFO(0x047607D0, Dictionary_2_System_UInt32_System_Object__FindEntry__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F030B0, void, Initialize, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, int32_t capacity))
    IL2CPP_REGISTER_METHOD(0x02F03210, bool, TryInsert, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key, app::Object * value, app::InsertionBehavior__Enum behavior))
    IL2CPP_REGISTER_METHODINFO(0x0475A898, Dictionary_2_System_UInt32_System_Object__TryInsert__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F038D0, void, OnDeserialization, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * sender))
    IL2CPP_REGISTER_METHODINFO(0x04782768, Dictionary_2_System_UInt32_System_Object__OnDeserialization__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F03CE0, void, Resize_1, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02F03DB0, void, Resize_2, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, int32_t new_size, bool force_new_hash_codes))
    IL2CPP_REGISTER_METHOD(0x02F04070, bool, Remove, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key))
    IL2CPP_REGISTER_METHODINFO(0x04742D38, Dictionary_2_System_UInt32_System_Object__Remove__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02BBA760, bool, TryGetValue, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key, app::Object * * value))
    IL2CPP_REGISTER_METHOD(0x02BAE050, bool, TryAdd, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, uint32_t key, app::Object * value))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___get_IsReadOnly, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283D900, void, System_Collections_Generic_ICollection_System_Collections_Generic_KeyValuePair_TKey_TValue___CopyTo, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::KeyValuePair_2_System_UInt32_System_Object___Array * array, int32_t index))
    IL2CPP_REGISTER_METHOD(0x02F04470, void, ICollection_CopyTo, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Array * array, int32_t index))
    IL2CPP_REGISTER_METHODINFO(0x047014A8, Dictionary_2_System_UInt32_System_Object__System_Collections_ICollection_CopyTo__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02BA5450, app::IEnumerator *, IEnumerable_GetEnumerator, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, ICollection_get_IsSynchronized, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02F04A00, app::Object *, ICollection_get_SyncRoot, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, IDictionary_get_IsFixedSize, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, IDictionary_get_IsReadOnly, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283E020, app::ICollection *, IDictionary_get_Keys, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0283E050, app::ICollection *, IDictionary_get_Values, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02BBAEE0, app::Object *, IDictionary_get_Item, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * key))
    IL2CPP_REGISTER_METHOD(0x02F04B60, void, IDictionary_set_Item, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * key, app::Object * value))
    IL2CPP_REGISTER_METHODINFO(0x04708070, Dictionary_2_System_UInt32_System_Object__System_Collections_IDictionary_set_Item__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F04E20, bool, IsCompatibleKey, (app::Object * key))
    IL2CPP_REGISTER_METHODINFO(0x047680A8, Dictionary_2_System_UInt32_System_Object__IsCompatibleKey__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02F04F20, void, IDictionary_Add, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * key, app::Object * value))
    IL2CPP_REGISTER_METHODINFO(0x04747220, Dictionary_2_System_UInt32_System_Object__System_Collections_IDictionary_Add__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x02BA7DD0, bool, IDictionary_Contains, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * key))
    IL2CPP_REGISTER_METHOD(0x02BA7EA0, app::IDictionaryEnumerator *, IDictionary_GetEnumerator, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02BA7F50, void, IDictionary_Remove, (app::Dictionary_2_System_UInt32_System_Object_ * this_ptr, app::Object * key))
}
