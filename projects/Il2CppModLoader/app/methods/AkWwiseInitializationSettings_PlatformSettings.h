#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::AkWwiseInitializationSettings_PlatformSettings {
    IL2CPP_REGISTER_METHOD(0x02706F50, void, IgnorePropertyValue, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::String * property_path))
    IL2CPP_REGISTER_METHOD(0x02707080, bool, IsPropertyIgnored, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::String * property_path))
    IL2CPP_REGISTER_METHOD(0x02707120, void, ctor, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr))
    IL2CPP_REGISTER_METHOD(0x02707380, void, SetUseGlobalPropertyValue, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::String * property_path, bool use))
    IL2CPP_REGISTER_METHOD(0x02707470, void, SetGlobalPropertyValues, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::IEnumerable * enumerable))
    IL2CPP_REGISTER_METHOD(0x027076A0, bool, IsUsingGlobalPropertyValue, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::String * property_path))
    IL2CPP_REGISTER_METHOD(0x02707740, app::HashSet_1_System_String_ *, get_GlobalPropertyHashSet, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FBB10, void, set_GlobalPropertyHashSet, (app::AkWwiseInitializationSettings_PlatformSettings * this_ptr, app::HashSet_1_System_String_ * value))
}
