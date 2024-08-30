#pragma once

/**
 * Any class extending `core::save_meta::SaveSerializable` can be stored
 * into game save files under a certain SaveMetaSlot.
 * Each slot can only be used once.
 */
enum class SaveMetaSlot {
    CheckpointGameStats,
    SaveFileGameStats,
    SeedMetaData,
    ArchipelagoData,
};
