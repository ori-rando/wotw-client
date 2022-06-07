#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::UnityEngine::TerrainData {
    IL2CPP_REGISTER_METHOD(0x0319A460, void, ctor, (app::TerrainData_1 * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0319A550, int32_t, GetBoundaryValue, (app::TerrainData_BoundaryValueType__Enum type))
    IL2CPP_REGISTER_METHOD(0x0319A5A0, void, Internal_Create, (app::TerrainData_1 * terrain_data))
    IL2CPP_REGISTER_METHOD(0x0319A5F0, app::Vector3, get_size, (app::TerrainData_1 * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0319A670, float, GetAlphamapResolutionInternal, (app::TerrainData_1 * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0319A6C0, void, cctor, ())
    IL2CPP_REGISTER_METHOD(0x0319A9F0, void, get_size_Injected, (app::TerrainData_1 * this_ptr, app::Vector3 * ret))
}
