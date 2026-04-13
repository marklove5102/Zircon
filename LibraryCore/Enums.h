#pragma once

#include <string>
#include <cstdint>

namespace Library
{
    // Gender
    enum class MirGender : uint8_t
    {
        Male,
        Female
    };

    // Class
    enum class MirClass : uint8_t
    {
        Warrior,
        Wizard,
        Taoist,
        Assassin,
    };

    // Attack Mode
    enum class AttackMode : uint8_t
    {
        Peace,      // Attack: Peaceful
        Group,      // Attack: Group
        Guild,      // Attack: Guild
        WarRedBrown,// Attack: War, Red, Brown
        All         // Attack: All
    };

    // Pet Mode
    enum class PetMode : uint8_t
    {
        Both,   // Pet: Move, Attack
        Move,   // Pet: Move
        Attack, // Pet: Attack
        PvP,    // Pet: PvP
        None,   // Pet: None
    };

    // Direction
    enum class MirDirection : uint8_t
    {
        Up = 0,
        UpRight = 1,
        Right = 2,
        DownRight = 3,
        Down = 4,
        DownLeft = 5,
        Left = 6,
        UpLeft = 7
    };

    // Required Class (Flags)
    enum class RequiredClass : uint8_t
    {
        None = 0,
        Warrior = 1,
        Wizard = 2,
        Taoist = 4,
        Assassin = 8,
        WarWizTao = Warrior | Wizard | Taoist,  // Warrior, Wizard, Taoist
        WizTao = Wizard | Taoist,               // Wizard, Taoist
        AssWar = Warrior | Assassin,            // Warrior, Assassin
        All = WarWizTao | Assassin
    };

    // Required Gender (Flags)
    enum class RequiredGender : uint8_t
    {
        Male = 1,
        Female = 2,
        None = Male | Female
    };

    // Equipment Slot
    enum class EquipmentSlot : int
    {
        Weapon = 0,
        Armour = 1,
        Helmet = 2,
        Torch = 3,
        Necklace = 4,
        BraceletL = 5,
        BraceletR = 6,
        RingL = 7,
        RingR = 8,
        Shoes = 9,
        Poison = 10,
        Amulet = 11,
        Flower = 12,
        HorseArmour = 13,
        Emblem = 14,
        Shield = 15,
        Costume = 16,

        Hook = 17,
        Float = 18,
        Bait = 19,
        Finder = 20,
        Reel = 21
    };

    // Companion Slot
    enum class CompanionSlot : int
    {
        Bag = 0,
        Head = 1,
        Back = 2,
        Food = 3,
    };

    // Days of Week (Flags)
    enum class DaysOfWeek : uint8_t
    {
        None = 0,
        Sunday = 1,
        Monday = 2,
        Tuesday = 4,
        Wednesday = 8,
        Thursday = 16,
        Friday = 32,
        Saturday = 64,
        Weekday = Monday | Tuesday | Wednesday | Thursday | Friday,
        Weekend = Saturday | Sunday
    };

    // Weather (Flags)
    enum class Weather : uint8_t
    {
        None = 0,
        Rain = 1,
        Snow = 2,
        Fog = 4,
        Lightning = 8,

        SnowFog = 6,              // Snow, Fog
        RainLightning = 9,        // Rain, Lightning
        FogLightning = 12,        // Fog, Lightning
        RainFogLightning = 13     // Rain, Fog, Lightning
    };

    // Grid Type
    enum class GridType : int
    {
        None,
        Inventory,
        Equipment,
        Belt,
        Repair,
        Storage,
        AutoPotion,
        RefineBlackIronOre,
        RefineAccessory,
        RefineSpecial,
        Inspect,
        Consign,
        SendMail,
        TradeUser,
        TradePlayer,
        GuildStorage,
        CompanionInventory,
        CompanionEquipment,
        WeddingRing,
        RefinementStoneIronOre,
        RefinementStoneSilverOre,
        RefinementStoneDiamond,
        RefinementStoneGoldOre,
        RefinementStoneCrystal,
        ItemFragment,
        AccessoryRefineUpgradeTarget,
        AccessoryRefineLevelTarget,
        AccessoryRefineLevelItems,
        MasterRefineFragment1,
        MasterRefineFragment2,
        MasterRefineFragment3,
        MasterRefineStone,
        MasterRefineSpecial,
        AccessoryReset,
        WeaponCraftTemplate,
        WeaponCraftYellow,
        WeaponCraftBlue,
        WeaponCraftRed,
        WeaponCraftPurple,
        WeaponCraftGreen,
        WeaponCraftGrey,
        RefineCorundumOre,
        AccessoryRefineCombTarget,
        AccessoryRefineCombItems,
        PartsStorage
    };

    // Inventory Mode
    enum class InventoryMode : int
    {
        Normal,
        Sell
    };

    // Buff Type
    enum class BuffType : int
    {
        None,

        Server = 1,
        HuntGold = 2,

        Observable = 3,
        Brown = 4,
        PKPoint = 5,
        PvPCurse = 6,
        Redemption = 7,
        Companion = 8,

        Castle = 9,

        ItemBuff = 10,
        ItemBuffPermanent = 11,

        Ranking = 12,
        Developer = 13,
        Veteran = 14,

        MapEffect = 15,
        InstanceEffect = 16,
        Guild = 17,

        DeathDrops = 18,

        Fame = 19,

        // War
        Defiance = 100,
        Might = 101,
        Endurance = 102,
        ReflectDamage = 103,
        Invincibility = 104,
        DefensiveBlow = 105,
    };

    // Required Type
    enum class RequiredType : uint8_t
    {
        Level,
        MaxLevel,
        AC,
        MR,
        DC,
        MC,
        SC,
        Health,
        Mana,
        Accuracy,
        Agility,
        CompanionLevel,
        MaxCompanionLevel,
        RebirthLevel,
        MaxRebirthLevel,
    };

    // Rarity
    enum class Rarity : uint8_t
    {
        Common,
        Superior,
        Elite,
    };

    // Light Setting
    enum class LightSetting : uint8_t
    {
        Default,
        Light,
        Night,
        Twilight,
    };

    // Time of Day
    enum class TimeOfDay : uint8_t
    {
        Dawn,
        Day,
        Dusk,
        Night
    };

    // Fight Setting
    enum class FightSetting : uint8_t
    {
        None,
        Safe,
        Fight,
    };

    // Instance Type
    enum class InstanceType : uint8_t
    {
        Player = 0,
        Group = 1,
        Guild = 2,
        Castle = 3
    };

    // Region Type
    enum class RegionType : uint8_t
    {
        None = 0,

        Area = 1,
        Connection = 2,
        Spawn = 3,
        Npc = 4,
        SpawnConnection = 5
    };

    // Object Type
    enum class ObjectType : uint8_t
    {
        None, // Error

        Player,
        Item,
        NPC,
        Spell,
        Monster
    };

    // Item Type
    enum class ItemType : uint8_t
    {
        Nothing = 0,

        Consumable = 1,
        Weapon = 2,
        Armour = 3,
        Torch = 4,
        Helmet = 5,
        Necklace = 6,
        Bracelet = 7,
        Ring = 8,
        Shoes = 9,
        Poison = 10,
        Amulet = 11,
        Meat = 12,
        Ore = 13,
        Book = 14,
        Scroll = 15,
        DarkStone = 16,           // Dark Stone
        RefineSpecial = 17,       // Refine Special
        HorseArmour = 18,         // Horse Armour
        Flower = 19,
        CompanionFood = 20,       // Companion Food
        CompanionBag = 21,        // Companion Bag
        CompanionHead = 22,       // Companion Head
        CompanionBack = 23,       // Companion Back
        System = 24,
        ItemPart = 25,            // Item Part
        Emblem = 26,
        Shield = 27,
        Costume = 28,
        Hook = 29,
        Float = 30,
        Bait = 31,
        Finder = 32,
        Reel = 33,
        Currency = 34
    };

    // Mir Action
    enum class MirAction : uint8_t
    {
        Standing,
        Moving,
        Pushed,
        Attack,
        RangeAttack,
        Spell,
        Harvest,
        Struck,
        Die,
        Dead,
        Show,
        Hide,
        Mount,
        Mining,
        Fishing
    };

    // Mir Animation
    enum class MirAnimation : uint8_t
    {
        Standing,
        Walking,
        CreepStanding,
        CreepWalkSlow,
        CreepWalkFast,
        Running,
        Pushed,
        Combat1,
        Combat2,
        Combat3,
        Combat4,
        Combat5,
        Combat6,
        Combat7,
        Combat8,
        Combat9,
        Combat10,
        Combat11,
        Combat12,
        Combat13,
        Combat14,
        Combat15,
        Harvest,
        Stance,
        Struck,
        Die,
        Dead,
        Skeleton,
        Show,
        Hide,

        HorseStanding,
        HorseWalking,
        HorseRunning,
        HorseStruck,

        StoneStanding,

        DragonRepulseStart,
        DragonRepulseMiddle,
        DragonRepulseEnd,

        ChannellingStart,
        ChannellingMiddle,
        ChannellingEnd,

        FishingCast,
        FishingWait,
        FishingReel
    };

    // Message Action
    enum class MessageAction : int
    {
        None,
        Revive,
    };

    // Message Type
    enum class MessageType : int
    {
        Normal,
        Shout,
        WhisperIn,
        GMWhisperIn,
        WhisperOut,
        Group,
        Global,
        Hint,
        System,
        Announcement,
        Combat,
        ObserverChat,
        Guild,
        Debug
    };

    // NPC Dialog Type
    enum class NPCDialogType : int
    {
        None,
        BuySell,
        Repair,
        Refine,
        RefineRetrieve,
        CompanionManage,
        WeddingRing,
        RefinementStone,
        MasterRefine,
        WeaponReset,
        ItemFragment,
        AccessoryRefineUpgrade,
        AccessoryRefineLevel,
        AccessoryReset,
        WeaponCraft,
        AccessoryRefine,

        RollDie,
        RollYut
    };

    // Magic School
    enum class MagicSchool : int
    {
        None,

        Passive = 1,
        Active,
        Toggle,
        Fire,
        Ice,
        Lightning,
        Wind,
        Holy,
        Dark,
        Phantom,
        Physical,
        Atrocity,
        Kill,
        Assassination,

        Horse,

        Discipline = 20
    };

    // Element
    enum class Element : uint8_t
    {
        None,

        Fire,
        Ice,
        Lightning,
        Wind,
        Holy,
        Dark,
        Phantom,
    };

    // Exterior Effect
    enum class ExteriorEffect : uint8_t
    {
        None = 0,

        // EquipEffect_Part [1~99]
        A_WhiteAura = 1,
        A_FlameAura = 2,
        A_BlueAura = 3,

        A_FlameAura2 = 9,
        A_GreenWings = 10,
        A_FlameWings = 11,
        A_BlueWings = 12,
        A_RedSinWings = 13,

        A_DiamondFireWings = 14,
        A_PurpleTentacles2 = 15,
        A_PhoenixWings = 16,
        A_IceKingWings = 17,
        A_BlueButterflyWings = 18,


        S_WarThurible = 50,
        S_PenanceThurible = 51,
        S_CensorshipThurible = 52,
        S_PetrichorThurible = 53,

        // EquipEffect_Full [100~119]
        A_FireDragonWings = 100,
        A_SmallYellowWings = 101,
        A_GreenFeatherWings = 102,
        A_RedFeatherWings = 103,
        A_BlueFeatherWings = 104,
        A_WhiteFeatherWings = 105,
        A_PurpleTentacles = 106,

        W_ChaoticHeavenBlade = 110,
        W_JanitorsScimitar = 111,
        W_JanitorsDualBlade = 112,

        // EquipEffect_FullEx1 [120~139]
        A_LionWings = 120,
        A_AngelicWings = 121,

        // EquipEffect_FullEx2 [140~159]
        A_BlueDragonWings = 140,

        // EquipEffect_FullEx3 [160~179]
        A_RedWings2 = 160,

        // EquipEffect_Item [180~199]
        // Reserved

        // MonMagicEx26 [200~250]
        E_RedEyeRing = 200,
        E_BlueEyeRing = 201,
        E_GreenSpiralRing = 202,
        E_Fireworks = 203
    };

    // Item Effect
    enum class ItemEffect : uint8_t
    {
        None,

        // Gold = 1,
        Experience = 2,
        CompanionTicket = 3,
        BasicCompanionBag = 4,
        PickAxe = 5,
        UmaKingHorn = 6,
        ItemPart = 7,
        Carrot = 8,

        DestructionElixir = 10,
        HasteElixir = 11,
        LifeElixir = 12,
        ManaElixir = 13,
        NatureElixir = 14,
        SpiritElixir = 15,

        BlackIronOre = 20,
        GoldOre = 21,
        Diamond = 22,
        SilverOre = 23,
        IronOre = 24,
        Corundum = 25,

        ElixirOfPurification = 30,
        PillOfReincarnation = 31,

        Crystal = 40,
        RefinementStone = 41,
        Fragment1 = 42,
        Fragment2 = 43,
        Fragment3 = 44,

        GenderChange = 50,
        HairChange = 51,
        ArmourDye = 52,
        NameChange = 53,
        FortuneChecker = 54,
        Caption = 55,
    };

} // namespace Library
