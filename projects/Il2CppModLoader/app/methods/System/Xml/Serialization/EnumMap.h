#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Xml::Serialization::EnumMap {
    IL2CPP_REGISTER_METHOD(0x01C8D8C0, void, ctor, (app::EnumMap * this_ptr, app::EnumMap_EnumMapMember__Array * members, bool is_flags))
    IL2CPP_REGISTER_METHOD(0x0052A280, bool, get_IsFlags, (app::EnumMap * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FB950, app::String__Array *, get_EnumNames, (app::EnumMap * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FBB00, app::String__Array *, get_XmlNames, (app::EnumMap * this_ptr))
    IL2CPP_REGISTER_METHOD(0x002FB990, app::Int64__Array *, get_Values, (app::EnumMap * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01C8DB40, app::String *, GetXmlName, (app::EnumMap * this_ptr, app::String * type_name, app::Object * enum_value))
    IL2CPP_REGISTER_METHODINFO(0x0475DDB0, EnumMap_GetXmlName__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01C8DEA0, app::String *, GetEnumName, (app::EnumMap * this_ptr, app::String * type_name, app::String * xml_name))
    IL2CPP_REGISTER_METHODINFO(0x0470D6A8, EnumMap_GetEnumName__MethodInfo)
}
