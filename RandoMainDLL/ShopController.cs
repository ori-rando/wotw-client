﻿using System;
using System.Collections.Generic;
using RandoMainDLL.Memory;
using System.Text;
using System.Runtime.InteropServices;

namespace RandoMainDLL {
  public static class ShopController {
    public static HashSet<string> Strings = new HashSet<string>();

    [DllExport]
    public static ulong ShopStringRepl(IntPtr str) {
      var strr = MemoryReader.ReadString(Randomizer.Memory.Program, str);
      var shopStr = GetShopNameReplacement(strr);
      if (shopStr != strr) {
        return (ulong)getIl2cppStringPointer(shopStr);
      }
      else if (!Strings.Contains(strr)) {
        // if (Randomizer.Dev)
        //   Randomizer.Log($"New String: |{strr}|", false);
        Strings.Add(strr);
      }
      return 0;
    }

    private static readonly Dictionary<string, IntPtr> stringAddresses = new Dictionary<string, IntPtr>();

    static IntPtr getIl2cppStringPointer(string str) {
      if (!stringAddresses.ContainsKey(str)) {
        var chars = str.ToCharArray();
        int size = Encoding.Unicode.GetByteCount(chars);
        byte[] bytes = Encoding.Unicode.GetBytes(chars);

        IntPtr ptr = Marshal.AllocHGlobal(0x14 + size);
        for (int i = 0; i < MemoryReader.stringHeader.Length; i++) {
          Marshal.WriteByte(ptr, i, MemoryReader.stringHeader[i]);
        }

        Marshal.WriteInt64(ptr, 0x10, str.Length);
        for (int i = 0; i < bytes.Length; i++) {
          Marshal.WriteByte(ptr, 0x14 + i, bytes[i]);
        }
        stringAddresses[str] = ptr;
      }

      return stringAddresses[str];
    }

    public static string GetShopNameReplacement(string orig) {
      if (RemoveStrings.Contains(orig)) {
        return " ";
      }
      else if (OpherWeaponDetail.ContainsKey(orig)) {
        var weapon = OpherWeaponDetail[orig];
        if (!OpherWeaponChatter.ContainsKey(weapon)) {
          OpherWeaponChatter[weapon] = Chatter[new Random().Next(Chatter.Count)];
        }
        return OpherWeaponChatter[weapon];
      }
      else if (OpherWeaponNames.ContainsKey(orig)) {
        return SeedController.OpherWeapon(OpherWeaponNames[orig]).ToString();

      }
      else if (TwillenShardDetail.ContainsKey(orig)) {
        var shard = TwillenShardDetail[orig];
        if (!TwillenShardChatter.ContainsKey(shard)) {
          TwillenShardChatter[shard] = Chatter[new Random().Next(Chatter.Count)];
        }
        return TwillenShardChatter[shard];
      }
      else if (TwillenShardNames.ContainsKey(orig)) {
        return SeedController.TwillenShard(TwillenShardNames[orig]).ToString();
      }

      return orig;
    }

    public static HashSet<string> RemoveStrings = new HashSet<string> {
      "Level {0}:",
      "Next Level",
      "Uses Energy",
      "Upgrade for",
      "Gain 2 additional Energy cells",
      "Gain 3 additional Energy cells",
      "Gain 2 additional Life cells",
      "Gain 3 additional Life cells",
      "Enemies drop 3 extra Spirit Light orbs",
      "Enemies drop 4 extra Spirit Light orbs",
      "20% chance to deal 50% bonus damage",
    };

    public static Dictionary<string, AbilityType> OpherWeaponNames = new Dictionary<string, AbilityType> {
      { "Sentry", AbilityType.Sentry },
      { "Spirit Smash", AbilityType.SpiritSmash },
      { "Spirit Star", AbilityType.SpiritStar },
      { "Spike", AbilityType.Spike },
      { "Blaze", AbilityType.Blaze },
      { "Water Breath", AbilityType.WaterBreath },
      { "Fast Travel", AbilityType.TeleportSpell },
    };

    public static Dictionary<string, AbilityType> OpherWeaponDetail = new Dictionary<string, AbilityType> {
      { "Pound foes with a strong, sweeping blow", AbilityType.SpiritSmash },
      { @"Throw a powerful spear of light.\nUses a large amount of Energy", AbilityType.Spike },
      { "Spawn a spirit orb that attacks for you", AbilityType.Sentry },
      { "Throw a star that returns to you", AbilityType.SpiritStar },
      { "Set nearby enemies on fire", AbilityType.Blaze },
      { "Breathe under water", AbilityType.WaterBreath },
      { "Select Spirit Wells on the map and #warp# to them #from anywhere#.", AbilityType.TeleportSpell }
    };

    public static Dictionary<string, ShardType> TwillenShardNames = new Dictionary<string, ShardType> {
      { "Energy", ShardType.Energy },
      { "Vitality", ShardType.Vitality },
      { "Overcharge", ShardType.Overcharge },
      { "Wingclip", ShardType.Wingclip },
      { "Triple Jump", ShardType.TripleJump },
      { "Finesse", ShardType.Finesse },
      { "Swap", ShardType.Swap },
      { "Light Harvest", ShardType.LightHarvest },
    };

    public static Dictionary<string, ShardType> TwillenShardDetail = new Dictionary<string, ShardType> {
      { "Gain 1 additional Energy cell", ShardType.Energy },
      { "Gain 1 additional Life cell", ShardType.Vitality },
      { "Reduce Energy costs by 50% and increase damage taken by 100%", ShardType.Overcharge },
      { "Deal bonus damage to flying enemies", ShardType.Wingclip},
      { "Jump twice mid-air before landing", ShardType.TripleJump},
      { "10% chance to deal 50% bonus damage", ShardType.Finesse},
      { "Swap maximum Life and Energy", ShardType.Swap },
      { "Enemies drop 2 extra Spirit Light orbs", ShardType.LightHarvest },
    };

    public static Dictionary<AbilityType, string> OpherWeaponChatter = new Dictionary<AbilityType, string>();
    public static Dictionary<ShardType, string> TwillenShardChatter = new Dictionary<ShardType, string>();

    public static List<string> Chatter = new List<string> {
      "Nice, isn't it?",
      "Very shiny",
      "One of my favorites",
      "I've always loved these",
      "Popular among the Moki",
      "A crowd favorite",
      "Seems kind of useless",
      "I guess someone could use this?",
      "I found this nearby",
      "Traded for this from a Moki",
      "Grom said he's never\nseen one of these",
      "Grom loves these",
      "Tokk gave me this",
      "Lupo found this while\nexploring the Wellspring",
      "Lupo found this deep\nin Inkwater Marsh",
      "Lupo found this under\nthe big statue of Kwolok",
      "Lupo found this floating\nin Luma Pools",
      "It's dangerous to go alone",
      "It's fresh!",
      "Hot item!",
      "Found this in the Midnight Burrows",
      "Fresh out of Nibel!",
      "I have no idea where this came from",
      "Not really sure what this is for",
      "You can use this, right?",
      "Selling this one at a loss",
      "Caveat emptor!",
    };

    private static Dictionary<AbilityType, float> weaponCostMods = new Dictionary<AbilityType, float>();
    private static Dictionary<ShardType, float> shardCostMods = new Dictionary<ShardType, float>();

    public static void SetCostMod(AbilityType type, float multi) => weaponCostMods[type] = multi;
    public static void SetCostMod(ShardType type, float multi) => shardCostMods[type] = multi;

    public static float GetCostMod(AbilityType type) => weaponCostMods.ContainsKey(type) ? weaponCostMods[type] : 0f;
    public static float GetCostMod(ShardType type) => shardCostMods.ContainsKey(type) ? shardCostMods[type] : 0f;

    [DllExport]
    public static void OpherBuyWeapon(AbilityType slot) {
      Sellable item = SeedController.OpherWeapon(slot);
      if (SaveController.Data.OpherSold.Contains(slot)) {
        Randomizer.Log($"OBW: not enough money or slot already sold");
        return;
      }
      SaveController.Data.OpherSold.Add(slot);
      Randomizer.Log($"sold {item} from {slot} for ${item.DefaultCost()}", false);
      item.Grant();
      Randomizer.PleaseSave = true;
      return;
    }

    [DllExport]
    public static void OpherBuyUpgrade(AbilityType slot) => SaveController.Data.OpherUpgraded.Add(slot, 1);

    [DllExport]
    public static bool OpherBoughtUpgrade(AbilityType slot) {
      SaveController.Data.OpherUpgraded.TryGetValue(slot, out int cnt);
      return cnt > 0;
    }


    [DllExport]
    public static void TwillenBuyShard(ShardType slot) {
      Sellable item = SeedController.TwillenShard(slot);
      if (SaveController.Data.TwillenSold.Contains(slot)) {
        Randomizer.Log($"TBS: not enough money or slot already sold ");
        return;
      }
      SaveController.Data.TwillenSold.Add(slot);
      Randomizer.PleaseSave = true;
      item.Grant();
      return;
    }
    [DllExport]
    public static bool OpherBoughtWeapon(AbilityType granted) => SaveController.Data.OpherSold.Contains(granted);

    [DllExport]
    public static bool TwillenBoughtShard(ShardType shard) => SaveController.Data.TwillenSold.Contains(shard);

    [DllExport]
    public static int TwillenShardCost(ShardType shard) => SeedController.TwillenShard(shard).CostWithMod(GetCostMod(shard));

    [DllExport]
    public static int OpherWeaponCost(AbilityType ability) => SeedController.OpherWeapon(ability).CostWithMod(GetCostMod(ability));
  }
}
