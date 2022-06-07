#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::DamagerAnimator {
    IL2CPP_REGISTER_METHOD(0x002FA000, void, CacheOriginals, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCA8A0, void, OnStartPlay, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCA8C0, void, OnStopPlay, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCA8E0, void, SampleValue, (app::DamagerAnimator * this_ptr, float value, bool force_sample))
    IL2CPP_REGISTER_METHOD(0x00DCAEB0, void, OnCollision, (app::DamagerAnimator * this_ptr, app::Collider * collider))
    IL2CPP_REGISTER_METHOD(0x00DCB630, app::EffectSpawn, ProvideDamageEffect, (app::DamagerAnimator * this_ptr, app::DamageResult result))
    IL2CPP_REGISTER_METHODINFO(0x0472FCE0, DamagerAnimator_ProvideDamageEffect__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x002FA000, void, RestoreToOriginalState, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCB6C0, float, get_Duration, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00417870, bool, get_IsLooping, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x003FFDF0, bool, TimelineActiveEditor, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCB6D0, void, ctor, (app::DamagerAnimator * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00DCB9B0, void, cctor, ())
}
