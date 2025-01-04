#include <Randomizer/conditions/new_setup_state_override.h>
#include <Randomizer/features/wheel.h>
#include <Randomizer/game/shops/shop.h>
#include <Randomizer/game/teleport.h>
#include <Randomizer/randomizer.h>
#include <Randomizer/seed/items/apply_uber_state.h>
#include <Randomizer/seed/items/call.h>
#include <Randomizer/seed/items/counting_message.h>
#include <Randomizer/seed/items/empty.h>
#include <Randomizer/seed/items/icon.h>
#include <Randomizer/seed/items/message.h>
#include <Randomizer/seed/items/refill.h>
#include <Randomizer/seed/items/value_modifier.h>
#include <Randomizer/seed/legacy_parser/parser.h>
#include <Randomizer/timer.h>

#include <Common/ext.h>

#include <Core/api/game/game.h>
#include <Core/api/game/player.h>
#include <Core/api/graphics/textures.h>
#include <Core/api/uber_states/uber_state_condition.h>
#include <Core/core.h>
#include <Core/settings.h>
#include <Core/text/text_database.h>

#include <Modloader/il2cpp_math.h>
#include <Modloader/modloader.h>
#include <Randomizer/seed/items/input.h>

#include <Randomizer/seed/items/icon_override.h>
#include <fstream>
#include <iostream>
#include <magic_enum.hpp>
#include <regex>
#include <span>
#include <string>

namespace randomizer::seed::legacy_parser {
    using location_type = core::api::uber_states::UberStateCondition;
    // Hacky way to do it, but can't be bothered to pass it all the way down.
    location_data::LocationCollection const* current_location_data = nullptr;

    struct ParserData {
        std::shared_ptr<Seed::Data> data;
        ItemData& location_data;
        int items_added;
        int& next_location_id;
        int& next_procedure_id;
        bool should_add_to_always_granted;
        bool should_add_default_messages;

        int line_number;
        std::string item_definition;

        void add_item(ItemData::item_entry entry) {
            ++items_added;
            entry->seed_line_number = line_number;
            entry->seed_definition = item_definition;
            auto& collection = should_add_to_always_granted ? location_data.always_granted_items : location_data.items;
            collection[next_location_id++] = std::move(entry);
        }
    };

    enum class ActionType {
        SpiritLight = 0,
        Resource = 1,
        Ability = 2,
        Shard = 3,
        SystemCommand = 4,
        Teleporter = 5,
        Message = 6,
        UberState = 8,
        QuestEvent = 9,
        BonusItem = 10,
        WeaponUpgrade = 11,
        ZoneHint = 12,
        CheckableHint = 13,
        Relic = 14,
        SysMessage = 15,
        Wheel = 16,
        Shop = 17,
        SetMapMessage = 18
    };

    enum class ResourceType { Health = 0, Energy = 1, Ore = 2, Keystone = 3, ShardSlot = 4 };

    enum class SystemCommand {
        Save = 0,
        SetResource = 1,
        Checkpoint = 2,
        SupressMagic = 3,
        StopIfEqual = 4,
        StopIfGreater = 5,
        StopIfLess = 6,
        SetState = 7,
        Warp = 8,
        RedirectState = 11,
        SetHealth = 12,
        SetEnergy = 13,
        SetSpiritLight = 14,
        Bind = 15,
        InputAction = 16,
        GrantIfEqual = 17,
        GrantIfGreater = 18,
        GrantIfLess = 19,
        DisableSync = 20,
        EnableSync = 21,
        CreateWarp = 22,
        DestroyWarp = 23,
        GrantIfBounds = 24,
        GrantIfCondEqual = 25,
        GrantIfCondGreater = 26,
        GrantIfCondLess = 27,
        Unbind = 28,
        SaveString = 29,
        AppendString = 30,
        SetIconOverride = 31,
        ClearIconOverride = 32,
    };

    void set_location(items::Message* message, location_type const& location) {
        auto const& location_data = current_location_data->location(location);
        if (location_data.has_value() && location_data.value().position.has_value()) {
            const auto [x, y] = location_data.value().position.value();
            message->info.pickup_position = app::Vector3{x, y, 0};
        }
    }

    bool parse_action(location_type const& location, std::span<std::string> parts, ParserData& data);

    std::string concatenate_parts(std::span<std::string> const& parts) {
        return std::accumulate(parts.begin(), parts.end(), std::string(), [](std::string const& ss, std::string const& s) {
            return ss.empty() ? s : std::format("{}|{}", ss, s);
        });
    }

    void parse_parts(const std::string_view str, std::vector<std::string>& parts) {
        enum class ReadMode { Normal, Ptr };

        std::string next;
        auto mode = ReadMode::Normal;
        std::stringstream stream((std::string(str)));
        char c = static_cast<char>(stream.get());
        while (!stream.eof()) {
            if (mode == ReadMode::Normal && c == '|') {
                parts.push_back(next);
                next.clear();
            } else if (mode == ReadMode::Normal && c == '$' && stream.peek() == '(') {
                mode = ReadMode::Ptr;
                next += c;
            } else if (mode == ReadMode::Ptr && c == ')') {
                mode = ReadMode::Normal;
                next += c;
            } else {
                next += c;
            }

            c = static_cast<char>(stream.get());
        }

        parts.push_back(next);
    }

    bool parse_spirit_light(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int spirit_light;
        if (!string_convert(parts[0], spirit_light)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto assigner = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
        assigner->variable = core::api::game::player::spirit_light();
        assigner->value.set(spirit_light);
        data.add_item(assigner);

        const auto collected = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
        collected->variable = core::Property<int>(UberStateGroup::RandoStats, 3);
        collected->value.set(spirit_light);
        data.add_item(collected);

        if (!data.should_add_default_messages) {
            return true;
        }

        std::string currency = "Spirit Light";
        if (!core::settings::use_default_currency_name()) {
            const auto slug_hash = std::hash<std::string>()(data.data->info.meta.slug);
            const auto location_hash = std::hash<location_type>()(location);
            currency = core::text::get_random_text_with_hash(
                spirit_light == 1
                    ? *static_text_entry::CurrencySingular
                    : *static_text_entry::CurrencyPlural,
                slug_hash ^ location_hash
            );
        }

        const auto text = std::format("{} {}", spirit_light, currency);
        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        message->info.text.set(text);

        data.add_item(message);
        data.location_data.names.emplace_back(message->info.text);
        data.location_data.icons.emplace_back(MapIcon::Experience);

        return true;
    }

    bool parse_resource(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int resource_type_int;
        if (!string_convert(parts[0], resource_type_int)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        MapIcon icon;
        switch (static_cast<ResourceType>(resource_type_int)) {
            case ResourceType::Health: {
                const auto adder = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                adder->variable = core::api::game::player::max_health();
                adder->value.set(5);
                data.add_item(adder);
                const auto refill = std::make_shared<items::Refill>();
                refill->type = items::Refill::RefillType::Health;
                data.add_item(refill);
                icon = MapIcon::HealthFragment;
                message->info.text.set("Health Fragment");
                break;
            }
            case ResourceType::Energy: {
                const auto adder = std::make_shared<items::ValueModifier<float, items::ValueOperator::Add>>();
                adder->variable = core::api::game::player::max_energy();
                adder->value.set(0.5f);
                data.add_item(adder);
                const auto refill = std::make_shared<items::Refill>();
                refill->type = items::Refill::RefillType::Energy;
                data.add_item(refill);
                icon = MapIcon::EnergyFragment;
                message->info.text.set("Energy Fragment");
                break;
            }
            case ResourceType::Ore: {
                const auto adder = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                adder->variable = core::api::game::player::ore();
                adder->value.set(1);
                data.add_item(adder);
                const auto collected = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                collected->variable = core::Property<int>(UberStateGroup::RandoStats, 5);
                collected->value.set(1);
                data.add_item(collected);
                icon = MapIcon::Ore;
                message->info.text.set("Gorlek Ore");
                break;
            }
            case ResourceType::Keystone: {
                const auto adder = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                adder->variable = core::api::game::player::keystones();
                adder->value.set(1);
                data.add_item(adder);
                const auto collected = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                collected->variable = core::Property<int>(UberStateGroup::RandoStats, 0);
                collected->value.set(1);
                data.add_item(collected);
                icon = MapIcon::Keystone;
                message->info.text.set("Keystone");
                break;
            }
            case ResourceType::ShardSlot: {
                const auto adder = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
                adder->variable = core::api::game::player::shard_slots();
                adder->value.set(1);
                data.add_item(adder);
                icon = MapIcon::ShardSlotUpgrade;
                message->info.text.set("Shard Slot");
                break;
            }
            default:
                return false;
        }

        if (!data.should_add_default_messages) {
            return true;
        }

        data.add_item(message);
        data.location_data.names.emplace_back(message->info.text);
        data.location_data.icons.emplace_back(icon);
        return true;
    }

    bool parse_ability(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int ability_type_int;
        if (!string_convert(parts[0], ability_type_int)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto should_add = !parts[0].starts_with("-");
        ability_type_int = should_add ? ability_type_int : -ability_type_int;
        const auto assigner = std::make_shared<items::ValueModifier<bool, items::ValueOperator::Assign>>();
        assigner->variable.assign(core::api::uber_states::UberState(UberStateGroup::Skills, ability_type_int));
        assigner->value.set(should_add);
        data.add_item(assigner);

        if (!data.should_add_default_messages) {
            return true;
        }

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        const auto text = should_add ? std::format("[ability({0})]", ability_type_int) : std::format("Removed [ability({0})]", ability_type_int);
        message->info.text.set(text);
        data.add_item(message);
        data.location_data.icons.emplace_back(MapIcon::AbilityPedestal);
        data.location_data.names.emplace_back(text);
        return true;
    }

    bool parse_shard(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int shard_type_int;
        if (!string_convert(parts[0], shard_type_int)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto should_add = !parts[0].starts_with("-");
        shard_type_int = should_add ? shard_type_int : -shard_type_int;
        const auto shard_type = static_cast<app::SpiritShardType__Enum>(shard_type_int);
        const auto assigner = std::make_shared<items::ValueModifier<bool, items::ValueOperator::Assign>>();
        assigner->variable = core::api::game::player::shard(shard_type);
        assigner->value.set(should_add);
        data.add_item(assigner);

        if (!data.should_add_default_messages) {
            return true;
        }

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        const auto text = should_add ? std::format("[shard({0})]", shard_type_int) : std::format("Removed [shard({0})]", shard_type_int);
        message->info.text.set(text);
        data.add_item(message);
        data.location_data.icons.emplace_back(MapIcon::SpiritShard);
        data.location_data.names.emplace_back(text);
        return true;
    }

    bool parse_stop_if(std::span<std::string> parts, ParserData& data, BooleanOperator op) {
        int group;
        int state;
        double value;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state) || !string_convert(parts[2], value)) {
            return false;
        }

        const auto stop_condition = core::api::uber_states::UberStateCondition{{group, state}, op, value};
        const auto stop = std::make_shared<items::Empty>();
        stop->stop.assign([](auto) {}, [stop_condition]() { return stop_condition.resolve(); });

        data.add_item(stop);
        return true;
    }

    bool parse_grant_if_state( // NOLINT
        location_type const& location,
        core::api::uber_states::UberState const& state,
        std::span<std::string> parts,
        ParserData& data,
        BooleanOperator op
    ) {
        if (parts.size() < 2) {
            return false;
        }

        double value;
        if (!string_convert(parts[0], value)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto skip = std::make_shared<items::Empty>();
        auto condition = core::api::uber_states::UberStateCondition{{state.group(), state.state()}, op, value};
        data.add_item(skip);
        auto skip_value = data.items_added;

        const auto sub_parts = std::span(parts.begin() + 1, parts.end());
        data.item_definition = concatenate_parts(sub_parts);
        parse_action(location, sub_parts, data);

        skip_value = data.items_added - skip_value;
        skip->skip.assign(core::set_get<int>{
            [](int) {},
            [condition, skip_value] { return condition.resolve() ? 0 : skip_value; },
        });

        return true;
    }

    bool parse_grant_if( // NOLINT
        location_type const& location,
        std::span<std::string> parts,
        ParserData& data,
        BooleanOperator op
    ) {
        if (parts.size() < 2) {
            return false;
        }

        int group;
        int state;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state)) {
            return false;
        }

        const auto sub_parts = std::span<std::string>(parts.begin() + 2, parts.end());
        return parse_grant_if_state(location, {group, state}, sub_parts, data, op);
    }

    bool parse_grant_if_bounds( // NOLINT
        location_type const& location,
        std::span<std::string> parts,
        ParserData& data
    ) {
        if (parts.size() < 4) {
            return false;
        }

        app::Rect rect{};
        if (!string_convert(parts[0], rect.m_XMin) || !string_convert(parts[1], rect.m_YMin) || !string_convert(parts[2], rect.m_Width) ||
            !string_convert(parts[3], rect.m_Height)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        if (rect.m_XMin > rect.m_Width) {
            std::swap(rect.m_XMin, rect.m_Width);
        }

        if (rect.m_YMin > rect.m_Height) {
            std::swap(rect.m_YMin, rect.m_Height);
        }

        rect.m_Width -= rect.m_XMin;
        rect.m_Height -= rect.m_YMin;

        const auto skip = std::make_shared<items::Empty>();
        data.add_item(skip);
        auto skip_value = data.items_added;

        const auto sub_parts = std::span(parts.begin() + 1, parts.end());
        parse_action(location, sub_parts, data);

        skip_value = data.items_added - skip_value;
        skip->skip.assign(core::set_get<int>{
            [](int value) {},
            [rect, skip_value]() { return modloader::math::in_rect(core::api::game::player::get_position(), rect) ? 0 : skip_value; },
        });

        return true;
    }

    bool parse_save(std::span<std::string> parts, ParserData& data, bool checkpoint) {
        const auto caller = std::make_shared<items::Call>();

        std::optional<app::Vector2> override_position = std::nullopt;

        if (parts.size() >= 2) {
            app::Vector2 position;
            if (!string_convert(parts[0], position.x) || !string_convert(parts[1], position.y)) {
                return false;
            }
            override_position = position;
        }

        core::api::game::SaveOptions save_options(
            false, false, !checkpoint, false, override_position
        );

        caller->description = checkpoint ? "do checkpoint" : "do save";

        if (override_position.has_value()) {
            caller->description += std::format(" at {}, {}", override_position->x, override_position->y);
        }

        caller->func = [save_options] {
            if (core::api::game::can_save()) {
                core::api::game::save(false, save_options);
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_warp(std::span<std::string> parts, ParserData& data) {
        if (parts.size() < 2) {
            return false;
        }

        app::Vector3 position{};
        if (!string_convert(parts[0], position.x) || !string_convert(parts[1], position.y)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = "warp player";
        caller->func = [position]() { game::teleportation::teleport_instantly(position); };
        data.add_item(caller);
        return true;
    }

    bool parse_redirect_state(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        conditions::applier_key key;
        int state;
        if (!string_convert(parts[1], key.second) || !string_convert(parts[2], state)) {
            return false;
        }

        key.first = parts[0];
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("register redirect {}:{}", key.first, key.second);
        caller->func = [key, state]() { conditions::register_new_setup_redirect(key, state); };
        data.add_item(caller);
        return true;
    }

    bool parse_bind(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 2) {
            return false;
        }

        int binding;
        int equip;
        if (!string_convert(parts[0], binding) || !string_convert(parts[1], equip)) {
            return false;
        }

        if (binding < 0 || binding > 2) {
            return false;
        }

        auto binding_type = static_cast<app::SpellInventory_Binding__Enum>(binding);
        auto equip_type = static_cast<app::EquipmentType__Enum>(equip);

        if (!core::api::game::player::is_valid_equipment(equip_type)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("equip {} to binding {}", equip, binding);
        caller->func = [binding_type, equip_type]() { core::api::game::player::bind(binding_type, equip_type); };
        data.add_item(caller);
        return true;
    }

    bool parse_unbind(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int equip;
        if (!string_convert(parts[0], equip)) {
            return false;
        }

        auto equip_type = static_cast<app::EquipmentType__Enum>(equip);
        if (!core::api::game::player::is_valid_equipment(equip_type)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("unbind {}", static_cast<int>(equip_type));
        caller->func = [equip_type]() { core::api::game::player::unbind(equip_type); };
        data.add_item(caller);
        return true;
    }

    bool parse_sync(std::span<std::string> parts, ParserData& data, bool unsyncable) {
        if (parts.size() != 2) {
            return false;
        }

        int group;
        int state;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state)) {
            return false;
        }

        core::api::uber_states::UberState sync_state(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("set unsyncable {}", sync_state.to_string());
        caller->func = [sync_state, unsyncable]() { multiplayer_universe().uber_state_handler().set_unsyncable(sync_state, unsyncable); };
        data.add_item(caller);
        return true;
    }

    bool parse_create_warp(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 4) {
            return false;
        }

        const auto icon = std::make_shared<items::CreateIcon>();
        if (!string_convert(parts[0], icon->id) || !string_convert(parts[1], icon->position.x) || !string_convert(parts[2], icon->position.y)) {
            return false;
        }

        icon->label = parts[3];
        icon->flags = game::map::FilterFlag::All | game::map::FilterFlag::Teleports | game::map::FilterFlag::InLogic | game::map::FilterFlag::Spoilers;
        icon->type = MapIcon::SavePedestal;
        icon->can_teleport = true;
        data.add_item(icon);
        return true;
    }

    bool parse_destroy_warp(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        const auto icon = std::make_shared<items::DestroyIcon>();
        if (!string_convert(parts[0], icon->id)) {
            return false;
        }

        data.add_item(icon);
        return true;
    }

    bool parse_string(std::span<std::string> parts, ParserData& data, bool append) {
        if (parts.size() < 2) {
            return false;
        }

        int id;
        if (!string_convert(parts[0], id)) {
            return false;
        }

        std::string text;
        for (auto it = parts.begin() + 1; it != parts.end(); ++it) {
            if (!text.empty()) {
                text += "|";
            }

            text += *it;
        }

        auto caller = std::make_shared<items::Call>();
        caller->description = append ? std::format("append \"{}\" to text entry {}", text, id) : std::format("set text entry {} to \"{}\"", id, text);
        caller->func = [append, id, text]() {
            auto mutable_text = text;
            general_text_processor()->process(*general_text_processor(), mutable_text);
            std::string actual_text(append ? core::text::get_text(id) : "");
            actual_text += mutable_text;
            core::text::clear_text(id);
            core::text::register_text(id, actual_text);
        };

        data.add_item(caller);
        return true;
    }

    bool parse_input_action(const std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        const auto action = magic_enum::enum_cast<Action>(parts[0]);
        if (!action.has_value()) {
            return false;
        }

        const auto input = std::make_shared<items::Input>();
        input->action = action.value();
        data.add_item(input);
        return true;
    }
    bool parse_set_icon_override(const std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        core::api::uber_states::UberStateCondition location;
        if (!parse_condition(std::span(parts.begin(), parts.begin() + 2), location)) {
            return false;
        }

        const auto icon = magic_enum::enum_cast<MapIcon>(parts[2]);
        if (!icon.has_value()) {
            return false;
        }

        const auto item = std::make_shared<items::SetIconOverride>();
        item->data = data.data;
        item->location = location;
        item->icon = icon.value();
        data.add_item(item);
        return true;
    }

    bool parse_clear_icon_override(const std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 2) {
            return false;
        }

        core::api::uber_states::UberStateCondition location;
        if (!parse_condition(std::span(parts.begin(), parts.begin() + 2), location)) {
            return false;
        }

        const auto item = std::make_shared<items::ClearIconOverride>();
        item->data = data.data;
        item->location = location;
        data.add_item(item);
        return true;
    }

    bool parse_sys_command(location_type const& location, std::span<std::string> parts, ParserData& data) {
        // NOLINT
        int sys_command_int;
        if (!string_convert(parts[0], sys_command_int)) {
            return false;
        }

        const auto sys_command = static_cast<SystemCommand>(sys_command_int);
        const auto next_parts = std::span<std::string>(parts.begin() + 1, parts.end());
        switch (sys_command) {
            case SystemCommand::Save:
                return parse_save(next_parts, data, false);
            case SystemCommand::Checkpoint:
                return parse_save(next_parts, data, true);
            case SystemCommand::StopIfEqual:
                return parse_stop_if(next_parts, data, BooleanOperator::Equals);
            case SystemCommand::StopIfGreater:
                return parse_stop_if(next_parts, data, BooleanOperator::Greater);
            case SystemCommand::StopIfLess:
                return parse_stop_if(next_parts, data, BooleanOperator::Lesser);
            case SystemCommand::GrantIfEqual:
                return parse_grant_if(location, next_parts, data, BooleanOperator::Equals);
            case SystemCommand::GrantIfGreater:
                return parse_grant_if(location, next_parts, data, BooleanOperator::Greater);
            case SystemCommand::GrantIfLess:
                return parse_grant_if(location, next_parts, data, BooleanOperator::Lesser);
            case SystemCommand::GrantIfCondEqual:
                return parse_grant_if_state(location, location.state, next_parts, data, BooleanOperator::Equals);
            case SystemCommand::GrantIfCondGreater:
                return parse_grant_if_state(location, location.state, next_parts, data, BooleanOperator::Greater);
            case SystemCommand::GrantIfCondLess:
                return parse_grant_if_state(location, location.state, next_parts, data, BooleanOperator::Lesser);
            case SystemCommand::GrantIfBounds:
                return parse_grant_if_bounds(location, next_parts, data);
            case SystemCommand::Warp:
                return parse_warp(next_parts, data);
            case SystemCommand::RedirectState:
                return parse_redirect_state(next_parts, data);
            case SystemCommand::Bind:
                return parse_bind(next_parts, data);
            case SystemCommand::Unbind:
                return parse_unbind(next_parts, data);
            case SystemCommand::EnableSync:
                return parse_sync(next_parts, data, false);
            case SystemCommand::DisableSync:
                return parse_sync(next_parts, data, true);
            case SystemCommand::CreateWarp:
                return parse_create_warp(next_parts, data);
            case SystemCommand::DestroyWarp:
                return parse_destroy_warp(next_parts, data);
            case SystemCommand::SaveString:
                return parse_string(next_parts, data, false);
            case SystemCommand::AppendString:
                return parse_string(next_parts, data, true);
            case SystemCommand::InputAction:
                return parse_input_action(next_parts, data);
            case SystemCommand::SetIconOverride:
                return parse_set_icon_override(next_parts, data);
            case SystemCommand::ClearIconOverride:
                return parse_clear_icon_override(next_parts, data);
            case SystemCommand::SetHealth:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SetHealth use virtual uber states instead.");
                return false;
            case SystemCommand::SetEnergy:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SetEnergy use virtual uber states instead.");
                return false;
            case SystemCommand::SetSpiritLight:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SetSpiritLight use virtual uber states instead.");
                return false;
            case SystemCommand::SetResource:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SetResource use virtual uber states instead.");
                return false;
            case SystemCommand::SupressMagic:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SuppressMagic use virtual uber states instead.");
                return false;
            case SystemCommand::SetState:
                modloader::warn("legacy_parser", "Use of deprecated command SystemCommand.SetState use uber states instead.");
                return false;
            default:
                return false;
        }
    }

    bool parse_teleporter(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int teleporter_int;
        if (!string_convert(parts[0], teleporter_int)) {
            return false;
        }

        const auto line = concatenate_parts(parts);

        const auto should_add = !parts[0].starts_with("-");
        teleporter_int = should_add ? teleporter_int : -teleporter_int;
        const auto assigner = std::make_shared<items::ValueModifier<bool, items::ValueOperator::Assign>>();
        assigner->value.set(should_add);
        auto teleporter_name = "Unknown";
        switch (teleporter_int) {
            case 0:
                assigner->variable.assign(core::api::uber_states::UberState(24922, 42531));
                teleporter_name = "Midnight Burrows";
                break;
            case 1:
                assigner->variable.assign(core::api::uber_states::UberState(11666, 61594));
                teleporter_name = "Howl's Den";
                break;
            case 3:
                assigner->variable.assign(core::api::uber_states::UberState(53632, 18181));
                teleporter_name = "Wellspring";
                break;
            case 4:
                assigner->variable.assign(core::api::uber_states::UberState(28895, 54235));
                teleporter_name = "Baur's Reach";
                break;
            case 5:
                assigner->variable.assign(core::api::uber_states::UberState(937, 26601));
                teleporter_name = "Kwolok's Hollow";
                break;
            case 6:
                assigner->variable.assign(core::api::uber_states::UberState(18793, 38871));
                teleporter_name = "Mouldwood Depths";
                break;
            case 7:
                assigner->variable.assign(core::api::uber_states::UberState(58674, 7071));
                teleporter_name = "Woods Entrance";
                break;
            case 8:
                assigner->variable.assign(core::api::uber_states::UberState(58674, 1965));
                teleporter_name = "Woods Exit";
                break;
            case 9:
                assigner->variable.assign(core::api::uber_states::UberState(58674, 10029));
                teleporter_name = "Feeding Grounds";
                break;
            case 10:
                assigner->variable.assign(core::api::uber_states::UberState(20120, 49994));
                teleporter_name = "Central Wastes";
                break;
            case 11:
                assigner->variable.assign(core::api::uber_states::UberState(20120, 41398));
                teleporter_name = "Outer Ruins";
                break;
            case 12:
                assigner->variable.assign(core::api::uber_states::UberState(16155, 41465));
                teleporter_name = "Willow's End";
                break;
            case 14:
                assigner->variable.assign(core::api::uber_states::UberState(10289, 4928));
                teleporter_name = "Inner Ruins";
                break;
            case 2: {
                assigner->variable.assign(core::api::uber_states::UberState(945, 58183));
                teleporter_name = "Central Luma";
                if (should_add) {
                    auto lower_water = std::make_shared<items::ValueModifier<bool, items::ValueOperator::Assign>>();
                    lower_water->variable.assign(core::api::uber_states::UberState(5377, 63173));
                    lower_water->value.set(should_add);
                    data.add_item(lower_water);
                }
                break;
            }
            case 13:
                assigner->variable.assign(core::api::uber_states::UberState(945, 1370));
                teleporter_name = "Luma Boss";
                break;
            case 15:
                assigner->variable.assign(core::api::uber_states::UberState(16155, 50867));
                teleporter_name = "Shriek";
                break;
            case 16:
                assigner->variable.assign(core::api::uber_states::UberState(21786, 10185));
                teleporter_name = "Inkwater Marsh";
                break;
            case 17:
                assigner->variable.assign(core::api::uber_states::UberState(42178, 42096));
                teleporter_name = "Glades";
                break;
            default:
                return false;
        }

        data.add_item(assigner);
        if (!data.should_add_default_messages) {
            return true;
        }

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        const auto text = should_add ? std::format("#{0} TP#", teleporter_name) : std::format("Removed #{0} TP#", teleporter_name);
        message->info.text.set(text);
        data.add_item(message);
        data.location_data.icons.emplace_back(MapIcon::SavePedestalInactive);
        data.location_data.names.emplace_back(text);
        return true;
    }

    bool parse_message(location_type const& location, std::span<std::string> parts, ParserData& data) {
        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        message->info.duration = 4;
        std::string text;
        for (const auto& part: parts) {
            if (part.starts_with("f=")) {
                if (int frames; string_convert(part.substr(2), frames)) {
                    message->info.duration = static_cast<float>(frames) / 60.f;
                }
            } else if (part.starts_with("p=")) {
                // Not used anymore.
            } else if (part == "noclear") {
                // Not used anymore.
            } else if (part == "quiet") {
                message->info.play_sound = false;
            } else if (part == "instant" || part == "prioritized") {
                message->info.prioritized = true;
                message->should_add_to_recent = false;
            } else if (part == "nofade") {
                message->info.instant_fade = true;
            } else if (part == "prepend") {
                // Not used anymore.
            } else {
                if (!text.empty()) {
                    text += "|";
                }

                text += part;
            }
        }

        message->info.text.set(text);
        data.add_item(message);
        data.location_data.names.emplace_back(text);
        return true;
    }

    std::regex ptr_regex(R"(\$\(([0-9]+)\|([0-9]+)\))");
    std::regex range_regex(R"(\[([^,\]]+),([^,\]]+)\])");

    bool gen_from_frag(const std::string& frag, core::Property<double>& value) {
        std::smatch results;
        if (std::regex_match(frag, results, ptr_regex)) {
            int group;
            int state;
            string_convert(results[1].str(), group);
            string_convert(results[2].str(), state);
            value.assign(core::api::uber_states::UberState(group, state));
        } else {
            double constant_value;
            if (string_convert(frag, constant_value)) {
                value.set(constant_value);
            } else {
                return false;
            }
        }

        return true;
    }

    bool parse_uber_state(std::span<std::string> parts, ParserData& data) {
        if (parts.size() < 4 || parts.size() > 5) {
            return false;
        }

        int group;
        if (!string_convert(parts[0], group)) {
            return false;
        }

        int state;
        if (!string_convert(parts[1], state)) {
            return false;
        }

        // auto type = uberTypeFromString(extras[2]);
        const bool negative = parts[3].starts_with('-');
        const bool is_modifier = parts[3].starts_with('+') || negative;
        if (is_modifier) {
            parts[3] = parts[3].substr(1);
        }

        auto should_skip = false;
        if (parts.size() > 4) {
            if (!parts[4].starts_with("skip")) {
                return false;
            }

            should_skip = true;
        }

        const auto line = concatenate_parts(parts);
        if (std::smatch results; std::regex_match(parts[3], results, range_regex)) {
            core::Property<double> start;
            core::Property<double> end;
            gen_from_frag(results[0], start);
            gen_from_frag(results[1], end);

            auto setget = core::set_get<double>{
                [](auto value) {},
                [start, end, negative]() {
                const auto lower = start.get();
                const auto upper = end.get();
                const auto random_value = core::random();
                const auto sign = negative ? -1.f : 1.f;
                return sign * random_value * (upper - lower) + lower;
            },
            };

            if (is_modifier) {
                if (negative) {
                    auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Add>>();
                    setter->variable.assign(core::api::uber_states::UberState(group, state));
                    setter->value.assign(setget);
                    setter->should_skip_grants = should_skip;
                    data.add_item(setter);
                } else {
                    auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Sub>>();
                    setter->variable.assign(core::api::uber_states::UberState(group, state));
                    setter->value.assign(setget);
                    setter->should_skip_grants = should_skip;
                    data.add_item(setter);
                }
            } else {
                auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Add>>();
                setter->variable.assign(core::api::uber_states::UberState(group, state));
                setter->value.assign(setget);
                setter->should_skip_grants = should_skip;
                data.add_item(setter);
            }
        } else if (is_modifier) {
            if (negative) {
                auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Sub>>();
                setter->should_skip_grants = should_skip;
                setter->variable.assign(core::api::uber_states::UberState(group, state));
                gen_from_frag(parts[3], setter->value);
                data.add_item(setter);
            } else {
                auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Add>>();
                setter->should_skip_grants = should_skip;
                setter->variable.assign(core::api::uber_states::UberState(group, state));
                gen_from_frag(parts[3], setter->value);
                data.add_item(setter);
            }
        } else {
            auto setter = std::make_shared<items::ValueModifier<double, items::ValueOperator::Assign>>();
            setter->should_skip_grants = should_skip;
            setter->variable.assign(core::api::uber_states::UberState(group, state));
            gen_from_frag(parts[3], setter->value);
            data.add_item(setter);
        }

        return true;
    }

    bool parse_quest_event(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        // If we add more than one event, don't early out here.
        if (int quest_event_int; !string_convert(parts[0], quest_event_int) || quest_event_int != 0) {
            return false;
        }

        const auto line = concatenate_parts(parts);
        const auto should_add = !parts[0].starts_with("-");

        const auto assigner = std::make_shared<items::ValueModifier<bool, items::ValueOperator::Assign>>();
        assigner->value.set(should_add);
        assigner->variable.assign(core::api::uber_states::UberState(6, 2000));
        data.add_item(assigner);

        auto applier = std::make_shared<items::ApplyUberState>();
        applier->state = core::api::uber_states::UberState(937, 34641);
        data.add_item(applier);

        applier = std::make_shared<items::ApplyUberState>();
        applier->state = core::api::uber_states::UberState(37858, 12379);
        data.add_item(applier);

        applier = std::make_shared<items::ApplyUberState>();
        applier->state = core::api::uber_states::UberState(37858, 10720);
        data.add_item(applier);

        if (!data.should_add_default_messages) {
            return true;
        }

        auto quest_event = "Clean Water";
        const auto text = should_add ? std::format("{0}", quest_event) : std::format("Removed {0}", quest_event);

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        message->info.text.set_format("*{0}*", text);
        data.add_item(message);

        data.location_data.icons.emplace_back(MapIcon::CleanWater);
        data.location_data.names.emplace_back().set_format("*{0}*", text);

        return true;
    }

    bool parse_bonus_item(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int bonus_type_int;
        if (!string_convert(parts[0], bonus_type_int)) {
            return false;
        }

        std::string bonus_item;
        switch (bonus_type_int) {
            case 30:
                bonus_item = "Health Regeneration";
                break;
            case 31:
                bonus_item = "Energy Regeneration";
                break;
            case 35:
                bonus_item = "Extra Double Jump";
                break;
            case 36:
                bonus_item = "Extra Air Dash";
                break;
            default:
                return false;
        }

        const auto line = concatenate_parts(parts);

        const auto item = std::make_shared<items::ValueModifier<int, items::ValueOperator::Add>>();
        item->variable.assign(core::api::uber_states::UberState(UberStateGroup::RandoUpgrade, bonus_type_int));
        item->value.set(1);
        data.add_item(item);

        if (!data.should_add_default_messages) {
            return true;
        }

        const auto message = std::make_shared<items::Message>();
        set_location(message.get(), location);
        message->should_add_to_recent = true;
        message->info.text.set_format(R"(#{0}[if([state_int(4|{1})] > 1,<> x[state_int(4|{1})],)]#)", bonus_item, bonus_type_int);
        data.add_item(message);

        data.location_data.icons.emplace_back(MapIcon::BonusItem);
        data.location_data.names.emplace_back(message->info.text.get());

        return true;
    }

    std::string weapon_upgrade_name(const int id) {
        switch (id) {
            case 0:
                return "#Rapid Hammer#";
            case 1:
                return "#Rapid Sword#";
            case 2:
                return "#Blaze Efficiency#";
            case 3:
                return "#Spear Efficiency#";
            case 4:
                return "#Shuriken Efficiency#";
            case 5:
                return "#Sentry Efficiency#";
            case 6:
                return "#Bow Efficiency#";
            case 7:
                return "#Regeneration Efficiency#";
            case 8:
                return "#Flash Efficiency#";
            case 9:
                return "#Grenade Efficiency#";
            case 45:
                return "#Exploding Spear#";
            case 46:
                return "#Hammer Shockwave#";
            case 47:
                return "#Static Shuriken#";
            case 48:
                return "#Charge Blaze#";
            case 49:
                return "#Sentry Speed#";
            default:
                return "Unknown";
        }
    }

    bool parse_weapon_upgrade(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int weapon_upgrade_int;
        if (!string_convert(parts[0], weapon_upgrade_int)) {
            return false;
        }

        if (weapon_upgrade_int >= 0 && weapon_upgrade_int <= 9) {
            const auto increment = std::make_shared<items::ValueModifier<float, items::ValueOperator::Add>>();
            increment->variable.assign(core::api::uber_states::UberState(4, 50 + weapon_upgrade_int));
            increment->value.set(1.f);
            data.add_item(increment);
        }

        const auto item = std::make_shared<items::ValueModifier<float, items::ValueOperator::Assign>>();
        item->value.set(1.f);
        switch (weapon_upgrade_int) {
            case 0:
            case 1:
                item->variable.assign(core::api::uber_states::UberState(UberStateGroup::RandoUpgrade, weapon_upgrade_int));
                item->value.assign(core::set_get<float>{
                    [](auto value) {},
                    [weapon_upgrade_int]() { return std::powf(1.25f, core::api::uber_states::UberState(4, 50 + weapon_upgrade_int).get<float>()); },
                });
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
                item->variable.assign(core::api::uber_states::UberState(UberStateGroup::RandoUpgrade, weapon_upgrade_int));
                item->value.assign(core::set_get<float>{
                    [](auto value) {},
                    [weapon_upgrade_int]() { return std::powf(0.5f, core::api::uber_states::UberState(UberStateGroup::RandoUpgrade, 50 + weapon_upgrade_int).get<float>()); },
                });
                break;
            case 45:
                item->variable.assign(core::api::uber_states::UberState(3440, 5687));
                break;
            case 46:
                item->variable.assign(core::api::uber_states::UberState(3440, 46488));
                break;
            case 47:
                item->variable.assign(core::api::uber_states::UberState(3440, 10776));
                break;
            case 48:
                item->variable.assign(core::api::uber_states::UberState(3440, 61898));
                break;
            case 49:
                item->variable.assign(core::api::uber_states::UberState(3440, 57376));
                break;
            default:
                return false;
        }

        const auto line = concatenate_parts(parts);
        data.add_item(item);

        if (!data.should_add_default_messages) {
            return true;
        }

        std::string name = weapon_upgrade_name(weapon_upgrade_int);

        const auto message = std::make_shared<items::Message>();
        message->should_add_to_recent = true;
        message->info.text.set(name);
        set_location(message.get(), location);

        data.add_item(message);
        data.location_data.names.emplace_back(name);
        // TODO: Maybe add specific icons for the vanilla opher upgrades?
        data.location_data.icons.emplace_back(MapIcon::BonusItem);

        return true;
    }

    bool parse_relic(location_type const& location, std::span<std::string> parts, ParserData& data) {
        if (parts.size() > 2) {
            return false;
        }

        data.data->relics.add(location, parts.size() == 2 ? std::optional(parts[1]) : std::nullopt);

        if (!data.should_add_default_messages) {
            return true;
        }

        const auto relic_name = std::format("@{} Relic@", std::string(data.data->relics.relic_name(location)));
        const auto message = std::make_shared<items::Message>();
        message->should_add_to_recent = true;
        message->info.text.set(relic_name);

        set_location(message.get(), location);
        data.add_item(message);
        data.location_data.names.emplace_back().set(relic_name);
        data.location_data.icons.emplace_back(MapIcon::MapstonePickup);

        return true;
    }

    /**
     * \brief
     * \param parts Parts array including the sys_message_type as parts[0]
     * \param data
     * \return
     */
    bool parse_sys_message(const std::span<std::string> parts, ParserData& data) {
        int sys_message_type;
        if (!string_convert(parts[0], sys_message_type)) {
            return false;
        }

        // TODO: RelicList, MapRelicList and GoalProgress should be implemented in headers/seedgen.
        switch (sys_message_type) {
            case 0:
                // RelicList
                // var rzs = RelicZones;
                // if (rzs.Count == 0)
                //    return "";
                // int cur = 0;
                // int tot = 0;
                // var s = String.Join(", ", rzs.Select(z => {
                //    int totz = Counts[z];
                //    int curz = UberGet.value(ZoneToId[z]).Byte;
                //    cur += curz;
                //    tot += totz;
                //    var w = "";
                //    if (curz >= totz)
                //        w = "@";
                //    else if (CurrentZone == z)
                //        w = "#";
                //    return $"{w}{z}{w}";
                //}));
                // var c = cur == tot ? "$" : "";
                // return $"{c}Relics ({cur}/{tot}):{c} {s}";
                return false;
            case 1:
                // MapRelicList
                // var rzs = RelicZones;
                // if (rzs.Count == 0)
                //     return "";
                // if (rzs.Contains(zone)) {
                //     if (UberGet.value(ZoneToId[zone]).Byte >= Counts[zone])
                //         return " $(Relic found)$";
                //     else
                //         return " (Relic not found)";
                // }
                // return " (Relicless)";
                return false;
            case 2: {
                const auto message = std::make_shared<items::Message>();
                message->should_add_to_recent = true;
                message->info.text.set("[state_int(6|2)]/[seed(pickup_count)]");
                data.add_item(message);
                data.location_data.names.emplace_back(message->info.text);
                break;
            }
            case 3:
                // GoalProgress
                // auto message = std::make_shared<items::Message>();
                // message->info.text = "[world(name)]";
                // message->info.should_save_as_last = true;
                // data.items.push_back(message);

                // if (InterOp.Utils.get_game_state() != GameState.Game)
                //     return ""; // don't even try!

                // var goalMsgs = new List<String>();
                // if (Flags.Contains(Flag.ALL_WISPS)) {
                //     var max = UberStateController.Wisps.Count;
                //     var amount = UberStateController.Wisps.Count((UberState s) = > s.GetValue().Bool);
                //     var w = amount == max ? met : unmet;
                //     goalMsgs.Add($ "{w}Wisps: {amount}/{max}{w}");
                // }

                // if (Flags.Contains(Flag.ALL_TREES)) {
                //     var amount = SaveController.TreeCount;
                //     var w = amount == 14 ? met : unmet;
                //     goalMsgs.Add($ "{w}Trees: {amount}/{14}{w}");
                // }

                // if (Flags.Contains(Flag.ALL_QUESTS)) {
                //     var max = UberStateController.Quests.Count;
                //     var amount = UberStateController.Quests.Count((UberState s) = > s.GetValue().Int == s.Value.Int);
                //     var w = amount == max ? met : unmet;
                //     goalMsgs.Add($ "{w}Quests: {amount}/{max}{w}");
                // }

                // var msg = String.Join(", ", goalMsgs);
                // if (withRelics && Flags.Contains(Flag.RELICS))
                //     msg += "\n" + Relic.RelicMessage();
                // return goalMsgs.Count > 0 ? (progress ? "\n" : "") + msg : msg;
                // return SeedController.GoalModeMessages(withRelics
                //                                        : false);
                return false;
            case 4: {
                std::vector<std::string> pieces;
                split_str(parts[1], pieces, ',');
                if (pieces.size() % 2 != 0) {
                    return false;
                }

                auto counter = std::make_shared<items::CountingMessage>();
                for (auto it = pieces.begin(); it != pieces.end(); it += 2) {
                    auto& target = counter->targets.emplace_back();
                    core::api::uber_states::parse_condition(std::span<std::string>(it, 2), target);
                }

                data.add_item(counter);
                data.location_data.names.emplace_back([](auto) {}, [counter]() { return counter->message_text(); });
                break;
            }
            case 5: {
                // WorldName
                const auto message = std::make_shared<items::Message>();
                message->info.text.set_format("[world({})]", parts[1]);
                message->should_add_to_recent = true;
                data.add_item(message);
                data.location_data.names.emplace_back(message->info.text);
                break;
            }
            default:
                return false;
        }

        return true;
    }

    bool parse_wheel_name(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int wheel;
        int item;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        auto& name = parts[2];
        caller->description = std::format("wheel item {}:{} set name {}", wheel, item, name);
        caller->func = [wheel, item, name]() { features::wheel::set_wheel_item_name(wheel, item, name); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_description(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int wheel;
        int item;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        auto& description = parts[2];
        caller->description = std::format("wheel item {}:{} set description {}", wheel, item, description);
        caller->func = [wheel, item, description]() { features::wheel::set_wheel_item_description(wheel, item, description); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_texture(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int wheel;
        int item;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        auto& texture = parts[2];
        caller->description = std::format("wheel item {}:{} set texture {}", wheel, item, texture);
        caller->func = [wheel, item, texture]() { features::wheel::set_wheel_item_texture(wheel, item, texture); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_color(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 6) {
            return false;
        }

        int wheel;
        int item;
        app::Color color{};
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item) || !string_convert(parts[2], color.r) || !string_convert(parts[3], color.g) ||
            !string_convert(parts[4], color.b) || !string_convert(parts[5], color.a)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("wheel item {}:{} set color ({}, {}, {}, {})", wheel, item, color.r, color.g, color.b, color.a);
        caller->func = [wheel, item, color]() {
            features::wheel::set_wheel_item_color(
                wheel, item, static_cast<int>(color.r), static_cast<int>(color.g), static_cast<int>(color.b), static_cast<int>(color.a)
            );
        };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_action(location_type const& location, std::span<std::string> parts, ParserData& data) {
        // NOLINT
        if (parts.size() <= 3) {
            return false;
        }

        int wheel;
        int item;
        int binding;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item) || !string_convert(parts[2], binding)) {
            return false;
        }

        auto binding_type = static_cast<app::SpellInventory_Binding__Enum>(binding - 1);
        if (binding < 0 || binding > 2) {
            return false;
        }

        auto procedure_id = data.next_procedure_id++;
        auto& procedure = data.data->procedures[procedure_id];
        ParserData procedure_data{
            .data = data.data,
            .location_data = procedure,
            .items_added = 0,
            .next_location_id = data.next_location_id,
            .next_procedure_id = data.next_procedure_id,
            .should_add_to_always_granted = false,
            .should_add_default_messages = parts.back() != "mute"
        };

        const auto action_parts = std::span(parts.begin() + 3, parts.end());
        if (!parse_action(location, action_parts, procedure_data)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("wheel item {}:{} set action '{}'", wheel, item, concatenate_parts(action_parts));
        caller->func = [wheel, item, binding_type, procedure_id]() {
            if (static_cast<int>(binding_type) == -1) {
                features::wheel::set_wheel_item_callback(wheel, item, app::SpellInventory_Binding__Enum::ButtonX, [procedure_id](auto, auto, auto) {
                    game_seed().procedure_call(procedure_id);
                });
                features::wheel::set_wheel_item_callback(wheel, item, app::SpellInventory_Binding__Enum::ButtonY, [procedure_id](auto, auto, auto) {
                    game_seed().procedure_call(procedure_id);
                });
                features::wheel::set_wheel_item_callback(wheel, item, app::SpellInventory_Binding__Enum::ButtonB, [procedure_id](auto, auto, auto) {
                    game_seed().procedure_call(procedure_id);
                });
            } else {
                features::wheel::set_wheel_item_callback(wheel, item, binding_type, [procedure_id](auto, auto, auto) {
                    game_seed().procedure_call(procedure_id);
                });
            }
        };

        modloader::ScopedSetter scoped(data.should_add_to_always_granted, false);
        data.add_item(caller);
        return true;
    }

    bool parse_wheel_sticky(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 2) {
            return false;
        }

        int wheel;
        bool sticky;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], sticky)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("wheel {} set sticky {}", wheel, sticky);
        caller->func = [wheel, sticky]() { features::wheel::set_wheel_sticky(wheel, sticky); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_active(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 1) {
            return false;
        }

        int wheel;
        if (!string_convert(parts[0], wheel)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("wheel {} set active", wheel);
        caller->func = [wheel]() { features::wheel::set_active_wheel(wheel); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_clear_item(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 2) {
            return false;
        }

        int wheel;
        int item;
        if (!string_convert(parts[0], wheel) || !string_convert(parts[1], item)) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("wheel {}:{} clear entry", wheel, item);
        caller->func = [wheel, item]() { features::wheel::clear_wheel_item(wheel, item); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel_clear_all(std::span<std::string> parts, ParserData& data) {
        if (!parts.empty()) {
            return false;
        }

        const auto caller = std::make_shared<items::Call>();
        caller->description = "wheel clear all";
        caller->func = []() { features::wheel::clear_wheels(); };

        data.add_item(caller);
        return true;
    }

    bool parse_wheel(location_type const& location, std::span<std::string> parts, ParserData& data) {
        // NOLINT
        if (parts.empty()) {
            return false;
        }

        int wheel_type;
        if (!string_convert(parts[0], wheel_type)) {
            return false;
        }

        const auto next_parts = std::span(parts.begin() + 1, parts.end());
        switch (wheel_type) {
            case 0:
                return parse_wheel_name(next_parts, data);
            case 1:
                return parse_wheel_description(next_parts, data);
            case 2:
                return parse_wheel_texture(next_parts, data);
            case 3:
                return parse_wheel_color(next_parts, data);
            case 4:
                return parse_wheel_action(location, next_parts, data);
            case 5:
                return parse_wheel_sticky(next_parts, data);
            case 6:
                return parse_wheel_active(next_parts, data);
            case 7:
                return parse_wheel_clear_item(next_parts, data);
            case 8:
                return parse_wheel_clear_all(next_parts, data);
            default:
                break;
        }

        return false;
    }

    bool parse_shop_icon(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int group;
        int state;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state)) {
            return false;
        }

        auto icon = parts[2];
        auto shop_state = core::api::uber_states::UberState(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("shop '{}' set icon {}", shop_state.to_string(), icon);
        caller->func = [shop_state, icon]() {
            if (const auto slot = game::shops::shop_slot_from_state(shop_state); slot != nullptr) {
                slot->normal.icon = core::api::graphics::textures::get_texture(icon);
                slot->locked.icon = slot->normal.icon;
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_shop_title(std::span<std::string> parts, ParserData& data) {
        if (parts.size() < 2 || parts.size() > 3) {
            return false;
        }

        int group;
        int state;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state)) {
            return false;
        }

        auto title = parts.size() == 3 ? parts[2] : " ";
        auto shop_state = core::api::uber_states::UberState(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("shop '{}' set title {}", shop_state.to_string(), title);
        caller->func = [shop_state, title]() {
            if (const auto slot = game::shops::shop_slot_from_state(shop_state); slot != nullptr) {
                slot->normal.name.set(title);
                slot->locked.name.set(title);
                slot->hidden.name.set(title);
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_shop_description(std::span<std::string> parts, ParserData& data) {
        if (parts.size() < 2 || parts.size() > 3) {
            return false;
        }

        int group;
        int state;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state)) {
            return false;
        }

        auto description = parts.size() == 3 ? parts[2] : " ";
        auto shop_state = core::api::uber_states::UberState(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("shop '{}' set description {}", shop_state.to_string(), description);
        caller->func = [shop_state, description]() {
            if (const auto slot = game::shops::shop_slot_from_state(shop_state); slot != nullptr) {
                slot->normal.description.set(description);
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_shop_locked(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int group;
        int state;
        bool locked;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state) || !string_convert(parts[2], locked)) {
            return false;
        }

        auto shop_state = core::api::uber_states::UberState(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("shop '{}' set locked {}", shop_state.to_string(), locked);
        caller->func = [shop_state, locked]() {
            if (const auto slot = game::shops::shop_slot_from_state(shop_state); slot != nullptr && slot->visibility != game::shops::SlotVisibility::Hidden) {
                slot->visibility = locked ? game::shops::SlotVisibility::Locked : game::shops::SlotVisibility::Visible;
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_shop_visible(std::span<std::string> parts, ParserData& data) {
        if (parts.size() != 3) {
            return false;
        }

        int group;
        int state;
        bool visible;
        if (!string_convert(parts[0], group) || !string_convert(parts[1], state) || !string_convert(parts[2], visible)) {
            return false;
        }

        auto shop_state = core::api::uber_states::UberState(group, state);
        const auto caller = std::make_shared<items::Call>();
        caller->description = std::format("shop '{}' set visible {}", shop_state.to_string(), visible);
        caller->func = [shop_state, visible]() {
            if (const auto slot = game::shops::shop_slot_from_state(shop_state); slot != nullptr) {
                slot->visibility = visible ? game::shops::SlotVisibility::Visible : game::shops::SlotVisibility::Hidden;
            }
        };

        data.add_item(caller);
        return true;
    }

    bool parse_shop(std::span<std::string> parts, ParserData& data) {
        if (parts.empty()) {
            return false;
        }

        int wheel_type;
        if (!string_convert(parts[0], wheel_type)) {
            return false;
        }

        const auto next_parts = std::span<std::string>(parts.begin() + 1, parts.end());
        switch (wheel_type) {
            case 0:
                return parse_shop_icon(next_parts, data);
            case 1:
                return parse_shop_title(next_parts, data);
            case 2:
                return parse_shop_description(next_parts, data);
            case 3:
                return parse_shop_locked(next_parts, data);
            case 4:
                return parse_shop_visible(next_parts, data);
            default:
                break;
        }

        return false;
    }

    bool parse_map_message(std::span<std::string> parts, ParserData& data) {
        const auto map_message = std::make_shared<items::MapMessage>();
        map_message->message = std::accumulate(parts.begin(), parts.end(), std::string(), [](auto const& ss, auto const& s) -> decltype(auto) {
            return ss.empty() ? s : ss + "|" + s;
        });

        data.add_item(map_message);
        return true;
    }

    bool parse_action(location_type const& location, std::span<std::string> parts, ParserData& data) {
        // NOLINT(*-no-recursion)
        // NOLINT
        if (parts.empty()) {
            return false;
        }

        int action_type_int;
        if (!string_convert(parts[0], action_type_int)) {
            return false;
        }

        const auto action_type = static_cast<ActionType>(action_type_int);
        const auto next_parts = std::span<std::string>(parts.begin() + 1, parts.end());
        switch (action_type) {
            case ActionType::SpiritLight:
                return parse_spirit_light(location, next_parts, data);
            case ActionType::Resource:
                return parse_resource(location, next_parts, data);
            case ActionType::Ability:
                return parse_ability(location, next_parts, data);
            case ActionType::Shard:
                return parse_shard(location, next_parts, data);
            case ActionType::SystemCommand:
                return parse_sys_command(location, next_parts, data);
            case ActionType::Teleporter:
                return parse_teleporter(location, next_parts, data);
            case ActionType::Message:
                return parse_message(location, next_parts, data);
            case ActionType::UberState:
                return parse_uber_state(next_parts, data);
            case ActionType::QuestEvent:
                return parse_quest_event(location, next_parts, data);
            case ActionType::BonusItem:
                return parse_bonus_item(location, next_parts, data);
            case ActionType::WeaponUpgrade:
                return parse_weapon_upgrade(location, next_parts, data);
            case ActionType::Relic:
                return parse_relic(location, next_parts, data);
            case ActionType::SysMessage:
                return parse_sys_message(next_parts, data);
            case ActionType::Wheel:
                return parse_wheel(location, next_parts, data);
            case ActionType::Shop:
                return parse_shop(next_parts, data);
            case ActionType::SetMapMessage:
                return parse_map_message(next_parts, data);
            default:
                return false;
        }
    }

    bool parse_expression(int& next_location_id, int& next_procedure_id, std::span<std::string> parts, std::shared_ptr<Seed::Data> data, int line_number) {
        if (parts.size() < 3) {
            // Need at least the trigger and an action type.
            return false;
        }

        bool should_always_grant = false;
        core::api::uber_states::UberStateCondition trigger;
        if (!parse_condition(std::span(parts.begin(), parts.begin() + 2), trigger, &should_always_grant)) {
            return false;
        }

        auto& location_item_data = data->locations[trigger.state][trigger];
        ParserData parser_data{
            .data = data,
            .location_data = location_item_data,
            .items_added = 0,
            .next_location_id = next_location_id,
            .next_procedure_id = next_procedure_id,
            .should_add_to_always_granted = should_always_grant,
            .should_add_default_messages = parts.back() != "mute",
            .line_number = line_number,
            .item_definition = std::string(concatenate_parts(parts))
        };

        const int parts_end_offset = parser_data.should_add_default_messages ? 0 : 1;
        return parse_action(trigger, std::span(parts.begin() + 2, parts.end() - parts_end_offset), parser_data);
    }

    /**
     * \brief Check if a line is a config line, and if yes, parse its contents into the seed data
     * \param line The current line as raw string (escape sequences have NOT been replaced yet)
     * \param data Seed data
     */
    void parse_config(std::string_view line, std::shared_ptr<Seed::Data> data) {
        if (line.starts_with("// This World:")) {
            const std::string str(line.substr(14));
            data->info.meta.world_index = std::stoi(str);
        } else if (line.starts_with("// Format Version:")) {
        } else if (line.starts_with("// Generator Version:")) {
        } else if (line.starts_with("// Slug:")) {
            data->info.meta.slug = trim_copy(line.substr(sizeof("// Slug:")));
        }

        // If we don't match anything here it's a comment, and we can ignore it.
    }

    bool is_seed_version_supported(semver::version version) {
        return semver::range::satisfies(version, ">=1.0.0 <=1.0.0");
    }

    std::variant<Seed::SeedMetaData, ParserError> parse_meta_data(const std::string_view content) {
        std::istringstream seed_file(content.data());

        std::optional<nlohmann::json> seedgen_config;
        Seed::SeedMetaData meta;
        std::string line;
        while (std::getline(seed_file, line)) {
            if (line.starts_with("// Format Version: ")) {
                const auto version = trim_copy(line.substr(19));
                const auto parsed = semver::from_string_noexcept(version);
                if (parsed.has_value()) {
                    meta.version = parsed.value();
                }

                if (!is_seed_version_supported(meta.version)) {
                    return ParserError::WrongVersion;
                }
            } else if (line.starts_with("// This World:")) {
                const std::string str(line.substr(14));
                meta.world_index = std::stoi(str);
            } else if (line.starts_with("// Slug:")) {
                meta.slug = trim_copy(line.substr(sizeof("// Slug:")));
            } else if (line.starts_with("// Config:")) {
                seedgen_config = nlohmann::json::parse(line.begin() + sizeof("// Config:"), line.end());
            } else {
                // Remove comments.
                line = line.substr(0, line.find("//"));

                if (line.starts_with("Flags:")) {
                    split_str(line.substr(6), meta.flags, ',');
                    for (auto& flag: meta.flags) {
                        trim(flag);
                    }
                } else if (line.starts_with("Spawn:")) {
                    std::vector<std::string> coords;
                    split_str(line.substr(6), coords, ',');
                    if (coords.size() != 2) {
                        continue;
                    }

                    app::Vector3 position{};
                    if (!string_convert(coords[0], position.x) || !string_convert(coords[1], position.y)) {
                        continue;
                    }

                    meta.start_position = position;
                } else if (line.starts_with("APSlot:")) {
                    meta.archipelago_slot_name = trim_copy(line.substr(sizeof("APSlot:")));
                } else if (line.starts_with("APSeed:")) {
                    meta.archipelago_seed = trim_copy(line.substr(sizeof("APSeed:")));
                }
            }
        }

        if (seedgen_config.has_value()) {
            if ((*seedgen_config)["worldSettings"][meta.world_index].value("hard", false)) {
                meta.game_difficulties.hard = Seed::GameDifficultySetting::Allow;
            } else {
                meta.game_difficulties.normal = Seed::GameDifficultySetting::Allow;
            }
        }

        return meta;
    }

    bool parse(const std::string_view content, location_data::LocationCollection const& location_data, std::shared_ptr<Seed::Data> data) {
        std::istringstream seed_file(content.data());

        current_location_data = &location_data;
        int next_location_id = 0;
        int next_procedure_id = 0;
        int line_number = 0;
        std::optional<nlohmann::json> seedgen_config;

        std::string line;
        while (std::getline(seed_file, line)) {
            if (line.starts_with("// Format Version: ")) {
                const auto version = trim_copy(line.substr(19));
                const auto parsed = semver::from_string_noexcept(version);
                if (parsed.has_value()) {
                    data->info.meta.version = parsed.value();
                }

                break;
            }
        }

        if (!is_seed_version_supported(data->info.meta.version)) {
            modloader::warn("legacy_seed_parser", "Failed to load seed due to incompatible version");
            data->info.parser_error = std::format("Failed to load seed\ndue to version incompatibility");
            return false;
        }

        seed_file.seekg(0);
        while (std::getline(seed_file, line)) {
            data->info.content += line;
            data->info.content += "\n";

            // Config needs to do its own escape handling (\n, \t etc)
            if (line.starts_with("//")) {
                if (line.starts_with("// Config:")) {
                    seedgen_config = nlohmann::json::parse(line.begin() + sizeof("// Config:"), line.end());
                } else {
                    parse_config(line, data);
                }

                ++line_number;
                continue;
            }

            replace_all(line, "\\n", "\n");
            replace_all(line, "\\t", "\t");

            // Remove comments.
            line = line.substr(0, line.find("//"));
            if (line.starts_with("Flags:")) {
                split_str(line.substr(6), data->info.meta.flags, ',');
                for (auto& flag: data->info.meta.flags) {
                    trim(flag);
                }
            } else if (line.starts_with("Spawn:")) {
                std::vector<std::string> coords;
                split_str(line.substr(6), coords, ',');
                if (coords.size() != 2) {
                    ++line_number;
                    continue;
                }

                app::Vector3 position{};
                if (!string_convert(coords[0], position.x) || !string_convert(coords[1], position.y)) {
                    ++line_number;
                    continue;
                }

                data->info.meta.start_position = position;
            } else if (line.starts_with("APSlot:")) {
                data->info.meta.archipelago_slot_name = trim_copy(line.substr(sizeof("APSlot:")));
            } else if (line.starts_with("timer:")) {
                std::vector<std::string> parts;
                auto timer_states = line.substr(6);
                trim(timer_states);
                parse_parts(timer_states, parts);

                if (parts.size() != 4) {
                    ++line_number;
                    continue;
                }

                int toggle_group;
                int toggle_state;
                int value_group;
                int value_state;

                if (
                    !string_convert(parts[0], toggle_group) ||
                    !string_convert(parts[1], toggle_state) ||
                    !string_convert(parts[2], value_group) ||
                    !string_convert(parts[3], value_state)
                ) {
                    ++line_number;
                    continue;
                }

                data->timers.push_back({
                    {toggle_group, toggle_state},
                    {value_group, value_state}
                });

            } else if (!line.empty()) {
                std::vector<std::string> parts;
                parse_parts(line, parts);
                parse_expression(next_location_id, next_procedure_id, std::span(parts.begin(), parts.end()), data, line_number);
            }

            ++line_number;
        }

        if (seedgen_config.has_value()) {
            if ((*seedgen_config)["worldSettings"][data->info.meta.world_index].value("hard", false)) {
                data->info.meta.game_difficulties.hard = Seed::GameDifficultySetting::Allow;
            } else {
                data->info.meta.game_difficulties.normal = Seed::GameDifficultySetting::Allow;
            }
        }

        return true;
    }

    std::optional<ItemData> parse_action(const std::string_view action) {
        auto data = std::make_shared<Seed::Data>();
        const location_type location{
            {},
            BooleanOperator::Equals,
            0,
        };

        ItemData& location_data = data->locations[location.state][location];
        int next_location_id = 0;
        int next_procedure_id = 0;

        std::vector<std::string> parts;
        parse_parts(action, parts);

        ParserData parser_data{
            .data = data,
            .location_data = location_data,
            .items_added = 0,
            .next_location_id = next_location_id,
            .next_procedure_id = next_procedure_id,
            .should_add_to_always_granted = false,
            .should_add_default_messages = parts.back() != "mute",
            .line_number = 0,
            .item_definition = std::string(action)
        };

        core::reactivity::ScopedReactivityBlocker blocker;
        return parse_action(location, parts, parser_data) ? std::optional(location_data) : std::nullopt;
    }
} // namespace randomizer::seed::legacy_parser
