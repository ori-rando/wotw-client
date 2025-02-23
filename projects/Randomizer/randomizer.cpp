#include <Core/api/game/debug_menu.h>
#include <Core/api/game/game.h>
#include <Core/api/game/player.h>
#include <Core/api/game/ui.h>
#include <Core/api/scenes/scene_load.h>
#include <Core/api/uber_states/uber_state_handlers.h>
#include <Core/core.h>
#include <Core/settings.h>
#include <Modloader/app/methods/Game/UI_Hints.h>
#include <Modloader/app/methods/GameController.h>
#include <Modloader/app/methods/GameStateMachine.h>
#include <Modloader/app/methods/TitleScreenManager.h>
#include <Modloader/app/types/GameController.h>
#include <Modloader/app/types/UI_Hints.h>
#include <Modloader/modloader.h>
#include <Randomizer/archipelago/archipelago.h>
#include <Randomizer/features/wheel.h>
#include <Randomizer/game/pickups/quests.h>
#include <Randomizer/game/shops/shop.h>
#include <Randomizer/location_data/parser.h>
#include <Randomizer/online/network_monitor.h>
#include <Randomizer/randomizer.h>
#include <Randomizer/seed/legacy_parser/parser.h>
#include <Randomizer/seed/seed_source.h>
#include <Randomizer/state_data/parser.h>
#include <Randomizer/text_processors/ability.h>
#include <Randomizer/text_processors/control.h>
#include <Randomizer/text_processors/legacy.h>
#include <Randomizer/text_processors/multiplayer.h>
#include <Randomizer/text_processors/seed.h>
#include <Randomizer/text_processors/shard.h>
#include <Randomizer/text_processors/uber_state.h>
#include <Randomizer/timer.h>
#include <Randomizer/uber_states/uber_state_intercepts.h>
#include <fstream>
#include <utility>


namespace randomizer {
    namespace {
        location_data::LocationCollection randomizer_location_collection;
        std::unordered_map<core::api::uber_states::UberStateCondition, std::string> randomizer_state_name_map;
        seed::Seed randomizer_seed(randomizer_location_collection);
        seed::ReachCheckResult reach_check_result;
        online::NetworkClient client;
        online::MultiplayerUniverse universe;
        std::shared_ptr<core::text::CompositeTextProcessor> text_processor;
        archipelago::ArchipelagoClient ap_client;

        online::NetworkMonitor monitor;
        core::dev::StatusDisplay status({
            .position = app::Vector3{0.2f, -0.2f, 0},
            .margins = {-0.09f, -0.09f},
            .alignment = app::AlignmentMode__Enum::Left,
            .horizontal_anchor = app::HorizontalAnchorMode__Enum::Left,
            .vertical_anchor = app::VerticalAnchorMode__Enum::Top,
            .screen_position = core::api::screen_position::ScreenPosition::TopLeft,
        });

        auto seed_save_data = std::make_shared<seed::SaveSlotSeedMetaData>();

        std::shared_ptr<seed::SeedSource> new_game_seed_source = std::make_shared<seed::EmptySeedSource>();
        std::string new_game_seed_content; // Set by spawning_and_preloading.cpp

        bool reach_check_queued = false;
        bool reach_check_in_progress = false;
        bool pause_timer = false;

        std::optional<long> multiverse_id_to_connect_to = std::nullopt;

        void on_reach_check(const std::optional<seed::ReachCheckResult>& result) {
            reach_check_in_progress = false;

            if (result.has_value()) {
                if (!reach_check_result.is_same_as(*result)) {
                    event_bus().trigger_event(RandomizerEvent::ReachableItemsChanged, EventTiming::Before);
                    reach_check_result = *result;
                    event_bus().trigger_event(RandomizerEvent::ReachableItemsChanged, EventTiming::After);
                }

                event_bus().trigger_event(RandomizerEvent::ReachCheck, EventTiming::After);
            }
        }

        bool do_reach_check() {
            if (reach_check_in_progress || !core::api::game::in_game()) {
                return false;
            }

            reach_check_in_progress = true;
            event_bus().trigger_event(RandomizerEvent::ReachCheck, EventTiming::Before);
            seed::reach_check(on_reach_check);
            return true;
        }

        [[maybe_unused]]
        auto on_before_shutdown = core::api::game::event_bus().register_handler(GameEvent::Shutdown, EventTiming::Before, [](auto, auto) {
            server_disconnect();
            ap_client.disconnect();
        });

        std::vector<std::function<void()>> input_unlocked_callbacks;
        [[maybe_unused]]
        auto on_input_locked_handler = core::api::game::event_bus().register_handler(GameEvent::FixedUpdate, EventTiming::After, [](auto, auto) {
            if (!core::api::game::player::can_move()) {
                return;
            }

            for (auto const& callback: input_unlocked_callbacks) {
                callback();
            }

            input_unlocked_callbacks.clear();
        });

        [[maybe_unused]]
        auto on_after_new_game_initialized = core::api::game::event_bus().register_handler(GameEvent::NewGameInitialized, EventTiming::After, [](auto, auto) {
            core::message_controller().clear_recent_messages();

            queue_input_unlocked_callback([]() {
                pause_timer = false;
                randomizer_seed.grant(core::api::uber_states::UberState(UberStateGroup::RandoEvents, 0), 0);
                randomizer_seed.grant(core::api::uber_states::UberState(UberStateGroup::RandoEvents, 1), 0);
                core::api::game::save(true);
                queue_reach_check();
                uber_states::disable_reverts() = false;

                if (network_client().wants_connection()) {
                    multiplayer_universe().report_player_save_guid(core::save_meta::get_current_save_guid());
                }
            });

            Game::UI_Hints::Show(
                core::api::system::create_message_provider("*Good Luck! <3*"), app::HintLayer__Enum::Gameplay, 3.f, app::Vector3{0.f, 0.f, 0.f}
            );

            game::pickups::quests::clear_queued_quest_messages_on_next_update();
        });

        [[maybe_unused]]
        auto on_respawn = core::api::game::event_bus().register_handler(GameEvent::Respawn, EventTiming::After, [](auto, auto) {
            core::message_controller().clear_central();
            queue_reach_check();
        });

        [[maybe_unused]]
        auto on_before_seed_loaded = randomizer::event_bus().register_handler(randomizer::RandomizerEvent::SeedLoaded, EventTiming::Before, [](auto, auto) {
            core::text::reset_to_default_values();
        });

        [[maybe_unused]]
        auto on_after_seed_loaded = event_bus().register_handler(RandomizerEvent::SeedLoaded, EventTiming::After, [](auto, auto) {
            universe.uber_state_handler().clear_unsyncables();
            features::wheel::clear_wheels();
            features::wheel::initialize_default_wheel();
            game::shops::reset_shop_data();
            randomizer_seed.grant(core::api::uber_states::UberState(UberStateGroup::RandoEvents, 1), 0);

            queue_reach_check();
            event_bus().trigger_event(RandomizerEvent::SeedLoadedPostGrant, EventTiming::Before);
            event_bus().trigger_event(RandomizerEvent::SeedLoadedPostGrant, EventTiming::After);

            if (should_use_ap_client() & !ap_client.is_connected()) {
                connect_ap_client();
            }
        });

        void load_seed(const bool show_message) {
            event_bus().trigger_event(RandomizerEvent::LocationCollectionLoaded, EventTiming::Before);
            randomizer_location_collection.read(modloader::base_path() / "loc_data.csv", location_data::parse_location_data);
            event_bus().trigger_event(RandomizerEvent::LocationCollectionLoaded, EventTiming::After);

            randomizer_state_name_map.clear();
            state_data::parse_state_data(modloader::base_path() / "state_data.csv", randomizer_state_name_map);

            randomizer_seed.read(seed_save_data->seed_content, seed::legacy_parser::parse, show_message);
        }

        [[maybe_unused]]
        auto on_before_new_game_initialized = core::api::game::event_bus().register_handler(GameEvent::NewGameInitialized, EventTiming::Before, [](auto, auto) {
            pause_timer = true;

            seed_save_data->seed_source_string = new_game_seed_source->to_source_string();
            seed_save_data->seed_content = new_game_seed_content;
            load_seed(false);

            core::api::game::player::shard_slots().set(3);

        });

        [[maybe_unused]]
        auto on_fixed_update = core::api::game::event_bus().register_handler(GameEvent::FixedUpdate, EventTiming::Before, [](auto, auto) {
            if (reach_check_queued && do_reach_check()) {
                reach_check_queued = false;
            }

            const float delta_time = core::api::game::fixed_delta_time();
            monitor.update(delta_time);
            status.update(delta_time);

            game_seed().process_timers(delta_time);
        });

        [[maybe_unused]]
        auto on_finished_loading_save_handle = core::api::game::event_bus().register_handler(
            GameEvent::FinishedLoadingSave,
            EventTiming::After,
            [](auto, auto) {
                load_seed(false);
                queue_reach_check();
                check_seed_difficulty_enforcement();
            }
        );

        [[maybe_unused]]
        auto on_restore_checkpoint = core::api::game::event_bus().register_handler(GameEvent::RestoreCheckpoint, EventTiming::After, [](auto, auto) {
            check_seed_difficulty_enforcement();
            randomizer_seed.grant(core::api::uber_states::UberState(UberStateGroup::RandoEvents, 7), 0);
            queue_reach_check();
        });

        [[maybe_unused]]
        auto on_uber_state_changed = core::api::uber_states::notification_bus().register_handler([](auto params) {
            randomizer_seed.grant(params.state, params.previous_value);
        });

        [[maybe_unused]]
        auto on_game_ready = modloader::event_bus().register_handler(ModloaderEvent::GameReady, [](auto) {
            monitor.display(&status);
            monitor.network_client(&client);

            universe.register_packet_handlers(client);

            // TODO: Don't just do this on game ready.
            modloader::cursor_lock(core::settings::cursor_locked());

            text_processor = std::make_shared<core::text::CompositeTextProcessor>();
            text_processor->compose(std::make_shared<text_processors::UberStateProcessor>());
            text_processor->compose(std::make_shared<text_processors::ControlProcessor>());
            text_processor->compose(std::make_shared<text_processors::AbilityProcessor>());
            text_processor->compose(std::make_shared<text_processors::ShardProcessor>());
            text_processor->compose(std::make_shared<text_processors::SeedProcessor>());
            text_processor->compose(std::make_shared<text_processors::LegacyProcessor>());
            text_processor->compose(std::make_shared<text_processors::MultiplayerProcessor>());

            core::message_controller().central_display().text_processor(text_processor);
            core::message_controller().recent_display().text_processor(text_processor);

            seed_save_data = std::make_unique<seed::SaveSlotSeedMetaData>();
            register_slot(SaveMetaSlot::SeedMetaData, SaveMetaSlotPersistence::None, seed_save_data);

            load_new_game_source();
        });

        IL2CPP_INTERCEPT(GameController, void, ParseCommandLineArgs, (app::GameController * this_ptr)) {
            next::GameController::ParseCommandLineArgs(this_ptr);
            core::api::game::debug_menu::set_debug_enabled(core::settings::start_debug_enabled());
        }

        [[maybe_unused]]
        auto on_title_screen_loaded = core::api::scenes::single_event_bus().register_handler("wotwTitleScreen", [](const auto meta_data, auto) {
            if (meta_data->state == app::SceneState__Enum::Loaded) {
                randomizer_seed.clear();
            }
        });
    } // namespace

    bool timer_should_pause() {
        return pause_timer;
    }

    void load_new_game_source() {
        std::ifstream seed_source_file(modloader::base_path() / ".newgameseedsource", std::ios::binary);

        if (seed_source_file.is_open()) {
            std::string source_str{std::istreambuf_iterator(seed_source_file),
                                   std::istreambuf_iterator<char>()};

            event_bus().trigger_event(RandomizerEvent::NewGameSeedSourceUpdated, EventTiming::Before);
            new_game_seed_source = seed::parse_source_string(source_str);
            event_bus().trigger_event(RandomizerEvent::NewGameSeedSourceUpdated, EventTiming::After);
        }
    }

    semver::version randomizer_version() {
        semver::version version = semver::from_string("0.0.0");
        const std::ifstream version_file(modloader::base_path() / "VERSION");
        if (version_file.is_open()) {
            std::stringstream version_buffer;
            version_buffer << version_file.rdbuf();
            const auto parsed = semver::from_string_noexcept(trim_copy(version_buffer.str()));

            if (parsed.has_value()) {
                version = parsed.value();
            }
        }

        return version;
    }

    void queue_input_unlocked_callback(std::function<void()> const& callback) { input_unlocked_callbacks.push_back(callback); }

    void queue_reach_check() {
        if (!do_reach_check()) {
            reach_check_queued = true;
        }
    }

    void reread_seed_source() {
        const auto current_source = seed_save_data->get_source();

        if (!current_source->allows_rereading()) {
            core::message_controller().queue_central({
                .text = core::Property<std::string>::format("Cannot re-read this seed."),
                .show_box = true,
                .prioritized = true,
            });
            return;
        }

        const auto [status, seed_content] = current_source->poll();

        switch (status) {
            case seed::SourceStatus::Ready:
                seed_save_data->seed_content = seed_content.value();
                load_seed(true);
                break;
            case seed::SourceStatus::Loading:
                core::message_controller().queue_central({
                    .text = core::Property<std::string>::format("The seed source is still loading. Please try again later..."),
                    .show_box = true,
                    .prioritized = true,
                });
                break;
            case seed::SourceStatus::Error:
                core::message_controller().queue_central({
                    .text = core::Property<std::string>::format("Error reading seed source: {}", current_source->get_error().value()),
                    .show_box = true,
                    .prioritized = true,
                });
                break;
        }
    }

    void server_reconnect_current_multiverse() {
        if (!multiverse_id_to_connect_to.has_value()) {
            if (network_client().wants_connection()) {
                server_disconnect();
            }

            return;
        }

        server_connect(*multiverse_id_to_connect_to, true);
    }

    void server_connect(long multiverse_id, bool force_reconnect) {
        // Don't try to connect if we are already connected to the target multiverse
        if (
            !force_reconnect &&
            network_client().wants_connection() &&
            multiverse_id_to_connect_to.has_value() &&
            *multiverse_id_to_connect_to == multiverse_id
            ) {
            return;
        }

        if (network_client().wants_connection()) {
            server_disconnect();
        }

        const auto insecure = core::settings::insecure();
        const auto host = core::settings::host();
        const auto udp_port = core::settings::udp_port();
        multiverse_id_to_connect_to = multiverse_id;

        const std::string websocket_url = std::format("{}://{}/api/client-websocket/{}/wotw", insecure ? "ws" : "wss", host, multiverse_id);
        client.websocket_connect(websocket_url);
        client.udp_open(host, udp_port);
    }

    void server_disconnect() {
        client.disconnect();
        multiverse_id_to_connect_to = std::nullopt;
        seed::set_server_seed_content(std::nullopt);
    }

    void check_seed_difficulty_enforcement() {
        const auto game_difficulties = [&]() -> seed::Seed::GameDifficultySettings {
            if (multiplayer_universe().game_difficulty_settings_overrides().has_value()) {
                return *multiplayer_universe().game_difficulty_settings_overrides();
            }

            return game_seed().info().meta.game_difficulties;
        }();

        const auto game_controller = core::api::game::game_controller();
        const auto current_difficulty = GameController::get_GameDifficultyMode(game_controller);

        if (game_difficulties.get_for_game_difficulty(current_difficulty) == seed::Seed::GameDifficultySetting::Deny) {
            auto lowest_allowed_difficulty = game_difficulties.get_lowest_allowed_difficulty();
            if (lowest_allowed_difficulty.has_value()) {
                GameController::set_GameDifficultyMode(game_controller, *lowest_allowed_difficulty);
            }
        }
    }

    common::TimedMultiEventBus<RandomizerEvent>& event_bus() {
        static common::TimedMultiEventBus<RandomizerEvent> randomizer_event_bus;
        return randomizer_event_bus;
    }

    void connect_ap_client() {
        std::string url;
        auto seed_meta = randomizer_seed.info().meta;
        if (seed_meta.archipelago_address.value_or("archipelago.gg") == "archipelago.gg") {
            url = std::format("wss://archipelago.gg:{}/", seed_meta.archipelago_port.value_or("38281"));
        }
        else {
            url = std::format("ws://{}:{}/", seed_meta.archipelago_address.value_or("archipelago.gg"), seed_meta.archipelago_port.value_or("38281"));
        }
        modloader::info("archipelago", std::format("Opening websocket to {}", url));
        archipelago_client().connect(url, seed_meta.archipelago_slot_name.value_or("empty_slot_name"), seed_meta.archipelago_password.value_or(""));
    };

    location_data::LocationCollection& location_collection() { return randomizer_location_collection; }

    std::unordered_map<core::api::uber_states::UberStateCondition, std::string>& state_collection() { return randomizer_state_name_map; }

    seed::Seed& game_seed() { return randomizer_seed; }

    seed::ReachCheckResult const& reach_check() { return reach_check_result; }

    online::NetworkClient& network_client() { return client; }

    archipelago::ArchipelagoClient& archipelago_client() { return ap_client; }
    bool should_use_ap_client() {return std::ranges::find(randomizer_seed.info().meta.flags, "AP") != randomizer_seed.info().meta.flags.end();}

    online::MultiplayerUniverse& multiplayer_universe() { return universe; }

    std::shared_ptr<core::text::CompositeTextProcessor> general_text_processor() { return text_processor; }
    std::shared_ptr<seed::SeedSource> get_new_game_seed_source() { return new_game_seed_source; }

    void set_new_game_seed_content(const std::string& content) { new_game_seed_content = content; }
    std::optional<long> get_multiverse_id() { return multiverse_id_to_connect_to; }
} // namespace randomizer
