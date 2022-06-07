#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::Moon::AdditiveBodyRotation {
    IL2CPP_REGISTER_METHOD(0x013325F0, void, OnAddedToAnimator, (app::AdditiveBodyRotation * this_ptr, app::MoonAnimator * animator))
    IL2CPP_REGISTER_METHOD(0x003FF7B0, int32_t, get_Order, (app::AdditiveBodyRotation * this_ptr))
    IL2CPP_REGISTER_METHOD(0x013327B0, void, OnDrawGizmosSelected, (app::AdditiveBodyRotation * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01332CC0, void, Process, (app::AdditiveBodyRotation * this_ptr, float delta_time))
    IL2CPP_REGISTER_METHOD(0x01333330, void, ctor, (app::AdditiveBodyRotation * this_ptr))
}
