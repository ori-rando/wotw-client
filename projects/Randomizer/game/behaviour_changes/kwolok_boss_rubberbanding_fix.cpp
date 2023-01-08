#include <Common/ext.h>
#include <Modloader/app/methods/Moon/ScalableAnimationPlayer_ScalingInterval.h>
#include <Modloader/app/types/ScalableAnimationPlayer.h>
#include <Modloader/app/types/ScalableAnimationPlayer_ScalingInterval.h>
#include <Modloader/common.h>
#include <Modloader/interception_macros.h>
#include <Core/utils/event_bus.h>
#include <Core/api/scenes/scene_load.h>

using namespace modloader;
using namespace app::classes;

namespace {
    void on_scene_load(scenes::SceneLoadEventMetadata* metadata, EventTiming timing) {
        if (metadata->state != app::SceneState__Enum::Loaded) {
            return;
        }

        if (metadata->scene_name == "kwolokBossChaseBG") {
            auto scene_root_go = il2cpp::unity::get_game_object(metadata->scene->fields.SceneRoot);

            auto timeline_go = il2cpp::unity::find_child(
                    scene_root_go,
                    std::vector<std::string>{
                            "kwolokBossSetup",
                            "kwolok",
                            "timelines",
                            "escape",
                            "stinkSpiritScalableAnimation" }
            );

            if (il2cpp::unity::is_valid(timeline_go)) {
                auto scalable_animation_player = il2cpp::unity::get_component<app::ScalableAnimationPlayer>(timeline_go, types::ScalableAnimationPlayer::get_class());

                // Moon why
                auto interval = types::ScalableAnimationPlayer_ScalingInterval::create();
                Moon::ScalableAnimationPlayer_ScalingInterval::ctor(interval);
                interval->fields.NormalizedStart = 0.f;
                interval->fields.NormalizedDuration = 1.f;

                il2cpp::invoke(scalable_animation_player->fields.ScalingAllowedIntervals, "Add", interval);
            }
        }
    }

    void initialize() {
        scenes::event_bus().register_handler(&on_scene_load);
    }

    CALL_ON_INIT(initialize);
} // namespace
