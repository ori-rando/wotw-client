#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Steamworks::SteamAPI {
    IL2CPP_REGISTER_METHOD(0x027E1F00, bool, Init, ())
    IL2CPP_REGISTER_METHOD(0x01600E60, void, Shutdown, ())
    IL2CPP_REGISTER_METHOD(0x01600EF0, bool, RestartAppIfNecessary, (app::AppId_t un_own_app_i_d))
    IL2CPP_REGISTER_METHOD(0x01600F90, void, ReleaseCurrentThreadMemory, ())
    IL2CPP_REGISTER_METHOD(0x016011C0, void, RunCallbacks, ())
    IL2CPP_REGISTER_METHOD(0x01601500, bool, IsSteamRunning, ())
    IL2CPP_REGISTER_METHOD(0x016016E0, app::HSteamUser, GetHSteamUserCurrent, ())
    IL2CPP_REGISTER_METHOD(0x01601800, app::HSteamPipe, GetHSteamPipe, ())
    IL2CPP_REGISTER_METHOD(0x01601930, app::HSteamUser, GetHSteamUser, ())
}
