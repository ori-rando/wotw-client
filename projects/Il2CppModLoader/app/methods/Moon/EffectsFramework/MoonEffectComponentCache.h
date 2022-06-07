#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::EffectsFramework::MoonEffectComponentCache {
    IL2CPP_REGISTER_METHOD(0x002FA280, app::GameObject *, get_Target, (app::MoonEffectComponentCache * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01980470, void, ctor, (app::MoonEffectComponentCache * this_ptr, app::GameObject * target, app::Type__Array * component_types))
    IL2CPP_REGISTER_METHOD(0x019808B0, app::List_1_UnityEngine_Component_ *, GetAllComponentsOfType_1, (app::MoonEffectComponentCache * this_ptr, app::Type * type))
    IL2CPP_REGISTER_METHOD(0x01EB8D30, app::List_1_System_Object_ *, GetAllComponentsOfType_2, (app::MoonEffectComponentCache * this_ptr))
}
