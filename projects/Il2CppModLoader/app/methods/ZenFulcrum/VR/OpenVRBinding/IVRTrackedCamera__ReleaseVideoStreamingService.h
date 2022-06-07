#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::ZenFulcrum::VR::OpenVRBinding::IVRTrackedCamera__ReleaseVideoStreamingService {
    IL2CPP_REGISTER_METHOD(0x00611810, void, ctor, (app::IVRTrackedCamera_ReleaseVideoStreamingService * this_ptr, app::Object * object, void * method_1))
    IL2CPP_REGISTER_METHOD(0x00F55110, app::EVRTrackedCameraError__Enum, Invoke, (app::IVRTrackedCamera_ReleaseVideoStreamingService * this_ptr, uint64_t h_tracked_camera))
    IL2CPP_REGISTER_METHOD(0x00F55460, app::IAsyncResult *, BeginInvoke, (app::IVRTrackedCamera_ReleaseVideoStreamingService * this_ptr, uint64_t h_tracked_camera, app::AsyncCallback * callback, app::Object * object))
    IL2CPP_REGISTER_METHOD(0x00F550D0, app::EVRTrackedCameraError__Enum, EndInvoke, (app::IVRTrackedCamera_ReleaseVideoStreamingService * this_ptr, app::IAsyncResult * result))
}
