#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::MixerSnapshotZone {
    IL2CPP_REGISTER_METHOD(0x0132EE60, app::Bounds, get_Bounds, (app::MixerSnapshotZone * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0132F070, void, OnEnable, (app::MixerSnapshotZone * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0132F1B0, void, OnDisable, (app::MixerSnapshotZone * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0132F340, void, UpdateSnapshotZoneState, (app::MixerSnapshotZone * this_ptr, bool is_zone_active))
    IL2CPP_REGISTER_METHOD(0x003F8A60, void, ctor, (app::MixerSnapshotZone * this_ptr))
}
