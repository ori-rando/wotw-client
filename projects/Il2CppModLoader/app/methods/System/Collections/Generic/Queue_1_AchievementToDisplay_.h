#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Collections::Generic::Queue_1_AchievementToDisplay_ {
    IL2CPP_REGISTER_METHOD(0x002FD1D0, int32_t, get_Count, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0472E280, Queue_1_AchievementToDisplay__get_Count__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243D360, app::AchievementToDisplay, Dequeue, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04776788, Queue_1_AchievementToDisplay__Dequeue__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243D1B0, void, Enqueue, (app::Queue_1_AchievementToDisplay_ * this_ptr, app::AchievementToDisplay item))
    IL2CPP_REGISTER_METHODINFO(0x04724940, Queue_1_AchievementToDisplay__Enqueue__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243CE40, void, Clear, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04795068, Queue_1_AchievementToDisplay__Clear__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243CB70, void, ctor_1, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04795C80, Queue_1_AchievementToDisplay___ctor__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243CBB0, void, ctor_2, (app::Queue_1_AchievementToDisplay_ * this_ptr, int32_t capacity))
    IL2CPP_REGISTER_METHODINFO(0x047303F0, Queue_1_AchievementToDisplay___ctor_1__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x00417870, bool, ICollection_get_IsSynchronized, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243CCE0, app::Object *, ICollection_get_SyncRoot, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243CEB0, void, ICollection_CopyTo, (app::Queue_1_AchievementToDisplay_ * this_ptr, app::Array * array, int32_t index))
    IL2CPP_REGISTER_METHODINFO(0x0476A648, Queue_1_AchievementToDisplay__System_Collections_ICollection_CopyTo__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0243D290, app::Queue_1_T_Enumerator_AchievementToDisplay_, GetEnumerator, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243D2D0, app::IEnumerator_1_AchievementToDisplay_ *, System_Collections_Generic_IEnumerable_T__GetEnumerator, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243D2D0, app::IEnumerator *, IEnumerable_GetEnumerator, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243D430, app::AchievementToDisplay, Peek, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243D4B0, bool, Contains, (app::Queue_1_AchievementToDisplay_ * this_ptr, app::AchievementToDisplay item))
    IL2CPP_REGISTER_METHOD(0x0243D5D0, app::AchievementToDisplay__Array *, ToArray, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0243D6C0, void, SetCapacity, (app::Queue_1_AchievementToDisplay_ * this_ptr, int32_t capacity))
    IL2CPP_REGISTER_METHOD(0x0243D7A0, void, MoveNext, (app::Queue_1_AchievementToDisplay_ * this_ptr, int32_t * index))
    IL2CPP_REGISTER_METHOD(0x0243D7D0, void, ThrowForEmptyQueue, (app::Queue_1_AchievementToDisplay_ * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x047434B0, Queue_1_AchievementToDisplay__ThrowForEmptyQueue__MethodInfo)
}
