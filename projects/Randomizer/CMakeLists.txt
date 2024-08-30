project("Randomizer")
string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)

message(STATUS "")
message(STATUS "Project ${PROJECT_NAME}:")

set(PROJECT_DIR ${WOTWR_PROJECTS_DIR}/${PROJECT_NAME})

set(
        SOURCE_FILES
        "archipelago/archipelago.cpp"
        "archipelago/archipelago_ids.cpp"
        "archipelago/archipelago_protocol.cpp"
        "archipelago/archipelago_save_meta.cpp"
        "conditions/condition_override.cpp"
        "conditions/condition_uber_state.cpp"
        "conditions/new_setup_state_override.cpp"
        "conditions/targeting_override.cpp"
        "dev/console_seed_debugger.cpp"
        "dev/cpp_seed_debugger.cpp"
        "dev/log_seed_debugger.cpp"
        "dev/seed_debugger.cpp"
        "features/area_segment_states.cpp"
        "features/better_menus.cpp"
        "features/controls/ability_overrides.cpp"
        "features/controls/air_no_deceleration.cpp"
        "features/controls/autoaim.cpp"
        "features/controls/hold_to_skip_dialog.cpp"
        "features/controls/invert_swim.cpp"
        "features/controls/launch_no_deceleration.cpp"
        "features/controls/mouse_control.cpp"
        "features/credits.cpp"
        "features/custom_fire_sources.cpp"
        "features/cutscene_skips/custom_cutscene_skips.cpp"
        "features/cutscene_skips/final_cutscene.cpp"
        "features/cutscene_skips/kwolok_boss_farewell.cpp"
        "features/cutscene_skips/kwolok_boss_intro.cpp"
        "features/cutscene_skips/mora_start.cpp"
        "features/cutscene_skips/reach_escape.cpp"
        "features/cutscene_skips/sandworm_end.cpp"
        "features/cutscene_skips/sandworm_start.cpp"
        "features/cutscene_skips/wellspring_escape_start.cpp"
        "features/cutscene_skips/wellspring_so_soggy.cpp"
        "features/cutscene_skips/willow_heart_cutscenes.cpp"
        "features/mini_map/mini_map.cpp"
        "features/difficulty.cpp"
        "features/keyboard_multibind.cpp"
        "features/keystone_door.cpp"
        "features/knock_knock_wellspring.cpp"
        "features/map.cpp"
        "features/npcs/lupo_everywhere.cpp"
        "features/npcs/opher_everywhere.cpp"
        "features/npcs/tokk_everywhere.cpp"
        "features/npcs/twillen_everywhere.cpp"
        "features/recording_utils.cpp"
        "features/scenes/modifications/double_jump_spring.cpp"
        "features/scenes/modifications/hornbug_arena_allow_teleportation.cpp"
        "features/scenes/modifications/keep_epilogue_loaded_during_shriek_escape.cpp"
        "features/scenes/modifications/kwolok_escape_sl_softlock_fix.cpp"
        "features/scenes/modifications/kwolok_escape_start_allow_teleportation.cpp"
        "features/scenes/modifications/load_wellspring_bottom_floor_center_path_earlier.cpp"
        "features/scenes/modifications/luma_fight_room_door_always_open.cpp"
        "features/scenes/modifications/marsh_burrow_fight_arena_allow_teleportation.cpp"
        "features/scenes/modifications/meeting_kwolok_cutscene_trigger_underwater_fix.cpp"
        "features/scenes/modifications/reactive_bone_bridge_state.cpp"
        "features/scenes/modifications/ruins_escape_allow_teleportation.cpp"
        "features/scenes/modifications/sandless_feeding_grounds_to_elevator.cpp"
        "features/scenes/modifications/sandless_shriek_escape.cpp"
        "features/secrets.cpp"
        "features/sentry_burn_damage_type_fix.cpp"
        "features/shrine_states.cpp"
        "features/trackers/ability_tracker.cpp"
        "features/trackers/goal_mode_check.cpp"
        "features/trial_texts.cpp"
        "features/wheel.cpp"
        "features/wheel_initialization.cpp"
        "game/behaviour_changes/allow_blind_forest_abilities.cpp"
        "game/behaviour_changes/alternative_baurs_reach_access.cpp"
        "game/behaviour_changes/better_lasers.cpp"
        "game/behaviour_changes/blaze_hit_environment.cpp"
        "game/behaviour_changes/burrow_and_waterdash_without_dash.cpp"
        "game/behaviour_changes/dash_stomper_fall_through.cpp"
        "game/behaviour_changes/deflector_without_bash.cpp"
        "game/behaviour_changes/faster_teleportation.cpp"
        "game/behaviour_changes/feeding_grounds_allow_burrow.cpp"
        "game/behaviour_changes/fix_kwolok_not_stopping_when_abandoning_challenge.cpp"
        "game/behaviour_changes/fix_shop_anywhere.cpp"
        "game/behaviour_changes/fix_straight_grenades.cpp"
        "game/behaviour_changes/flap_without_glide.cpp"
        "game/behaviour_changes/instant_tp_activation.cpp"
        "game/behaviour_changes/keep_shriek_health_bar_visible.cpp"
        "game/behaviour_changes/kwolok_boss_rubberbanding_fix.cpp"
        "game/behaviour_changes/luma_contact_switch_door_jank_fix.cpp"
        "game/behaviour_changes/patch2_kickback.cpp"
        "game/behaviour_changes/prevent_pickup.cpp"
        "game/behaviour_changes/stomp_into_water.cpp"
        "game/behaviour_changes/stomp_through_portals.cpp"
        "game/behaviour_changes/teleport_restriction.cpp"
        "game/behaviour_changes/teleporter_glades_identifier.cpp"
        "game/behaviour_changes/teleporter_map_activation.cpp"
        "game/behaviour_changes/teleporting_oob_fix.cpp"
        "game/behaviour_changes/luma_trial_bubbles.cpp"
        "game/behaviour_changes/trials_leaderboards.cpp"
        "game/behaviour_changes/triple_jump_shockwave.cpp"
        "game/condition_intercepts/day_night_logic.cpp"
        "game/condition_intercepts/good_hollow.cpp"
        "game/condition_intercepts/grom_built_tps.cpp"
        "game/condition_intercepts/grom_projects.cpp"
        "game/condition_intercepts/tuley_switch.cpp"
        "game/condition_intercepts/water.cpp"
        "game/event_handlers/on_area_map.cpp"
        "game/event_handlers/on_save.cpp"
        "game/event_handlers/on_teleport.cpp"
        "game/event_handlers/on_trial.cpp"
        "game/camera_shake.cpp"
        "game/map/filter.cpp"
        "game/map/icon.cpp"
        "game/map/map.cpp"
        "game/map/map_initialization.cpp"
        "game/map/player_color.cpp"
        "game/map/teleport_anywhere.cpp"
        "game/map/tree_visibility_fix.cpp"
        "game/music.cpp"
        "game/pickups/bonus/grenade.cpp"
        "game/pickups/bonus/bow_attack_speed.cpp"
        "game/pickups/bonus/energy_cost_upgrades.cpp"
        "game/pickups/bonus/energy_regeneration.cpp"
        "game/pickups/bonus/extra_ability_activations.cpp"
        "game/pickups/bonus/extra_shurikens.cpp"
        "game/pickups/bonus/hammer_attack_speed.cpp"
        "game/pickups/bonus/health_regeneration.cpp"
        "game/pickups/bonus/regenerate_speed.cpp"
        "game/pickups/bonus/sentry_upgrades.cpp"
        "game/pickups/bonus/spear_attack_speed.cpp"
        "game/pickups/bonus/sword_attack_speed.cpp"
        "game/pickups/bonus/velocity.cpp"
        "game/pickups/bonus/flash.cpp"
        "game/pickups/pickups.cpp"
        "game/pickups/quests.cpp"
        "game/pickups/spirit_shard.cpp"
        "game/pickups/tree.cpp"
        "game/shops/fast_purchase.cpp"
        "game/shops/general.cpp"
        "game/shops/grom.cpp"
        "game/shops/lupo.cpp"
        "game/shops/lupo_dont_open_map.cpp"
        "game/shops/opher.cpp"
        "game/shops/shop.cpp"
        "game/shops/spirit_light_spent.cpp"
        "game/shops/tuley.cpp"
        "game/shops/twillen.cpp"
        "game/spawning_and_preloading.cpp"
        "game/teleport.cpp"
        "ghosts/plugins/update_active_animations_plugin.cpp"
        "ghosts/plugins.cpp"
        "ghosts.cpp"
        "ghosts_playground.cpp"
        "input/action_registration.cpp"
        "input/controller_bindings.cpp"
        "input/helpers.cpp"
        "input/rando_bindings.cpp"
        "input/sdl_input.cpp"
        "ipc/base_handlers.cpp"
        "ipc/hierarchy.cpp"
        "league/league.cpp"
        "location_data/location_collection.cpp"
        "location_data/parser.cpp"
        "messages/credits_controller.cpp"
        "messages/credit_entries/base_entry.cpp"
        "messages/credit_entries/text_entry.cpp"
        "messages/credit_entries/move_entry.cpp"
        "messages/map_message.cpp"
        "messages/messages.cpp"
        "online/multiplayer.cpp"
        "online/network.cpp"
        "online/network_monitor.cpp"
        "online/player.cpp"
        "online/player_icon.cpp"
        "online/uber_state_handler.cpp"
        "randomizer.cpp"
        "seed/items/apply_uber_state.cpp"
        "seed/items/call.cpp"
        "seed/items/call_procedure.cpp"
        "seed/items/counting_message.cpp"
        "seed/items/icon.cpp"
        "seed/items/icon_override.cpp"
        "seed/items/input.cpp"
        "seed/items/message.cpp"
        "seed/items/refill.cpp"
        "seed/items/value_modifier.cpp"
        "seed/legacy_parser/parser.cpp"
        "seed/reach_check.cpp"
        "seed/relics.cpp"
        "seed/seed.cpp"
        "seed/seed_source.cpp"
        "state_data/parser.cpp"
        "shrek.cpp"
        "stats/enemies.cpp"
        "stats/game_stats.cpp"
        "text_processors/ability.cpp"
        "text_processors/control.cpp"
        "text_processors/helpers.cpp"
        "text_processors/legacy.cpp"
        "text_processors/location.cpp"
        "text_processors/multiplayer.cpp"
        "text_processors/seed.cpp"
        "text_processors/shard.cpp"
        "text_processors/uber_state.cpp"
        "timer.cpp"
        "tracking/game_tracker.cpp"
        "uber_states/misc_handlers.cpp"
        "uber_states/uber_state_initialization.cpp"
        "uber_states/uber_state_intercepts.cpp"
        "ui/always_show_keystones.cpp"
        "ui/empty_message_provider_fix.cpp"
        "ui/main_menu_seed_info.cpp"
)

set(
        PUBLIC_HEADER_FILES
        "archipelago/archipelago.h"
        "archipelago/archipelago_ids.h"
        "archipelago/archipelago_protocol.h"
        "conditions/condition_override.h"
        "conditions/condition_uber_state.h"
        "conditions/new_setup_state_override.h"
        "conditions/targeting_override.h"
        "constants.h"
        "dev/seed_debugger.h"
        "features/area_segment_states.h"
        "features/controls/ability_overrides.h"
        "features/controls/invert_swim.h"
        "features/controls/mouse_control.h"
        "features/credits.h"
        "features/cutscene_skips/custom_cutscene_skips.h"
        "game/map/filter.h"
        "game/map/icon.h"
        "game/map/teleport_anywhere.h"
        "game/pickups/quests.h"
        "game/shops/shop.h"
        "game/shops/shop_data.h"
        "game/spawning_and_preloading.h"
        "game/teleport.h"
        "ghosts/plugins/update_active_animations_plugin.h"
        "ghosts/plugins.h"
        "ghosts.h"
        "input/controller_bindings.h"
        "input/helpers.h"
        "input/rando_bindings.h"
        "ipc/base_handlers.h"
        "location_data/location.h"
        "location_data/location_collection.h"
        "location_data/parser.h"
        "macros.h"
        "messages/credits_controller.h"
        "messages/credit_entries/base_entry.h"
        "messages/credit_entries/text_entry.h"
        "messages/credit_entries/move_entry.h"
        "messages/map_message.h"
        "online/multiplayer.h"
        "online/network.h"
        "online/network_monitor.h"
        "online/player.h"
        "online/player_icon.h"
        "online/uber_state_handler.h"
        "randomizer.h"
        "seed/items/apply_uber_state.h"
        "seed/items/call.h"
        "seed/items/call_procedure.h"
        "seed/items/counting_message.h"
        "seed/items/empty.h"
        "seed/items/icon.h"
        "seed/items/icon_override.h"
        "seed/items/input.h"
        "seed/items/message.h"
        "seed/items/refill.h"
        "seed/items/value_modifier.h"
        "seed/legacy_parser/parser.h"
        "seed/item_data.h"
        "seed/reach_check.h"
        "seed/relics.h"
        "seed/seed.h"
        "seed/seed_source.h"
        "state_data/parser.h"
        "stats/game_stats.h"
        "text_processors/ability.h"
        "text_processors/control.h"
        "text_processors/helpers.h"
        "text_processors/legacy.h"
        "text_processors/location.h"
        "text_processors/multiplayer.h"
        "text_processors/seed.h"
        "text_processors/shard.h"
        "text_processors/uber_state.h"
        "timer.h"
        "tracking/game_tracker.h"
)

set(
        MISC_FILES
        "CMakeLists.txt"
)

find_package(Protobuf CONFIG REQUIRED)
protobuf_generate_cpp(PROTO_SRC PROTO_HEADERS proto/packets.proto)
set_source_files_properties(${PROTO_SRC} ${PROTO_HEADERS} PROPERTIES GENERATED TRUE)

add_library(
        ${PROJECT_NAME}
        SHARED
        ${SOURCE_FILES}
        ${PUBLIC_HEADER_FILES}
        ${MISC_FILES}
        ${PROTO_SRC}
        ${PROTO_HEADERS}
)

target_compile_definitions(
        ${PROJECT_NAME}
        PRIVATE COMPILING_RANDOMIZER
)

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        VERSION ${WORWR_VERSION}
        SOVERSION ${WORWR_MAJOR_VERSION}
        FOLDER cpp
)

target_include_directories(
        ${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CONFIG_DIRECTORY}
        ${CONFIG_DIRECTORY}
        ${WOTWR_BASE_INCLUDES}
        ${PROJECT_BINARY_DIR}
        ${protobuf_INCLUDE_DIR}
)

target_link_libraries(
        ${PROJECT_NAME}
        Common
        Modloader
        Core
)

find_package(semver CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} semver::semver)

find_package(nlohmann_json REQUIRED)
target_link_libraries(${PROJECT_NAME} nlohmann_json::nlohmann_json)

find_package(magic_enum REQUIRED)
target_link_libraries(${PROJECT_NAME} magic_enum::magic_enum)

find_package(ixwebsocket REQUIRED)
target_link_libraries(${PROJECT_NAME} ixwebsocket::ixwebsocket)

find_package(httplib CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} httplib::httplib)

find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} OpenSSL::SSL OpenSSL::Crypto)

target_link_libraries(${PROJECT_NAME} protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)

find_package(SDL2 CONFIG REQUIRED)
target_link_libraries(
        ${PROJECT_NAME}
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)

message(STATUS "Assigning source groups.")

set_vc_structure("${CMAKE_CURRENT_SOURCE_DIR}" "${SOURCE_FILES};${PUBLIC_HEADER_FILES};${MISC_FILES}")
set_vc_structure_with_prefix("_project_settings" "${CMAKE_CURRENT_SOURCE_DIR}" "${MISC_FILES};")

install(
        TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION "${WOTWR_INSTALL_DIR}"
        LIBRARY DESTINATION "${WOTWR_INSTALL_DIR}"
        ARCHIVE DESTINATION "${WOTWR_INSTALL_DIR}"
)

install(
        FILES $<TARGET_PDB_FILE:${PROJECT_NAME}>
        DESTINATION "${WOTWR_INSTALL_DIR}"
        OPTIONAL
)
