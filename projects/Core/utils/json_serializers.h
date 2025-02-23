#pragma once

#include <Core/api/graphics/sprite.h>
#include <nlohmann/json.hpp>

#include <Modloader/app/structs/AbilityType__Enum.h>
#include <Modloader/app/structs/AlignmentMode__Enum.h>
#include <Modloader/app/structs/BlendMode__Enum.h>
#include <Modloader/app/structs/ConditionUberState_ConditionsCheckMode__Enum.h>
#include <Modloader/app/structs/HorizontalAnchorMode__Enum.h>
#include <Modloader/app/structs/QuestNodeSetup_RewardType__Enum.h>
#include <Modloader/app/structs/SetupControllerStateHolder_StateControllerMode__Enum.h>
#include <Modloader/app/structs/UberStateConditionType__Enum.h>
#include <Modloader/app/structs/VerticalAnchorMode__Enum.h>
#include <Modloader/app/structs/WorldMapIconType__Enum.h>

CORE_DLLEXPORT bool load_json_file(const std::string& path, nlohmann::json& j);

namespace app {
    CORE_DLLEXPORT void to_json(nlohmann::json& j, const Vector2& s);
    CORE_DLLEXPORT void from_json(const nlohmann::json& j, Vector2& s);

    CORE_DLLEXPORT void to_json(nlohmann::json& j, const Vector3& s);
    CORE_DLLEXPORT void from_json(const nlohmann::json& j, Vector3& s);

    CORE_DLLEXPORT void to_json(nlohmann::json& j, const Vector4& s);
    CORE_DLLEXPORT void from_json(const nlohmann::json& j, Vector4& s);

    CORE_DLLEXPORT void to_json(nlohmann::json& j, const Color& s);
    CORE_DLLEXPORT void from_json(const nlohmann::json& j, Color& s);

    NLOHMANN_JSON_SERIALIZE_ENUM(
        BlendMode__Enum,
        {
            {BlendMode__Enum::Zero,             "Zero"            },
            {BlendMode__Enum::One,              "One"             },
            {BlendMode__Enum::DstColor,         "DstColor"        },
            {BlendMode__Enum::SrcColor,         "SrcColor"        },
            {BlendMode__Enum::OneMinusDstColor, "OneMinusDstColor"},
            {BlendMode__Enum::SrcAlpha,         "SrcAlpha"        },
            {BlendMode__Enum::OneMinusSrcColor, "OneMinusSrcColor"},
            {BlendMode__Enum::DstAlpha,         "DstAlpha"        },
            {BlendMode__Enum::OneMinusDstAlpha, "OneMinusDstAlpha"},
            {BlendMode__Enum::SrcAlphaSaturate, "SrcAlphaSaturate"},
            {BlendMode__Enum::OneMinusSrcAlpha, "OneMinusSrcAlpha"},
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        AlignmentMode__Enum,
        {
            {AlignmentMode__Enum::Left,    "Left"   },
            {AlignmentMode__Enum::Center,  "Center" },
            {AlignmentMode__Enum::Right,   "Right"  },
            {AlignmentMode__Enum::Justify, "Justify"},
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        HorizontalAnchorMode__Enum,
        {
            {HorizontalAnchorMode__Enum::Left,   "Left"  },
            {HorizontalAnchorMode__Enum::Center, "Center"},
            {HorizontalAnchorMode__Enum::Right,  "Right" },
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        VerticalAnchorMode__Enum,
        {
            {VerticalAnchorMode__Enum::Top,    "Top"   },
            {VerticalAnchorMode__Enum::Middle, "Middle"},
            {VerticalAnchorMode__Enum::Bottom, "Bottom"},
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        SetupControllerStateHolder_StateControllerMode__Enum,
        {
            {SetupControllerStateHolder_StateControllerMode__Enum::Active,  "Active" },
            {SetupControllerStateHolder_StateControllerMode__Enum::Passive, "Passive"},
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        AbilityType__Enum,
        {
            {app::AbilityType__Enum::None,                   "None"                  },
            {app::AbilityType__Enum::Bash,                   "Bash"                  },
            {app::AbilityType__Enum::ChargeFlame,            "ChargeFlame"           },
            {app::AbilityType__Enum::WallJump,               "WallJump"              },
            {app::AbilityType__Enum::Stomp,                  "Stomp"                 },
            {app::AbilityType__Enum::DoubleJump,             "DoubleJump"            },
            {app::AbilityType__Enum::ChargeJump,             "ChargeJump"            },
            {app::AbilityType__Enum::Magnet,                 "Magnet"                },
            {app::AbilityType__Enum::UltraMagnet,            "UltraMagnet"           },
            {app::AbilityType__Enum::Climb,                  "Climb"                 },
            {app::AbilityType__Enum::Glide,                  "Glide"                 },
            {app::AbilityType__Enum::SpiritFlame,            "SpiritFlame"           },
            {app::AbilityType__Enum::RapidFlame,             "RapidFlame"            },
            {app::AbilityType__Enum::SplitFlameUpgrade,      "SplitFlameUpgrade"     },
            {app::AbilityType__Enum::SoulEfficiency,         "SoulEfficiency"        },
            {app::AbilityType__Enum::WaterBreath,            "WaterBreath"           },
            {app::AbilityType__Enum::ChargeFlameBlast,       "ChargeFlameBlast"      },
            {app::AbilityType__Enum::ChargeFlameBurn,        "ChargeFlameBurn"       },
            {app::AbilityType__Enum::DoubleJumpUpgrade,      "DoubleJumpUpgrade"     },
            {app::AbilityType__Enum::BashBuff,               "BashBuff"              },
            {app::AbilityType__Enum::UltraDefense,           "UltraDefense"          },
            {app::AbilityType__Enum::HealthEfficiency,       "HealthEfficiency"      },
            {app::AbilityType__Enum::Sense,                  "Sense"                 },
            {app::AbilityType__Enum::UltraStomp,             "UltraStomp"            },
            {app::AbilityType__Enum::SparkFlame,             "SparkFlame"            },
            {app::AbilityType__Enum::QuickFlame,             "QuickFlame"            },
            {app::AbilityType__Enum::MapMarkers,             "MapMarkers"            },
            {app::AbilityType__Enum::EnergyEfficiency,       "EnergyEfficiency"      },
            {app::AbilityType__Enum::HealthMarkers,          "HealthMarkers"         },
            {app::AbilityType__Enum::EnergyMarkers,          "EnergyMarkers"         },
            {app::AbilityType__Enum::AbilityMarkers,         "AbilityMarkers"        },
            {app::AbilityType__Enum::Rekindle,               "Rekindle"              },
            {app::AbilityType__Enum::Regroup,                "Regroup"               },
            {app::AbilityType__Enum::ChargeFlameEfficiency,  "ChargeFlameEfficiency" },
            {app::AbilityType__Enum::UltraSoulFlame,         "UltraSoulFlame"        },
            {app::AbilityType__Enum::SoulFlameEfficiency,    "SoulFlameEfficiency"   },
            {app::AbilityType__Enum::CinderFlame,            "CinderFlame"           },
            {app::AbilityType__Enum::UltraSplitFlame,        "UltraSplitFlame"       },
            {app::AbilityType__Enum::Dash,                   "Dash"                  },
            {app::AbilityType__Enum::Grenade,                "Grenade"               },
            {app::AbilityType__Enum::GrenadeUpgrade,         "GrenadeUpgrade"        },
            {app::AbilityType__Enum::ChargeDash,             "ChargeDash"            },
            {app::AbilityType__Enum::AirDash,                "AirDash"               },
            {app::AbilityType__Enum::GrenadeEfficiency,      "GrenadeEfficiency"     },
            {app::AbilityType__Enum::Bounce,                 "Bounce"                },
            {app::AbilityType__Enum::SpiritLeash,            "SpiritLeash"           },
            {app::AbilityType__Enum::SpiritSlash,            "SpiritSlash"           },
            {app::AbilityType__Enum::HeavySpiritSlash,       "HeavySpiritSlash"      },
            {app::AbilityType__Enum::FireburstSpell,         "FireburstSpell"        },
            {app::AbilityType__Enum::FirewhirlSpell,         "FirewhirlSpell"        },
            {app::AbilityType__Enum::GlowSpell,              "GlowSpell"             },
            {app::AbilityType__Enum::LockOnSpell,            "LockOnSpell"           },
            {app::AbilityType__Enum::TimeWarpSpell,          "TimeWarpSpell"         },
            {app::AbilityType__Enum::ShieldSpell,            "ShieldSpell"           },
            {app::AbilityType__Enum::EnergyWallSpell,        "EnergyWallSpell"       },
            {app::AbilityType__Enum::InvisibilitySpell,      "InvisibilitySpell"     },
            {app::AbilityType__Enum::TrapSpell,              "TrapSpell"             },
            {app::AbilityType__Enum::WarpSpell,              "WarpSpell"             },
            {app::AbilityType__Enum::LightSpell,             "LightSpell"            },
            {app::AbilityType__Enum::MindControlSpell,       "MindControlSpell"      },
            {app::AbilityType__Enum::MirageSpell,            "MirageSpell"           },
            {app::AbilityType__Enum::StickyMineSpell,        "StickyMineSpell"       },
            {app::AbilityType__Enum::SpiritSpearSpell,       "SpiritSpearSpell"      },
            {app::AbilityType__Enum::LightSpearSpell,        "LightSpearSpell"       },
            {app::AbilityType__Enum::LifeAbsorbSpell,        "LifeAbsorbSpell"       },
            {app::AbilityType__Enum::MeditateSpell,          "MeditateSpell"         },
            {app::AbilityType__Enum::ChargeShotSpell,        "ChargeShotSpell"       },
            {app::AbilityType__Enum::SpiritShardsSpell,      "SpiritShardsSpell"     },
            {app::AbilityType__Enum::SpiritSentrySpell,      "SpiritSentrySpell"     },
            {app::AbilityType__Enum::PowerslideSpell,        "PowerslideSpell"       },
            {app::AbilityType__Enum::CounterstrikeSpell,     "CounterstrikeSpell"    },
            {app::AbilityType__Enum::EarthShatterSpell,      "EarthShatterSpell"     },
            {app::AbilityType__Enum::JumpShotSpell,          "JumpShotSpell"         },
            {app::AbilityType__Enum::RoundupLeashSpell,      "RoundupLeashSpell"     },
            {app::AbilityType__Enum::BurrowSpell,            "BurrowSpell"           },
            {app::AbilityType__Enum::PowerOfFriendshipSpell, "PowerOfFriendshipSpell"},
            {app::AbilityType__Enum::LightningSpell,         "LightningSpell"        },
            {app::AbilityType__Enum::SpiritFlareSpell,       "SpiritFlareSpell"      },
            {app::AbilityType__Enum::EntanglingRootsSpell,   "EntanglingRootsSpell"  },
            {app::AbilityType__Enum::MarkOfTheWildsSpell,    "MarkOfTheWildsSpell"   },
            {app::AbilityType__Enum::HomingMissileSpell,     "HomingMissileSpell"    },
            {app::AbilityType__Enum::SpiritCrescentSpell,    "SpiritCrescentSpell"   },
            {app::AbilityType__Enum::MineSpell,              "MineSpell"             },
            {app::AbilityType__Enum::Pinned,                 "Pinned"                },
            {app::AbilityType__Enum::Leached,                "Leached"               },
            {app::AbilityType__Enum::Bow,                    "Bow"                   },
            {app::AbilityType__Enum::Hammer,                 "Hammer"                },
            {app::AbilityType__Enum::Torch,                  "Torch"                 },
            {app::AbilityType__Enum::Sword,                  "Sword"                 },
            {app::AbilityType__Enum::Digging,                "Digging"               },
            {app::AbilityType__Enum::DashNew,                "DashNew"               },
            {app::AbilityType__Enum::Launch,                 "Launch"                },
            {app::AbilityType__Enum::WaterDash,              "WaterDash"             },
            {app::AbilityType__Enum::TeleportSpell,          "TeleportSpell"         },
            {app::AbilityType__Enum::ChakramSpell,           "ChakramSpell"          },
            {app::AbilityType__Enum::Drill,                  "Drill"                 },
            {app::AbilityType__Enum::GoldenSein,             "GoldenSein"            },
            {app::AbilityType__Enum::BowCharge,              "BowCharge"             },
            {app::AbilityType__Enum::Swordstaff,             "Swordstaff"            },
            {app::AbilityType__Enum::Chainsword,             "Chainsword"            },
            {app::AbilityType__Enum::SpiritMagnet,           "SpiritMagnet"          },
            {app::AbilityType__Enum::SwordCharge,            "SwordCharge"           },
            {app::AbilityType__Enum::HammerCharge,           "HammerCharge"          },
            {app::AbilityType__Enum::Blaze,                  "Blaze"                 },
            {app::AbilityType__Enum::TurretSpell,            "TurretSpell"           },
            {app::AbilityType__Enum::Regenerate,             "Regenerate"            },
            {app::AbilityType__Enum::FeatherFlap,            "FeatherFlap"           },
            {app::AbilityType__Enum::WeaponCharge,           "WeaponCharge"          },
            {app::AbilityType__Enum::DamageUpgradeA,         "DamageUpgradeA"        },
            {app::AbilityType__Enum::DamageUpgradeB,         "DamageUpgradeB"        },
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        QuestNodeSetup_RewardType__Enum,
        {
            {app::QuestNodeSetup_RewardType__Enum::None,            "None"           },
            {app::QuestNodeSetup_RewardType__Enum::CompletedReward, "CompletedReward"},
            {app::QuestNodeSetup_RewardType__Enum::WelcomeReward,   "WelcomeReward"  },
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        UberStateConditionType__Enum,
        {
            {app::UberStateConditionType__Enum::Undefined,             "Undefined"            },
            {app::UberStateConditionType__Enum::BooleanCondition,      "BooleanCondition"     },
            {app::UberStateConditionType__Enum::FloatCondition,        "FloatCondition"       },
            {app::UberStateConditionType__Enum::AbilityCondition,      "AbilityCondition"     },
            {app::UberStateConditionType__Enum::IntCondition,          "IntCondition"         },
            {app::UberStateConditionType__Enum::HoldingTorchCondition, "HoldingTorchCondition"},
            {app::UberStateConditionType__Enum::ByteCondition,         "ByteCondition"        },
            {app::UberStateConditionType__Enum::SceneCondition,        "SceneCondition"       },
            {app::UberStateConditionType__Enum::GenericCondition,      "GenericCondition"     },
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        ConditionUberState_ConditionsCheckMode__Enum,
        {
            {app::ConditionUberState_ConditionsCheckMode__Enum::AllTrueRequired, "AllTrueRequired"},
            {app::ConditionUberState_ConditionsCheckMode__Enum::AnyTrueSuffice,  "AnyTrueSuffice" },
    }
    );

    NLOHMANN_JSON_SERIALIZE_ENUM(
        WorldMapIconType__Enum,
        {
            {app::WorldMapIconType__Enum::Keystone,             "Keystone"            },
            {app::WorldMapIconType__Enum::Mapstone,             "Mapstone"            },
            {app::WorldMapIconType__Enum::BreakableWall,        "BreakableWall"       },
            {app::WorldMapIconType__Enum::BreakableWallBroken,  "BreakableWallBroken" },
            {app::WorldMapIconType__Enum::StompableFloor,       "StompableFloor"      },
            {app::WorldMapIconType__Enum::StompableFloorBroken, "StompableFloorBroken"},
            {app::WorldMapIconType__Enum::EnergyGateTwo,        "EnergyGateTwo"       },
            {app::WorldMapIconType__Enum::EnergyGateOpen,       "EnergyGateOpen"      },
            {app::WorldMapIconType__Enum::KeystoneDoorFour,     "KeystoneDoorFour"    },
            {app::WorldMapIconType__Enum::KeystoneDoorOpen,     "KeystoneDoorOpen"    },
            {app::WorldMapIconType__Enum::AbilityPedestal,      "AbilityPedestal"     },
            {app::WorldMapIconType__Enum::HealthUpgrade,        "HealthUpgrade"       },
            {app::WorldMapIconType__Enum::EnergyUpgrade,        "EnergyUpgrade"       },
            {app::WorldMapIconType__Enum::SavePedestal,         "SavePedestal"        },
            {app::WorldMapIconType__Enum::AbilityPoint,         "AbilityPoint"        },
            {app::WorldMapIconType__Enum::KeystoneDoorTwo,      "KeystoneDoorTwo"     },
            {app::WorldMapIconType__Enum::Invisible,            "Invisible"           },
            {app::WorldMapIconType__Enum::Experience,           "Experience"          },
            {app::WorldMapIconType__Enum::MapstonePickup,       "MapstonePickup"      },
            {app::WorldMapIconType__Enum::EnergyGateTwelve,     "EnergyGateTwelve"    },
            {app::WorldMapIconType__Enum::EnergyGateTen,        "EnergyGateTen"       },
            {app::WorldMapIconType__Enum::EnergyGateEight,      "EnergyGateEight"     },
            {app::WorldMapIconType__Enum::EnergyGateSix,        "EnergyGateSix"       },
            {app::WorldMapIconType__Enum::EnergyGateFour,       "EnergyGateFour"      },
            {app::WorldMapIconType__Enum::SpiritShard,          "SpiritShard"         },
            {app::WorldMapIconType__Enum::NPC,                  "NPC"                 },
            {app::WorldMapIconType__Enum::QuestItem,            "QuestItem"           },
            {app::WorldMapIconType__Enum::ShardSlotUpgrade,     "ShardSlotUpgrade"    },
            {app::WorldMapIconType__Enum::Teleporter,           "Teleporter"          },
            {app::WorldMapIconType__Enum::Ore,                  "Ore"                 },
            {app::WorldMapIconType__Enum::HealthFragment,       "HealthFragment"      },
            {app::WorldMapIconType__Enum::EnergyFragment,       "EnergyFragment"      },
            {app::WorldMapIconType__Enum::Seed,                 "Seed"                },
            {app::WorldMapIconType__Enum::QuestStart,           "QuestStart"          },
            {app::WorldMapIconType__Enum::QuestEnd,             "QuestEnd"            },
            {app::WorldMapIconType__Enum::RaceStart,            "RaceStart"           },
            {app::WorldMapIconType__Enum::RaceEnd,              "RaceEnd"             },
            {app::WorldMapIconType__Enum::Eyestone,             "Eyestone"            },
            {app::WorldMapIconType__Enum::WatermillDoor,        "WatermillDoor"       },
            {app::WorldMapIconType__Enum::TempleDoor,           "TempleDoor"          },
            {app::WorldMapIconType__Enum::SmallDoor,            "SmallDoor"           },
            {app::WorldMapIconType__Enum::Shrine,               "Shrine"              },
            {app::WorldMapIconType__Enum::Loremaster,           "Loremaster"          },
            {app::WorldMapIconType__Enum::Weaponmaster,         "Weaponmaster"        },
            {app::WorldMapIconType__Enum::Gardener,             "Gardener"            },
            {app::WorldMapIconType__Enum::Mapmaker,             "Mapmaker"            },
            {app::WorldMapIconType__Enum::Shardtrader,          "Shardtrader"         },
            {app::WorldMapIconType__Enum::Wanderer,             "Wanderer"            },
            {app::WorldMapIconType__Enum::Treekeeper,           "Treekeeper"          },
            {app::WorldMapIconType__Enum::Builder,              "Builder"             },
            {app::WorldMapIconType__Enum::Kwolok,               "Kwolok"              },
            {app::WorldMapIconType__Enum::Statistician,         "Statistician"        },
            {app::WorldMapIconType__Enum::CreepHeart,           "CreepHeart"          },
            {app::WorldMapIconType__Enum::Miner,                "Miner"               },
            {app::WorldMapIconType__Enum::Spiderling,           "Spiderling"          },
            {app::WorldMapIconType__Enum::Moki,                 "Moki"                },
            {app::WorldMapIconType__Enum::MokiBrave,            "MokiBrave"           },
            {app::WorldMapIconType__Enum::MokiAdventurer,       "MokiAdventurer"      },
            {app::WorldMapIconType__Enum::MokiArtist,           "MokiArtist"          },
            {app::WorldMapIconType__Enum::MokiDarkness,         "MokiDarkness"        },
            {app::WorldMapIconType__Enum::MokiFashionable,      "MokiFashionable"     },
            {app::WorldMapIconType__Enum::MokiFisherman,        "MokiFisherman"       },
            {app::WorldMapIconType__Enum::MokiFrozen,           "MokiFrozen"          },
            {app::WorldMapIconType__Enum::MokiKwolokAmulet,     "MokiKwolokAmulet"    },
            {app::WorldMapIconType__Enum::MokiSpyglass,         "MokiSpyglass"        },
            {app::WorldMapIconType__Enum::Ku,                   "Ku"                  },
            {app::WorldMapIconType__Enum::IceFisher,            "IceFisher"           },
            {app::WorldMapIconType__Enum::Siira,                "Siira"               },
    }
    );
} // namespace app
