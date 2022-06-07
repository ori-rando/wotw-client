#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::CageTextureMaker {
    IL2CPP_REGISTER_METHOD(0x00CC0780, app::Material *, get_baseMaterial, ())
    IL2CPP_REGISTER_METHOD(0x00CC0980, app::Material *, get_strokeMaterial, ())
    IL2CPP_REGISTER_METHOD(0x00CC0B80, app::Mesh *, get_QuadMesh, ())
    IL2CPP_REGISTER_METHOD(0x00CC1150, app::Texture2D *, CreateTexture, (app::Bounds bounds, app::Mesh * mesh, app::Transform * cage_structure_transform))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, ctor, (app::CageTextureMaker * this_ptr))
}
