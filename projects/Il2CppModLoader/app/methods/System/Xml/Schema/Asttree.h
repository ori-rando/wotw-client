#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::System::Xml::Schema::Asttree {
    IL2CPP_REGISTER_METHOD(0x002FA280, app::ArrayList *, get_SubtreeArray, (app::Asttree * this_ptr))
    IL2CPP_REGISTER_METHOD(0x019A16D0, void, ctor, (app::Asttree * this_ptr, app::String * x_path, bool is_field, app::XmlNamespaceManager * nsmgr))
    IL2CPP_REGISTER_METHOD(0x019A16F0, bool, IsNameTest, (app::Axis * ast))
    IL2CPP_REGISTER_METHOD(0x019A1720, bool, IsAttribute, (app::Axis * ast))
    IL2CPP_REGISTER_METHOD(0x019A1750, bool, IsDescendantOrSelf, (app::Axis * ast))
    IL2CPP_REGISTER_METHOD(0x019A1780, bool, IsSelf, (app::Axis * ast))
    IL2CPP_REGISTER_METHOD(0x019A17B0, void, CompileXPath, (app::Asttree * this_ptr, app::String * x_path, bool is_field, app::XmlNamespaceManager * nsmgr))
    IL2CPP_REGISTER_METHODINFO(0x0474A0E8, Asttree_CompileXPath__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x019A2340, void, SetURN, (app::Asttree * this_ptr, app::Axis * axis, app::XmlNamespaceManager * nsmgr))
    IL2CPP_REGISTER_METHODINFO(0x0470C328, Asttree_SetURN__MethodInfo)
}
