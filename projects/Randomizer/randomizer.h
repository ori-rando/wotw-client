#pragma once

#include <Common/event_bus.h>

#include <Randomizer/archipelago/archipelago.h>
#include <Randomizer/location_data/location_collection.h>
#include <Randomizer/online/multiplayer.h>
#include <Randomizer/online/network.h>
#include <Randomizer/seed/reach_check.h>
#include <Randomizer/seed/seed.h>
#include <semver.hpp>

namespace randomizer {
    enum class RandomizerEvent {
        LocationCollectionLoaded,
        SeedLoaded,
        SeedLoadedPostGrant,
        ReachCheck,
        ReachableItemsChanged,
        NewGameSeedSourceUpdated,
    };

    bool timer_should_pause();
    void reread_seed_source();
    void server_connect(long multiverse_id, bool force_reconnect = false);
    void server_reconnect_current_multiverse();
    void server_disconnect();
    void load_new_game_source();

    semver::version randomizer_version();

    /**
     * If difficulty enforcement is enabled and the current
     * difficulty differs from the intended one, set the current
     * difficulty to the intended one
     */
    void check_seed_difficulty_enforcement();

    void queue_reach_check();
    seed::ReachCheckResult const& reach_check();

    common::TimedMultiEventBus<RandomizerEvent>& event_bus();
    std::unordered_map<core::api::uber_states::UberStateCondition, std::string>& state_collection();
    location_data::LocationCollection& location_collection();
    seed::Seed& game_seed();
    online::NetworkClient& network_client();
    archipelago::ArchipelagoClient& archipelago_client();
    void connect_ap_client();
    bool should_use_ap_client();
    online::MultiplayerUniverse& multiplayer_universe();
    std::shared_ptr<core::text::CompositeTextProcessor> general_text_processor();
    std::shared_ptr<seed::SeedSource> get_new_game_seed_source();
    void set_new_game_seed_content(const std::string& content);
    std::optional<long> get_multiverse_id();

    void queue_input_unlocked_callback(std::function<void()> const& callback);
} // namespace randomizer
