#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::AkAcousticSurfaceArray {
    IL2CPP_REGISTER_METHOD(0x026C4F40, void, ctor, (app::AkAcousticSurfaceArray * this_ptr, int32_t count))
    IL2CPP_REGISTER_METHOD(0x026C4FD0, int32_t, get_StructureSize, (app::AkAcousticSurfaceArray * this_ptr))
    IL2CPP_REGISTER_METHOD(0x026C5060, void, DefaultConstructAtIntPtr, (app::AkAcousticSurfaceArray * this_ptr, void * address))
    IL2CPP_REGISTER_METHOD(0x026C5100, app::AkAcousticSurface *, CreateNewReferenceFromIntPtr, (app::AkAcousticSurfaceArray * this_ptr, void * address))
    IL2CPP_REGISTER_METHOD(0x026C5250, void, CloneIntoReferenceFromIntPtr, (app::AkAcousticSurfaceArray * this_ptr, void * address, app::AkAcousticSurface * other))
}
