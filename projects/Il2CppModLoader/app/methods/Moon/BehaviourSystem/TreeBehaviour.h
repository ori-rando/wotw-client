#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::BehaviourSystem::TreeBehaviour {
    IL2CPP_REGISTER_METHOD(0x030120C0, void, OnValidate, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0217ACC0, app::String *, get_Info, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x03012130, bool, get_IsDisabled, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00446980, void, set_IsDisabled, (app::TreeBehaviour * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x030121B0, bool, get_IsEnabled, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x030121C0, void, set_IsEnabled, (app::TreeBehaviour * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, PerformSanityCheck, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, OnBeforeSerialize, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, OnAfterDeserialize, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x006771B0, void, ctor, (app::TreeBehaviour * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0153EFF0, app::String *, EditorResolveToString_1, (app::IMoonType_1_System_Object_ * moon_type))
    IL2CPP_REGISTER_METHOD(0x0153EA00, app::String *, EditorResolveToString_2, (app::IMoonType_1_System_Boolean_ * moon_type))
    IL2CPP_REGISTER_METHODINFO(0x0478A918, TreeBehaviour_EditorResolveToString_1__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0153F570, app::String *, EditorResolveToString_3, (app::IMoonType_1_UnityEngine_Vector3_ * moon_type))
    IL2CPP_REGISTER_METHODINFO(0x04754928, TreeBehaviour_EditorResolveToString_2__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0153F290, app::String *, EditorResolveToString_4, (app::IMoonType_1_System_Single_ * moon_type))
    IL2CPP_REGISTER_METHODINFO(0x0472AC90, TreeBehaviour_EditorResolveToString_3__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0153ECF0, app::String *, EditorResolveToString_5, (app::IMoonType_1_System_Int32_ * moon_type))
    IL2CPP_REGISTER_METHODINFO(0x04741AC8, TreeBehaviour_EditorResolveToString_4__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0153EFF0, app::String *, EditorResolveToString_6, (app::IMoonType_1_UnityEngine_GameObject_ * moon_type))
    IL2CPP_REGISTER_METHODINFO(0x0474F480, TreeBehaviour_EditorResolveToString_5__MethodInfo)
}
