#include <Core/api/game/game.h>
#include <Core/api/game/player.h>
#include <Core/api/uber_states/uber_state.h>
#include <Core/api/uber_states/uber_state_virtual.h>
#include <Core/dev/timing.h>
#include <Core/enums/uber_state.h>
#include <Modloader/app/methods/Moon/UberStateCollection.h>
#include <Modloader/app/types/BooleanUberState.h>
#include <Modloader/app/types/ByteUberState.h>
#include <Modloader/app/types/FloatUberState.h>
#include <Modloader/app/types/IntUberState.h>
#include <Modloader/app/types/SerializedBooleanUberState.h>
#include <Modloader/app/types/SerializedByteUberState.h>
#include <Modloader/app/types/SerializedFloatUberState.h>
#include <Modloader/app/types/SerializedIntUberState.h>
#include <Modloader/app/types/UberID.h>
#include <Modloader/app/types/UberStateGroup.h>
#include <Modloader/il2cpp_helpers.h>
#include <Modloader/interception_macros.h>
#include <Modloader/modloader.h>
#include <Randomizer/constants.h>
#include <Randomizer/features/area_segment_states.h>
#include <Randomizer/randomizer.h>
#include <chrono>

using namespace modloader;
using namespace app::classes;
using namespace core::api::uber_states;

namespace randomizer {
    namespace {
        app::UberID* create_uber_id_ptr(int id) {
            auto uber_id = types::UberID::create();
            uber_id->fields.m_id = id;
            return uber_id;
        }

        // We cache the scriptable objects and use il2cpp::unity::instantiate_object to create instances from them
        // because that's a lot faster
        std::unordered_map<Il2CppClass*, app::IUberState*> uber_state_so_cache;
        app::UberStateGroup* group_so_cache = nullptr;

        template<typename T>
        Il2CppClass* get_klass();

        template<>
        Il2CppClass* get_klass<app::SerializedBooleanUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::SerializedBooleanUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::SerializedByteUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::SerializedByteUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::SerializedIntUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::SerializedIntUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::SerializedFloatUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::SerializedFloatUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::BooleanUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::BooleanUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::ByteUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::ByteUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::IntUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::IntUberState::get_class());
        }

        template<>
        Il2CppClass* get_klass<app::FloatUberState>() {
            return reinterpret_cast<Il2CppClass*>(types::FloatUberState::get_class());
        }

        template<typename T, typename V>
        app::IUberState* add_state(UberStateGroup group, const std::string& state_name, int state_id, V default_value) {
            auto klass = get_klass<T>();

            if (!uber_state_so_cache.contains(klass)) {
                uber_state_so_cache[klass] = reinterpret_cast<app::IUberState*>(il2cpp::unity::create_scriptable_object<T>(get_klass<T>()));
            }

            auto state = il2cpp::unity::instantiate_object<T>(reinterpret_cast<T*>(uber_state_so_cache[klass]));

            if (group_so_cache == nullptr) {
                group_so_cache = il2cpp::unity::create_scriptable_object<app::UberStateGroup>(types::UberStateGroup::get_class());
            }

            state->fields.Group = il2cpp::unity::instantiate_object<app::UberStateGroup>(group_so_cache);

            state->fields.Group->fields._.m_id = create_uber_id_ptr(static_cast<int>(group));
            il2cpp::invoke(state->fields.Group, "set_name", il2cpp::string_new(custom_uber_state_group_name(group).value_or("unknown")));

            state->fields._.m_id = create_uber_id_ptr(state_id);
            il2cpp::invoke(state, "set_name", il2cpp::string_new(state_name));

            state->fields.DefaultValue = default_value;
            state->fields.m_value = default_value;
            state->fields.NamedValues = nullptr;
            state->fields._VolitileGenericOverrideValue_k__BackingField.has_value = false;

            return reinterpret_cast<app::IUberState*>(state);
        }

        IL2CPP_INTERCEPT(Moon::UberStateCollection, void, PrepareRuntimeDataType, (app::UberStateCollection * this_ptr)) {
            auto start_time = std::chrono::high_resolution_clock::now();

            std::vector<app::IUberState*> states = {
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "sword", static_cast<int>(app::AbilityType__Enum::Sword), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "doubleJump", static_cast<int>(app::AbilityType__Enum::DoubleJump), false),
                add_state<app::SerializedBooleanUberState>(
                    UberStateGroup::Tree, "regenerateTree", static_cast<int>(app::AbilityType__Enum::MeditateSpell), false
                ),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "bow", static_cast<int>(app::AbilityType__Enum::Bow), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "dash", static_cast<int>(app::AbilityType__Enum::DashNew), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "bash", static_cast<int>(app::AbilityType__Enum::Bash), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "grapple", static_cast<int>(app::AbilityType__Enum::SpiritLeash), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "waterDash", static_cast<int>(app::AbilityType__Enum::WaterDash), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "flash", static_cast<int>(app::AbilityType__Enum::GlowSpell), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "grenade", static_cast<int>(app::AbilityType__Enum::Grenade), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "burrow", static_cast<int>(app::AbilityType__Enum::Digging), false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::Tree, "launch", static_cast<int>(app::AbilityType__Enum::ChargeJump), false),
                add_state<app::SerializedBooleanUberState>(
                    UberStateGroup::Tree, "gladesAncestralLight", static_cast<int>(app::AbilityType__Enum::DamageUpgradeA), false
                ),
                add_state<app::SerializedBooleanUberState>(
                    UberStateGroup::Tree, "inkwaterAncestralLight", static_cast<int>(app::AbilityType__Enum::DamageUpgradeB), false
                ),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "waterBreath", 23, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "spear", 74, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "hammer", 98, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "fastTravel", 105, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "shuriken", 106, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "blaze", 115, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "sentry", 116, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "explodingSpear", 1074, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "hammerShockwave", 1098, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "staticShuriken", 1106, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "chargeBlaze", 1115, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::OpherShop, "rapidSentry", 1116, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "waterBreathCost", 10023, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "spearCost", 10074, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "hammerCost", 10098, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "fastTravelCost", 10105, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "shurikenCost", 10106, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "blazeCost", 10115, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "sentryCost", 10116, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "explodingSpearCost", 11074, 300),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "hammerShockwaveCost", 11098, 300),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "staticShurikenCost", 11106, 300),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "chargeBlazeCost", 11115, 300),
                add_state<app::SerializedIntUberState>(UberStateGroup::OpherShop, "rapidSentryCost", 11116, 300),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "energy", 26, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "vitality", 22, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "overcharge", 1, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "wingclip", 3, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "tripleJump", 2, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "finesse", 40, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "swap", 5, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::TwillenShop, "lightHarvest", 19, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "energyCost", 126, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "vitalityCost", 122, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "overchargeCost", 101, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "wingclipCost", 103, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "tripleJumpCost", 102, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "finesseCost", 140, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "swapCost", 105, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TwillenShop, "lightHarvestCost", 119, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "spiritWellBuilt", 16825, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "housesABuilt", 51230, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "housesBBuilt", 23607, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "housesCBuilt", 40448, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "removeThornsBuilt", 18751, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "openCaveBuilt", 16586, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "beautifyBuilt", 15068, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "spiritWellCost", 16826, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "housesACost", 51231, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "housesBCost", 23608, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "housesCCost", 40449, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "removeThornsCost", 18752, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "openCaveCost", 16587, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::GromShop, "beautifyCost", 15069, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "spiritWellPlayCutscene", 16827, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "housesAPlayCutscene", 51232, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "housesBPlayCutscene", 23609, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "housesCPlayCutscene", 40450, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "removeThornsPlayCutscene", 18753, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "openCavePlayCutscene", 16588, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GromShop, "beautifyPlayCutscene", 15070, false),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "lightcatchersPlanted", 47651, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "selaFlowersPlanted", 16254, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "blueMoonPlanted", 33011, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "stickyGrassPlanted", 64583, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "springPlantsPlanted", 38393, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::GladesProjects, "lastTreePlanted", 40006, 0),

                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "lightcatchersCost", 47652, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "selaFlowersCost", 16255, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "blueMoonCost", 33012, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "stickyGrassCost", 64584, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "springPlantsCost", 38394, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "lastTreeCost", 40007, 0),

                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "lightcatchersPlayCutscene", 47653, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "selaFlowersPlayCutscene", 16256, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "blueMoonPlayCutscene", 33013, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "stickyGrassPlayCutscene", 64585, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "springPlantsPlayCutscene", 38395, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::TuleyShop, "lastTreePlayCutscene", 40008, 0),

                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "hammerSpeedMultiplier", 0, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "swordSpeedMultiplier", 1, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "blazeCostMultiplier", 2, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "spearCostMultiplier", 3, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "shurikenCostMultiplier", 4, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "sentryCostMultiplier", 5, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "bowCostMultiplier", 6, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "regenerationCostMultiplier", 7, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "flashCostMultiplier", 8, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "grenadeCostMultiplier", 9, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "bowRapidFireMultiplier", 10, 1),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "spearSpeedMultiplier", 11, 1),

                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "healthRegeneration", 30, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "energyRegeneration", 31, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "extraDoubleJumps", 35, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "extraDashes", 36, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "extraSentries", 37, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "extraShurikens", 38, 0),

                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "extraGrenades", 40, 0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "grenadesExplodeOnCollision", 41, true),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "bashableUnchargedGrenades", 42, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "chargedAirGrenades", 43, false),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "grenadeChargeTimeModifier", 44, 1.0f),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "grenadeMultishot", 45, 0),

                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "sentryShots", 46, 3),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "sentryFireRateSpeed", 47, 1.0),

                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "shurikenMultishotCount", 48, 0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "shurikenMultishotSpread", 49, 35.f),

                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "hammerSpeed", 50, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "swordSpeed", 51, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "blazeEfficiency", 52, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "spearEfficiency", 53, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "shurikenEfficiency", 54, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "sentryEfficiency", 55, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "bowEfficiency", 56, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "regenerateEfficiency", 57, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "flashEfficiency", 58, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::RandoUpgrade, "grenadeEfficiency", 59, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "bowAsFireSource", 70, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "blazeAsFireSource", 71, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "swordAsFireSource", 72, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "hammerAsFireSource", 73, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "spearAsFireSource", 74, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "shurikenAsFireSource", 75, false),

                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "launchSpeed", 80, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "dashDistance", 81, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "bashSpeed", 82, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "burrowSpeed", 83, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "burrowDashSpeed", 84, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "swimSpeed", 85, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "waterDashSpeed", 86, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "jumpHeight", 87, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "wallJumpStrength", 88, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "doubleJumpStrength", 89, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "grappleSpeed", 90, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "regenerateSpeed", 91, 1.0),

                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "shurikenDamageMultiplier", 92, 1.0),
                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "flashDamageMultiplier", 93, 1.0),

                add_state<app::SerializedFloatUberState>(UberStateGroup::RandoUpgrade, "flashTickInterval", 94, 1.0),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "shurikenBashable", 95, false),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoUpgrade, "overflowPickupUpgrade", 150, false),

                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onTeleport", 20, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onJump", 30, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onDoubleJump", 31, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onDash", 32, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onBash", 33, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onGlide", 34, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onSword", 35, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onHammer", 36, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onSpear", 37, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onShuriken", 38, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onGrenade", 39, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onBow", 40, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onBlaze", 41, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onSentry", 42, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onFlash", 43, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onLaunch", 44, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onWallJump", 45, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onBurrow", 46, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onWaterDash", 47, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onFlap", 48, false),
                add_state<app::BooleanUberState>(UberStateGroup::RandoEvents, "onRegenerate", 49, false),

                add_state<app::IntUberState>(UberStateGroup::Shrines, "gladesWave", 0, 0),
                add_state<app::IntUberState>(UberStateGroup::Shrines, "inkwaterWave", 1, 0),
                add_state<app::IntUberState>(UberStateGroup::Shrines, "howlsDenWave", 2, 0),
                add_state<app::IntUberState>(UberStateGroup::Shrines, "depthsWave", 3, 0),
                add_state<app::IntUberState>(UberStateGroup::Shrines, "woodsWave", 4, 0),

                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "keystonesCollected", 0, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "pickupsCollected", 2, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "spiritLightCollected", 3, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "spiritLightSpent", 4, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "oreCollected", 5, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::RandoStats, "oreSpent", 6, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoState, "tuleyExists", 300, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoState, "rainLiftedInInkwater", 401, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoState, "regenTreeDrained", 402, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoState, "cleanWater", 2000, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "squares", 0, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "lines", 1, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "rank", 2, 0),

                // murder tracking
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "kills", 10, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "swordKills", 11, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "hammerKills", 12, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "bowKills", 13, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "spearKills", 14, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "sentryKills", 15, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "blazeKills", 16, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "grenadeKills", 17, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "burnDoTKills", 18, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "shurikenKills", 19, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "launchKills", 20, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "flashKills", 21, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "bashKills", 22, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "drownedEnemies", 23, 0),

                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "minerKills", 40, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "flierKills", 41, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "tentaKills", 42, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "slimeKills", 43, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "fishKills", 44, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::BingoState, "exploderKills", 45, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "preventMapReactivateTps", 1, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "allowOpeningEyestoneDoor", 6, true),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "preventPickup", PREVENT_PICKUP_ID, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "stompThroughPortals", STOMP_THROUGH_PORTALS_ID, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "stompIntoWater", STOMP_INTO_WATER_ID, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "goodHollow", GOOD_HOLLOW_ID, true),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "inLogicFilterEnabled", IN_LOGIC_FILTER_ENABLED_ID, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "fixMeetingKwolokUnderwaterTrigger", 13, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "fixTeleporterChainOutOfBounds", 14, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "fixKwolokBossEscapeUnderwaterSpiritLightSoftlock", 15, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "fixShopAnywhere", 16, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "usePatch2Kickback", 17, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "allowTeleportingUnderwater", 18, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "allowTeleportingDuringCombatShrineFights", 19, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "removeShriekEscapeSand", 100, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "removeFeedingGroundsToElevatorSand", 101, false),
               
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "transparentCorruptedWater", 200, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::RandoConfig, "forceNoAirDecelerationFlag", FORCE_AIR_NO_DECELERATION_ID, 0),

                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "baurSneezeWithBlaze", 420, false),
                add_state<app::SerializedBooleanUberState>(UberStateGroup::RandoConfig, "baurSneezeWithFlash", 421, false),

                add_state<app::SerializedIntUberState>(UberStateGroup::UI, "launchFragmentsCount", 1, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::UI, "launchFragmentsRequired", 2, 0),

                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "inkwater", static_cast<int>(app::GameWorldAreaID__Enum::InkwaterMarsh), 200
                ),
                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "hollow", static_cast<int>(app::GameWorldAreaID__Enum::KwoloksHollow), 150
                ),
                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "wellspring", static_cast<int>(app::GameWorldAreaID__Enum::WaterMill), 150
                ),
                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "burrows", static_cast<int>(app::GameWorldAreaID__Enum::MidnightBurrow), 50
                ),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoMapCosts, "reach", static_cast<int>(app::GameWorldAreaID__Enum::BaursReach), 150),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoMapCosts, "luma", static_cast<int>(app::GameWorldAreaID__Enum::LumaPools), 150),
                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "depths", static_cast<int>(app::GameWorldAreaID__Enum::MouldwoodDepths), 150
                ),
                add_state<app::SerializedIntUberState>(
                    UberStateGroup::LupoMapCosts, "wastes", static_cast<int>(app::GameWorldAreaID__Enum::WindsweptWastes), 150
                ),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoMapCosts, "willow", static_cast<int>(app::GameWorldAreaID__Enum::WillowsEnd), 50),

                add_state<app::SerializedByteUberState>(UberStateGroup::LupoShop, "hcMapIcons", 19396, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoShop, "hcMapIconsCost", 19397, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::LupoShop, "ecMapIcons", 57987, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoShop, "ecMapIconsCost", 57988, 0),
                add_state<app::SerializedByteUberState>(UberStateGroup::LupoShop, "shardMapIcons", 41666, 0),
                add_state<app::SerializedIntUberState>(UberStateGroup::LupoShop, "shardMapIconsCost", 41667, 0),

                add_state<app::IntUberState>(UberStateGroup::Player, "currentMapArea", 51, static_cast<int>(GameArea::TOTAL)),
            };

            dev::print_time(start_time, "Built state list");

            // Custom states for userland variables
            constexpr int custom_int_count = 100;
            constexpr int custom_bool_count = 50;
            constexpr int custom_float_count = 25;

            auto next_id = 0;
            for (int i = 0; i < custom_int_count; ++i) {
                const auto id = next_id++;
                states.push_back(add_state<app::SerializedIntUberState>(UberStateGroup::Custom, std::format("int{:04d}", i), id, 0));
            }

            for (int i = 0; i < custom_bool_count; ++i) {
                const auto id = next_id++;
                states.push_back(add_state<app::SerializedBooleanUberState>(UberStateGroup::Custom, std::format("bool{:04d}", i), id, false));
            }

            for (int i = 0; i < custom_float_count; ++i) {
                const auto id = next_id++;
                states.push_back(add_state<app::SerializedFloatUberState>(UberStateGroup::Custom, std::format("float{:04d}", i), id, false));
            }

            // Saved appliers.
            constexpr int appliers_group_count = 50;
            for (int i = 0; i < appliers_group_count; ++i) {
                states.push_back(add_state<app::SerializedIntUberState>(UberStateGroup::Appliers, std::format("{:04d}_id", i * 2), i * 2, 0));

                states.push_back(add_state<app::SerializedIntUberState>(UberStateGroup::Appliers, std::format("{:04d}_value", i * 2 + 1), i * 2 + 1, 0));
            }

            dev::print_time(start_time, "Built custom state list");

            for (int i = 0; i < 2000; ++i) {
                states.push_back(add_state<app::SerializedBooleanUberState>(UberStateGroup::Multiworld, std::format("state{}", i), i, false));
            }

            dev::print_time(start_time, "Built multi state list");

            for (auto* state: states) {
                il2cpp::invoke(this_ptr->fields.m_descriptors, "Add", state);
            }

            dev::print_time(start_time, "Added states");

            info("initialize", "Custom uber states initialized.");
            next::Moon::UberStateCollection::PrepareRuntimeDataType(this_ptr);

            register_virtual_event_state(UberStateGroup::RandoEvents, 0, "onNewGame");
            register_virtual_event_state(UberStateGroup::RandoEvents, 1, "onLoadSeed");
            register_virtual_event_state(UberStateGroup::RandoEvents, 2, "onBinding1");
            register_virtual_event_state(UberStateGroup::RandoEvents, 3, "onBinding2");
            register_virtual_event_state(UberStateGroup::RandoEvents, 4, "onBinding3");
            register_virtual_event_state(UberStateGroup::RandoEvents, 5, "onBinding4");
            register_virtual_event_state(UberStateGroup::RandoEvents, 6, "onBinding5");
            register_virtual_event_state(UberStateGroup::RandoEvents, 7, "onRestoreCheckpoint");
            register_virtual_event_state(UberStateGroup::RandoEvents, 8, "onProgressHint");

            register_virtual_event_state(UberStateGroup::RandoEvents, 100, "onRequestInkwaterTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 101, "onRequestHollowTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 102, "onRequestWellspringTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 103, "onRequestWoodsTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 104, "onRequestReachTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 105, "onRequestDepthsTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 106, "onRequestLumaTrialText");
            register_virtual_event_state(UberStateGroup::RandoEvents, 107, "onRequestWastesTrialText");

            using namespace core::api::game::player;
            register_virtual_state({ValueType::Integer, UberStateGroup::Player, 0, "spiritLight", false, true}, spirit_light().wrap<double>());
            register_virtual_state({ValueType::Integer, UberStateGroup::Player, 1, "gorlekOre", false, true}, ore().wrap<double>());
            register_virtual_state({ValueType::Integer, UberStateGroup::Player, 2, "keystones", false, true}, keystones().wrap<double>());
            register_virtual_state({ValueType::Integer, UberStateGroup::Player, 10, "maxHealth", false, true}, max_health().wrap<double>());
            register_virtual_state({ValueType::Float, UberStateGroup::Player, 11, "health", false, true}, health().wrap<double>());
            register_virtual_state({ValueType::Float, UberStateGroup::Player, 12, "maxEnergy", false, true}, max_energy().wrap<double>());
            register_virtual_state({ValueType::Float, UberStateGroup::Player, 13, "energy", false, true}, energy().wrap<double>());

            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Player,
                    .state = 50,
                    .name = "currentArea",
                    .readonly = true,
                    .polled = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentArea (5, 50) is read only."); },
                    []() -> double { return static_cast<double>(get_current_area()); }
                )
            );
            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Goals,
                    .state = 500,
                    .name = "totalRelicCount",
                    .readonly = true,
                    .polled = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate totalRelicCount (23, 500) is read only."); },
                    []() -> double { return game_seed().relics().relic_count(); }
                )
            );
            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Goals,
                    .state = 501,
                    .name = "currentRelicCount",
                    .readonly = true,
                    .polled = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentRelicCount (23, 501) is read only."); },
                    []() -> double { return game_seed().relics().found_relics(); }
                )
            );
            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Goals,
                    .state = 502,
                    .name = "currentTreeCount",
                    .readonly = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentTreeCount (23, 502) is read only."); },
                    []() -> double {
                        return UberState(UberStateGroup::Tree, app::AbilityType__Enum::Sword).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::DoubleJump).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::MeditateSpell).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::Bow).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::DashNew).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::Bash).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::SpiritLeash).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::WaterDash).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::GlowSpell).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::Grenade).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::Digging).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::ChargeJump).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::DamageUpgradeA).get() +
                            UberState(UberStateGroup::Tree, app::AbilityType__Enum::DamageUpgradeB).get();
                    }
                )
            );
            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Goals,
                    .state = 503,
                    .name = "currentWispCount",
                    .readonly = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentWispCount (23, 503) is read only."); },
                    []() -> double {
                        return UberState(static_cast<UberStateGroup>(28895), 25522).get() // Reach
                            + UberState(static_cast<UberStateGroup>(18793), 63291).get() // Depths
                            + UberState(static_cast<UberStateGroup>(945), 49747).get() // Luma
                            + UberState(static_cast<UberStateGroup>(10289), 22102).get() // Wastes
                            + UberState(static_cast<UberStateGroup>(46462), 59806).get(); // Hollow
                    }
                )
            );
            register_virtual_state(
                {
                    .type = ValueType::Byte,
                    .group = UberStateGroup::Goals,
                    .state = 504,
                    .name = "currentQuestCount",
                    .readonly = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentQuestCount (23, 504) is read only."); },
                    []() -> double {
                        return static_cast<int>(UberState(static_cast<UberStateGroup>(937), 34641).get() > 3.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 35399).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 35087).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 45931).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 8973).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(48248), 51645).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(48248), 18458).get() > 3.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 20667).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 15983).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 27804).get() > 3.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 59708).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 61011).get() > 4.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 26318).get() > 10.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 33776).get() > 2.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 50597).get() > 3.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 44578).get() > 1.5) +
                            static_cast<int>(UberState(static_cast<UberStateGroup>(14019), 26394).get() > 1.5);
                    }
                )
            );

            register_virtual_state(
                {
                    .type = ValueType::Boolean,
                    .group = UberStateGroup::Goals,
                    .state = 505,
                    .name = "currentAreaHasUncollectedRelic",
                    .readonly = true,
                    .polled = true,
                },
                core::Property<double>(
                    [](double x) { error("uber_state_virtual", "Invalid operation: uberstate currentAreaHasUncollectedRelic (23, 505) is read only."); },
                    []() -> double {
                        const auto area = core::api::game::player::get_current_area();
                        return game_seed().relics().found_relics_in_area(area) < game_seed().relics().relic_count_in_area(area) ? 1.0 : 0.0;
                    }
                )
            );

            std::array shop_data{
                // Grom
                std::make_tuple(UberStateGroup::GromShop, 16825, "spiritWellBought"),
                std::make_tuple(UberStateGroup::GromShop, 51230, "housesABought"),
                std::make_tuple(UberStateGroup::GromShop, 23607, "housesBBought"),
                std::make_tuple(UberStateGroup::GromShop, 40448, "housesCBought"),
                std::make_tuple(UberStateGroup::GromShop, 18751, "removeThornsBought"),
                std::make_tuple(UberStateGroup::GromShop, 16586, "openCaveBought"),
                std::make_tuple(UberStateGroup::GromShop, 15068, "beautifyBought"),
                // Tuley
                std::make_tuple(UberStateGroup::TuleyShop, 47651, "lightcatchers"),
                std::make_tuple(UberStateGroup::TuleyShop, 16254, "selaFlowers"),
                std::make_tuple(UberStateGroup::TuleyShop, 33011, "blueMoon"),
                std::make_tuple(UberStateGroup::TuleyShop, 64583, "stickyGrass"),
                std::make_tuple(UberStateGroup::TuleyShop, 38393, "springPlants"),
                std::make_tuple(UberStateGroup::TuleyShop, 40006, "lastTree"),
            };

            for (auto const& [slot_group, state, name]: shop_data) {
                register_virtual_state(
                    {
                        .type = ValueType::Boolean,
                        .group = slot_group,
                        .state = state,
                        .name = name,
                    },
                    core::Property<double>(
                        [state](const double x) { UberState(42178, state).set(x > 0.5 ? 3 : 1); },
                        [state] -> double { return UberState(42178, state).get<int>() >= 3 ? 1 : 0; }
                    )
                );
            }

            constexpr std::array skills = {
                std::make_tuple(app::AbilityType__Enum::Bash, "bash"),
                std::make_tuple(app::AbilityType__Enum::WallJump, "wallJump"),
                std::make_tuple(app::AbilityType__Enum::DoubleJump, "doubleJump"),
                std::make_tuple(app::AbilityType__Enum::ChargeJump, "launch"),
                std::make_tuple(app::AbilityType__Enum::Glide, "glide"),
                std::make_tuple(app::AbilityType__Enum::WaterBreath, "waterBreath"),
                std::make_tuple(app::AbilityType__Enum::Grenade, "grenade"),
                std::make_tuple(app::AbilityType__Enum::SpiritLeash, "grapple"),
                std::make_tuple(app::AbilityType__Enum::GlowSpell, "flash"),
                std::make_tuple(app::AbilityType__Enum::SpiritSpearSpell, "spear"),
                std::make_tuple(app::AbilityType__Enum::MeditateSpell, "regenerate"),
                std::make_tuple(app::AbilityType__Enum::Bow, "bow"),
                std::make_tuple(app::AbilityType__Enum::Hammer, "hammer"),
                std::make_tuple(app::AbilityType__Enum::Torch, "torch"),
                std::make_tuple(app::AbilityType__Enum::Sword, "sword"),
                std::make_tuple(app::AbilityType__Enum::Digging, "burrow"),
                std::make_tuple(app::AbilityType__Enum::DashNew, "dash"),
                std::make_tuple(app::AbilityType__Enum::WaterDash, "waterDash"),
                std::make_tuple(app::AbilityType__Enum::ChakramSpell, "shuriken"),
                std::make_tuple(app::AbilityType__Enum::GoldenSein, "sein"),
                std::make_tuple(app::AbilityType__Enum::Blaze, "blaze"),
                std::make_tuple(app::AbilityType__Enum::TurretSpell, "sentry"),
                std::make_tuple(app::AbilityType__Enum::FeatherFlap, "flap"),
                std::make_tuple(app::AbilityType__Enum::DamageUpgradeA, "gladesAncestralLight"),
                std::make_tuple(app::AbilityType__Enum::DamageUpgradeB, "inkwaterAncestralLight"),
                std::make_tuple(app::AbilityType__Enum::SpiritFlame, "spiritFlame"),
                std::make_tuple(app::AbilityType__Enum::UltraDefense, "resilience"),
                std::make_tuple(app::AbilityType__Enum::HealthEfficiency, "healthEfficiency"),
                std::make_tuple(app::AbilityType__Enum::EnergyEfficiency, "energyEfficiency"),
                std::make_tuple(app::AbilityType__Enum::BowCharge, "bowCharge"),
                std::make_tuple(app::AbilityType__Enum::SpiritMagnet, "spiritMagnet"),
                std::make_tuple(app::AbilityType__Enum::WeaponCharge, "weaponCharge"),
            };

            for (const auto& [type, name]: skills) {
                register_virtual_state(
                    {
                        .type = ValueType::Boolean,
                        .group = UberStateGroup::Skills,
                        .state = static_cast<int>(type),
                        .name = name,
                    },
                    core::Property<double>(
                        [type](const double x) { ability(type).set(x > 0.5); },
                        [type]() -> double { return ability(type).get(); }
                    )
                );
            }

            constexpr std::array shards = {
                std::make_tuple(app::SpiritShardType__Enum::GlassCannon, "overcharge"),
                std::make_tuple(app::SpiritShardType__Enum::TripleJump, "tripleJump"),
                std::make_tuple(app::SpiritShardType__Enum::AntiAir, "wingclip"),
                std::make_tuple(app::SpiritShardType__Enum::Focus, "bounty"),
                std::make_tuple(app::SpiritShardType__Enum::Swap, "swap"),
                std::make_tuple(app::SpiritShardType__Enum::CrescentShot_Deprecated, "crescentShotDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Pierce, "pierce"),
                std::make_tuple(app::SpiritShardType__Enum::SpiritMagnet, "magnet"),
                std::make_tuple(app::SpiritShardType__Enum::Splinter, "splinter"),
                std::make_tuple(app::SpiritShardType__Enum::Blaze_Deprecated, "blazeDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Frost_Deprecated, "frostDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::LifeLeech_Deprecated, "lifeLeechDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Reckless, "reckless"),
                std::make_tuple(app::SpiritShardType__Enum::Frenzy, "quickshot"),
                std::make_tuple(app::SpiritShardType__Enum::Explosive_Deprecated, "explosiveDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Ricochet, "ricochet"),
                std::make_tuple(app::SpiritShardType__Enum::Climb_Deprecated, "climbDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Barrier, "resilience"),
                std::make_tuple(app::SpiritShardType__Enum::SpiritLightLuck, "spiritLightHarvest"),
                std::make_tuple(app::SpiritShardType__Enum::Compass_Deprecated, "compassDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Waterbreathing_Deprecated, "waterbreathingDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Vitality, "vitality"),
                std::make_tuple(app::SpiritShardType__Enum::VitalityLuck, "lifeHarvest"),
                std::make_tuple(app::SpiritShardType__Enum::SpiritWellShield_Deprecated, "spiritWellShieldDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::EnergyLuck, "energyHarvest"),
                std::make_tuple(app::SpiritShardType__Enum::Energy, "energy"),
                std::make_tuple(app::SpiritShardType__Enum::BloodPact, "lifePact"),
                std::make_tuple(app::SpiritShardType__Enum::LastResort, "lastStand"),
                std::make_tuple(app::SpiritShardType__Enum::HarvestOfLight_Deprecated, "harvestOfLightDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Sense, "sense"),
                std::make_tuple(app::SpiritShardType__Enum::UnderwaterEfficiency_Deprecated, "underwaterEfficiencyDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::UltraBash, "ultraBash"),
                std::make_tuple(app::SpiritShardType__Enum::UltraLeash, "ultraGrapple"),
                std::make_tuple(app::SpiritShardType__Enum::Recycler, "overflow"),
                std::make_tuple(app::SpiritShardType__Enum::Counterstrike, "thorn"),
                std::make_tuple(app::SpiritShardType__Enum::HollowEnergy, "catalyst"),
                std::make_tuple(app::SpiritShardType__Enum::Supressor, "supressor"),
                std::make_tuple(app::SpiritShardType__Enum::Aggressor, "turmoil"),
                std::make_tuple(app::SpiritShardType__Enum::Glue, "sticky"),
                std::make_tuple(app::SpiritShardType__Enum::CombatLuck, "finesse"),
                std::make_tuple(app::SpiritShardType__Enum::SpiritPower, "spiritSurge"),
                std::make_tuple(app::SpiritShardType__Enum::Overcharge_Deprecated, "overchargeDeprecated"),
                std::make_tuple(app::SpiritShardType__Enum::Untouchable, "lifeforce"),
                std::make_tuple(app::SpiritShardType__Enum::MirrorStrike, "deflector"),
                std::make_tuple(app::SpiritShardType__Enum::Stinger, "stinger"),
                std::make_tuple(app::SpiritShardType__Enum::Fracture, "fracture"),
                std::make_tuple(app::SpiritShardType__Enum::ChainLightning, "arcing"),
            };

            for (const auto& [type, name]: shards) {
                register_virtual_state(
                    {
                        .type = ValueType::Boolean,
                        .group = UberStateGroup::Shards,
                        .state = static_cast<int>(type),
                        .name = name,
                    },
                    core::Property<double>(
                        [type](const double x) { shard(type).set(x > 0.5); },
                        [type]() -> double { return shard(type).get(); }
                    )
                );
            }

            area_segment_states::register_virtual_uber_states();
            dev::print_time(start_time, "Virtual states initialized");

            dev::print_time(start_time, "Uber states initialized");
        }
    } // namespace
} // namespace randomizer
