#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::CameraFilterPack_Vision_Aura {
    IL2CPP_REGISTER_METHOD(0x020F4260, app::Material *, get_material, (app::CameraFilterPack_Vision_Aura * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020F4440, void, Start, (app::CameraFilterPack_Vision_Aura * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020F45D0, void, OnRenderImage, (app::CameraFilterPack_Vision_Aura * this_ptr, app::RenderTexture * source_texture, app::RenderTexture * dest_texture))
    IL2CPP_REGISTER_METHOD(0x020F4A20, void, OnValidate, (app::CameraFilterPack_Vision_Aura * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020F4AD0, void, Update, (app::CameraFilterPack_Vision_Aura * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020F4BB0, void, OnDisable, (app::CameraFilterPack_Vision_Aura * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020F4C90, void, ctor, (app::CameraFilterPack_Vision_Aura * this_ptr))
}
