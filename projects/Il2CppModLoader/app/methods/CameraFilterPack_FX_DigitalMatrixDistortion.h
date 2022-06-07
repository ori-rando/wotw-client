#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::CameraFilterPack_FX_DigitalMatrixDistortion {
    IL2CPP_REGISTER_METHOD(0x0246A8A0, app::Material *, get_material, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0246AA80, void, Start, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0246ABF0, void, OnRenderImage, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr, app::RenderTexture * source_texture, app::RenderTexture * dest_texture))
    IL2CPP_REGISTER_METHOD(0x0246AF90, void, OnValidate, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0246B020, void, Update, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0246B0B0, void, OnDisable, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0246B190, void, ctor, (app::CameraFilterPack_FX_DigitalMatrixDistortion * this_ptr))
}
