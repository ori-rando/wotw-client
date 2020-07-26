#include <macros.h>
#include <dll_main.h>
#include <uber_states/uber_state_manager.h>
 
#include <Il2CppModLoader/common.h>
#include <Il2CppModLoader/console.h>
#include <Il2CppModLoader/il2cpp_helpers.h>
#include <Il2CppModLoader/interception_macros.h>

INJECT_C_DLLEXPORT void teleport(float x, float y);

namespace
{
    enum class TeleportState
    {
        None,
        Teleport,
        PostTeleport
    };

    const app::Vector3 ORIGINAL_START = { -798.797058f, -4310.119141f, 0.f };
    bool overwrite_start = false;
    app::Vector3 start_position;

    TeleportState teleport_state = TeleportState::None;
    app::Vector3 teleport_position;

    bool handling_start = false;
    int cutscene_skips = 0;
    int ignore_count = 0;
    IL2CPP_BINDING(, SkipCutsceneController, void, SkipCutscene, (app::SkipCutsceneController* this_ptr));
    IL2CPP_BINDING(, SkipCutsceneController, void, SkipPrologue, (app::SkipCutsceneController* this_ptr));
    IL2CPP_BINDING(, SeinCharacter, app::Vector3, get_Position, (app::SeinCharacter* thisPtr));
    IL2CPP_INTERCEPT(, SeinCharacter, void, set_Position, (app::SeinCharacter* this_ptr, app::Vector3 value)) {
        if (ignore_count > 0)
            --ignore_count;
        else
            SeinCharacter::set_Position(this_ptr, value);
    }

    IL2CPP_BINDING(, GameplayCamera, void, MoveCameraToTargetInstantly, (app::GameplayCamera* this_ptr, bool updateTargetPosition));
    IL2CPP_INTERCEPT(, SeinCharacter, void, FixedUpdate, (app::SeinCharacter* this_ptr)) {
        // Don't teleport during cutscene skips, causes crashes.
        if (teleport_state == TeleportState::Teleport && cutscene_skips == 0)
        {
            modloader::console::console_send("called teleport");
            SeinCharacter::set_Position(this_ptr, teleport_position);
            teleport_state = TeleportState::PostTeleport;
        }
        else if (teleport_state == TeleportState::PostTeleport)
        {
            modloader::console::console_send("called post teleport");
            auto cameras = il2cpp::get_nested_class<app::UI_Cameras__Class>("Game", "UI", "Cameras");
            if (cameras != nullptr && cameras->static_fields->Current != nullptr)
            {
                // We need to do this on the next frame to allow state to update without causing flickering.
                auto camera = cameras->static_fields->Current;
                GameplayCamera::MoveCameraToTargetInstantly(camera, true);
            }
            else
                modloader::warn("teleport", "failed to refocus camera");

            teleport_state = TeleportState::None;
            handling_start = false;
        }

        if (cutscene_skips > 0)
        {
            auto controller = il2cpp::get_class<app::SkipCutsceneController__Class>("", "SkipCutsceneController")->static_fields->Instance;
            SkipCutsceneController::SkipCutscene(controller);
            --cutscene_skips;
        }

        SeinCharacter::FixedUpdate(this_ptr);
    }
;
    IL2CPP_INTERCEPT(, GameStateMachine, void, SetToPrologue, (app::GameStateMachine* this_ptr)) {
        GameStateMachine::SetToPrologue(this_ptr);
        handling_start = true;
        auto controller = il2cpp::get_class<app::SkipCutsceneController__Class>("", "SkipCutsceneController")->static_fields->Instance;
        SkipCutsceneController::SkipPrologue(controller);
        uber_states::set_uber_state_value(21786, 48748, 1);
        teleport_position = overwrite_start ? start_position : ORIGINAL_START;
        teleport_state = TeleportState::Teleport;
        // I hate this but required for nice looking transition here.
        cutscene_skips += 2;
    }

    IL2CPP_INTERCEPT(Moon.uberSerializationWisp, PlayerUberStateAreaMapInformation, void, SetAreaState,
        (app::PlayerUberStateAreaMapInformation* this_ptr, app::GameWorldAreaID__Enum area_id, int index, app::WorldMapAreaState__Enum state, app::Vector3 position)) {
        if (handling_start && state == app::WorldMapAreaState__Enum_Visited)
            state = app::WorldMapAreaState__Enum_Discovered;

        PlayerUberStateAreaMapInformation::SetAreaState(this_ptr, area_id, index, state, position);
    }
}

INJECT_C_DLLEXPORT void teleport(float x, float y)
{
    teleport_position = { x, y, 0.f };
    teleport_state = TeleportState::Teleport;
}

INJECT_C_DLLEXPORT void set_start_position(float x, float y)
{
    start_position = { x, y, 0.f };
    overwrite_start = true;
}

INJECT_C_DLLEXPORT void clear_start_position()
{
    overwrite_start = false;
}
