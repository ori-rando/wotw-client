#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::Rendering::RenderScopeExtensions {
    IL2CPP_REGISTER_METHOD(0x00EB1A50, bool, match, (app::RenderScope__Enum scope, app::MoonRenderPipelineViewType__Enum type))
    IL2CPP_REGISTER_METHODINFO(0x04787590, RenderScopeExtensions_match__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x00EB1B80, bool, hasFlag, (app::RenderScope__Enum value, app::RenderScope__Enum flag))
    IL2CPP_REGISTER_METHOD(0x00EB1B90, app::RenderScope__Enum, setFlag, (app::RenderScope__Enum scope, app::RenderScope__Enum flag, bool on))
}
