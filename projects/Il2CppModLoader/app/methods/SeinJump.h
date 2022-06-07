#pragma once
#include <Il2CppModLoader/interception_macros.h>

namespace app::methods::SeinJump {
    IL2CPP_REGISTER_METHOD(0x003FFDF0, bool, get_IsBlindForest, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00CBCC50, bool, get_PerformingSpringJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016070, void, set_PerformingSpringJump, (app::SeinJump * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x01016080, bool, get_AirDirectionFliped, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016100, bool, get_CanJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x005D06C0, app::CharacterPlatformMovement *, get_PlatformMovement, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00B39320, bool, get_SpriteMirrorLock, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016260, void, set_SpriteMirrorLock, (app::SeinJump * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x005D0720, app::CharacterSpriteMirror *, get_CharacterSpriteMirror, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016320, void, OnSetReferenceToSein, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010163F0, void, UpdateCharacterState, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010167D0, bool, HasGenericTurnTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016860, bool, HasCustomTurnTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016900, bool, DoesSpringJumpAllowTurn, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016950, bool, IsPlayingFlipAnim, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016970, void, ResetRunningJumpCount, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016980, void, ResetJumpIdleCount, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01016990, void, ForcePreviousDirection, (app::SeinJump * this_ptr, int32_t direction))
    IL2CPP_REGISTER_METHOD(0x010169A0, float, CalculateSpeedFromHeight, (app::SeinJump * this_ptr, float height))
    IL2CPP_REGISTER_METHOD(0x01016AA0, void, PerformTurnAroundBackFlipJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01017140, void, PerformBackflipJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0477EF28, SeinJump_PerformBackflipJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01017370, void, TransitionToFlipAnimation_1, (app::SeinJump * this_ptr, app::MoonAnimation * prev_anim_type, app::MoonAnimation * new_anim_type, app::Func_1_Boolean_ * should_anim_keep_playing, bool inherit_normalized_time, app::ActiveAnimationHandle * new_anim))
    IL2CPP_REGISTER_METHOD(0x01017540, void, TransitionToFlipAnimation_2, (app::GenericPuppet * puppet, app::MoonAnimation * prev_anim_type, app::MoonAnimation * new_anim_type, app::Func_1_Boolean_ * should_anim_keep_playing, bool inherit_normalized_time, int32_t anim_layer, app::Action * on_anim_start, app::Action * on_anim_end, app::ActiveAnimationHandle * new_anim))
    IL2CPP_REGISTER_METHOD(0x010177D0, void, TransitionToFlipAnimationIndexed_1, (app::SeinJump * this_ptr, app::MoonAnimation * prev_anim_type, app::MoonAnimation__Array * new_anim_type, int32_t index, app::Func_1_Boolean_ * should_anim_keep_playing, bool inherit_normalized_time, app::ActiveAnimationHandle * new_anim))
    IL2CPP_REGISTER_METHOD(0x010179B0, void, TransitionToFlipAnimationIndexed_2, (app::GenericPuppet * puppet, app::MoonAnimation * prev_anim_type, app::MoonAnimation__Array * new_anim_type, int32_t index, app::Func_1_Boolean_ * should_anim_keep_playing, bool inherit_normalized_time, int32_t anim_layer, app::Action * on_anim_start, app::Action * on_anim_end, app::ActiveAnimationHandle * new_anim))
    IL2CPP_REGISTER_METHOD(0x01017BB0, void, PerformJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01018500, void, PerformSpringJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010189B0, float, get_TimeSinceLastJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010189C0, void, PerformRunningJump_1, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01018A00, void, CacheDelegates, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01018C50, void, PerformRunningJump_2, (app::SeinJump * this_ptr, int32_t jump_index, float jump_height, float jump_sustain_mul, app::SurfaceToSoundProviderMap * sound_provider))
    IL2CPP_REGISTER_METHOD(0x01018FA0, void, PerformFirstRunningJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01019150, void, PerformSecondRunningJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x01019320, void, PerformThirdRunningJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010194E0, void, PerformGenericJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04795BF0, SeinJump_PerformGenericJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x01016860, bool, CanPerformCurrentJumpCustomTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x010199E0, float, GetCurrentEarlyFlipTime, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101A0D0, bool, CanPerformBashCustomTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101A320, void, PerformJumpFlipTransition, (app::SeinJump * this_ptr, app::MoonAnimation__Array * flip_early_anims, int32_t jump_index, float early_flip_time))
    IL2CPP_REGISTER_METHOD(0x0101A4B0, void, PerformFirstRunningJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0472C400, SeinJump_PerformFirstRunningJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101A520, void, PerformSecondRunningJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04745588, SeinJump_PerformSecondRunningJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101A590, void, PerformThirdRunningJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04712CC0, SeinJump_PerformThirdRunningJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101A600, void, PerformIdleJump_1, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101A640, void, PerformIdleJump_2, (app::SeinJump * this_ptr, int32_t jump_index, float jump_height, app::SurfaceToSoundProviderMap * sound_provider))
    IL2CPP_REGISTER_METHOD(0x0101A9E0, void, PerformFirstIdleJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101AB90, void, PerformSecondIdleJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101AD40, void, PerformThirdIldleJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101AEF0, void, PerformJumpFlipIdleTransition, (app::SeinJump * this_ptr, int32_t jump_index))
    IL2CPP_REGISTER_METHOD(0x0101B0F0, void, PerformFirstJumpIdleFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04722F98, SeinJump_PerformFirstJumpIdleFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101B100, void, PerformSecondJumpFlipIdleTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04788710, SeinJump_PerformSecondJumpFlipIdleTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101B110, void, PerformThirdJumpFlipIdleTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04783B90, SeinJump_PerformThirdJumpFlipIdleTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101B120, void, PerformWallSlideJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101B680, void, PerformWallSlideJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04731C90, SeinJump_PerformWallSlideJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101B850, void, PerformCrouchJump, (app::SeinJump * this_ptr, bool * jumped_down_though_platform))
    IL2CPP_REGISTER_METHOD(0x0101C420, void, PerformCrouchJumpFlipTransition, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x047811A0, SeinJump_PerformCrouchJumpFlipTransition__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x005E1300, bool, ShouldBackflipAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04791A80, SeinJump_ShouldBackflipAnimationKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x005E1300, bool, ShouldSpringJumpAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04707508, SeinJump_ShouldSpringJumpAnimationKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x005E1300, bool, ShouldJumpIdleAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04730D58, SeinJump_ShouldJumpIdleAnimationKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101C650, bool, ShouldJumpIdleFlipTransitionKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04744708, SeinJump_ShouldJumpIdleFlipTransitionKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101C860, bool, ShouldWallSlideJumpAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0477E118, SeinJump_ShouldWallSlideJumpAnimationKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101C9D0, bool, ShouldJumpMovingAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0470ABB0, SeinJump_ShouldJumpMovingAnimationKeepPlaying__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x005E1300, bool, ShouldThirdJumpMovingAnimationKeepPlaying, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101CD20, void, add_OnJumpEvent, (app::SeinJump * this_ptr, app::Action_1_Single_ * value))
    IL2CPP_REGISTER_METHOD(0x0101CE10, void, remove_OnJumpEvent, (app::SeinJump * this_ptr, app::Action_1_Single_ * value))
    IL2CPP_REGISTER_METHOD(0x008775B0, void, OnAnimationEnd, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04767AB0, SeinJump_OnAnimationEnd__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x002FA000, void, OnAnimationStart, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0476D880, SeinJump_OnAnimationStart__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101CF00, void, UseGenericJumpFlipTransitionAsDefault, (app::SeinJump * this_ptr, app::Component_1 * client, bool use))
    IL2CPP_REGISTER_METHOD(0x008A60A0, void, ResetTimeSinceLastJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x008760C0, void, UseSpecificJumpFlipTransition, (app::SeinJump * this_ptr, app::Action * action))
    IL2CPP_REGISTER_METHOD(0x0101D000, void, FlipTurnAnimationStart, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04735468, SeinJump_FlipTurnAnimationStart__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x008775B0, void, FlipTurnAnimationEnd, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04742C60, SeinJump_FlipTurnAnimationEnd__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x002FA000, void, SpringJumpAnimationStart, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04738FA8, SeinJump_SpringJumpAnimationStart__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x008775B0, void, SpringJumpAnimationStop, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0474EF10, SeinJump_SpringJumpAnimationStop__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101D160, bool, CanUseTurningHandler, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D2A0, bool, get_HasStartedTurning, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D2D0, bool, get_HasFinishedTurning, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00A5BA30, bool, get_WantsToFaceLeft, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D2F0, void, set_WantsToFaceLeft, (app::SeinJump * this_ptr, bool value))
    IL2CPP_REGISTER_METHOD(0x0101D300, bool, get_ShouldInterruptTurning, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D320, bool, get_IsCancellable, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D340, void, InterruptTurning, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D360, void, Turn, (app::SeinJump * this_ptr, bool face_left))
    IL2CPP_REGISTER_METHOD(0x0101D340, void, OnWallJump, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04757A00, SeinJump_OnWallJump__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101D3F0, void, Serialize, (app::SeinJump * this_ptr, app::Archive * ar))
    IL2CPP_REGISTER_METHOD(0x0101D490, void, OnAwake, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D630, void, OnDestroy, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D7E0, void, OnEnable, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101D9C0, void, OnDisable, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x00B3A3B0, void, OnRestoreCheckpoint, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04750FA8, SeinJump_OnRestoreCheckpoint__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x0101DBB0, app::OriJumpPuppet *, get_Puppet, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101DC70, void, ctor, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHOD(0x0101DF70, bool, _PerformGenericJumpFlipTransition_b__66_0, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x0475FBC8, SeinJump__PerformGenericJumpFlipTransition_b__66_0__MethodInfo)
    IL2CPP_REGISTER_METHOD(0x005E1300, bool, _PerformCrouchJump_b__85_0, (app::SeinJump * this_ptr))
    IL2CPP_REGISTER_METHODINFO(0x04752848, SeinJump__PerformCrouchJump_b__85_0__MethodInfo)
}
