#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::CameraFilterPack_TV_Chromatical {
    IL2CPP_REGISTER_METHOD(0x020E7110, app::Material *, get_material, (app::CameraFilterPack_TV_Chromatical * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020E72F0, void, Start, (app::CameraFilterPack_TV_Chromatical * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020E7440, void, OnRenderImage, (app::CameraFilterPack_TV_Chromatical * this_ptr, app::RenderTexture * source_texture, app::RenderTexture * dest_texture))
    IL2CPP_REGISTER_METHOD(0x002FA000, void, Update, (app::CameraFilterPack_TV_Chromatical * this_ptr))
    IL2CPP_REGISTER_METHOD(0x020E77B0, void, OnDisable, (app::CameraFilterPack_TV_Chromatical * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0136E200, void, ctor, (app::CameraFilterPack_TV_Chromatical * this_ptr))
}
