#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::RestartOneLifeMode {
    IL2CPP_REGISTER_METHOD(0x0090A9D0, void, Perform, (app::RestartOneLifeMode * this_ptr, app::IContext * context))
    IL2CPP_REGISTER_METHOD(0x0090ACD0, app::IEnumerator *, RestartingCleanupNextFrame, (app::RestartOneLifeMode * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0044C850, void, ctor, (app::RestartOneLifeMode * this_ptr))
}
