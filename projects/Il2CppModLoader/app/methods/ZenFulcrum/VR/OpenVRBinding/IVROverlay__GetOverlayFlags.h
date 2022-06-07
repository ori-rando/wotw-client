#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::ZenFulcrum::VR::OpenVRBinding::IVROverlay__GetOverlayFlags {
    IL2CPP_REGISTER_METHOD(0x00611810, void, ctor, (app::IVROverlay_GetOverlayFlags * this_ptr, app::Object * object, void * method_1))
    IL2CPP_REGISTER_METHOD(0x02188B40, app::EVROverlayError__Enum, Invoke, (app::IVROverlay_GetOverlayFlags * this_ptr, uint64_t ul_overlay_handle, uint32_t * p_flags))
    IL2CPP_REGISTER_METHOD(0x02D7AC10, app::IAsyncResult *, BeginInvoke, (app::IVROverlay_GetOverlayFlags * this_ptr, uint64_t ul_overlay_handle, uint32_t * p_flags, app::AsyncCallback * callback, app::Object * object))
    IL2CPP_REGISTER_METHOD(0x00F51FA0, app::EVROverlayError__Enum, EndInvoke, (app::IVROverlay_GetOverlayFlags * this_ptr, uint32_t * p_flags, app::IAsyncResult * result))
}
