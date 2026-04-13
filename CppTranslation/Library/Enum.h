#pragma once

#include <cstdint>
#include <string>
#include <type_traits>

namespace Library
{

// 辅助宏：用于枚举的 Description 属性（C++ 中作为注释或未来扩展）
#define ENUM_DESCRIPTION(enum_val, desc) // C++ 中暂不实现，可作为未来反射系统的基础

enum class MirGender : uint8_t
{
    Male,
    Female
};

enum class MirClass : uint8_t
{
    Warrior,
    Wizard,
    Taoist,
    Assassin,
};

enum class AttackMode : uint8_t
{
    Peace,      // Attack: Peaceful
    Group,      // Attack: Group
    Guild,      // Attack: Guild
    WarRedBrown,// Attack: War, Red, Brown
    All         // Attack: All
};

enum class PetMode : uint8_t
{
    Both,   // Pet: Move, Attack
    Move,   // Pet: Move
    Attack, // Pet: Attack
    PvP,    // Pet: PvP
    None,   // Pet: None
};

enum class MirDirection : uint8_t
{
    Up = 0,
    UpRight = 1,    // Up Right
    Right = 2,
    DownRight = 3,  // Down Right
    Down = 4,
    DownLeft = 5,   // Down Left
    Left = 6,
    UpLeft = 7      // Up Left
};

// Flags 枚举：支持位运算
enum class RequiredClass : uint8_t
{
    None = 0,
    Warrior = 1,
    Wizard = 2,
    Taoist = 4,
    Assassin = 8,
    WarWizTao = Warrior | Wizard | Taoist,          // Warrior, Wizard, Taoist
    WizTao = Wizard | Taoist,                       // Wizard, Taoist
    AssWar = Warrior | Assassin,                    // Warrior, Assassin
    All = WarWizTao | Assassin
};

// 位运算操作符
inline RequiredClass operator|(RequiredClass a, RequiredClass b)
{
    return static_cast<RequiredClass>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline RequiredClass operator&(RequiredClass a, RequiredClass b)
{
    return static_cast<RequiredClass>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline RequiredClass operator^(RequiredClass a, RequiredClass b)
{
    return static_cast<RequiredClass>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

inline RequiredClass operator~(RequiredClass a)
{
    return static_cast<RequiredClass>(~static_cast<uint8_t>(a));
}

inline RequiredClass& operator|=(RequiredClass& a, RequiredClass b)
{
    a = a | b;
    return a;
}

inline RequiredClass& operator&=(RequiredClass& a, RequiredClass b)
{
    a = a & b;
    return a;
}

enum class RequiredGender : uint8_t
{
    Male = 1,
    Female = 2,
    None = Male | Female
};

// 位运算操作符
inline RequiredGender operator|(RequiredGender a, RequiredGender b)
{
    return static_cast<RequiredGender>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline RequiredGender operator&(RequiredGender a, RequiredGender b)
{
    return static_cast<RequiredGender>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

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
    Wings = 16,
};

enum class CompanionSlot : int
{
    Bag = 0,
    Head = 1,
    Back = 2,
    Food = 3,
};

enum class GridType : int
{
    None,
    Inventory,
    Equipment,
    Belt,
    Sell,
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
    PartsStorage,
};

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
    Guild = 16,

    DeathDrops = 17,

    Defiance = 100,
    Might = 101,
    Endurance = 102,
    ReflectDamage = 103,

    Renounce = 200,
    MagicShield = 201,
    JudgementOfHeaven = 202,

    Heal = 300,
    Invisibility = 301,
    MagicResistance = 302,
    Resilience = 303,
    ElementalSuperiority = 304,
    BloodLust = 305,
    StrengthOfFaith = 306,
    CelestialLight = 307,
    Transparency = 308,
    LifeSteal = 309,

    PoisonousCloud = 400,

    FullBloom = 401,
    WhiteLotus = 402,
    RedLotus = 403,
    Cloak = 404,
    GhostWalk = 405,
    TheNewBeginning = 406,
    DarkConversion = 407,
    DragonRepulse = 408,
    Evasion = 409,
    RagingWind = 410,
    FrostBite = 411,

    MagicWeakness = 500,
};

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

enum class Rarity : uint8_t
{
    Common,
    Superior,
    Elite,
};

enum class LightSetting : uint8_t
{
    Default,
    Light,
    Night,
    Twilight,
};

enum class FightSetting : uint8_t
{
    None,
    Safe,
    Fight,
};

enum class ObjectType : uint8_t
{
    None,   // Error
    Player,
    Item,
    NPC,
    Spell,
    Monster
};

enum class ItemType : uint8_t
{
    Nothing,
    Consumable,
    Weapon,
    Armour,
    Torch,
    Helmet,
    Necklace,
    Bracelet,
    Ring,
    Shoes,
    Poison,
    Amulet,
    Meat,
    Ore,
    Book,
    Scroll,
    DarkStone,        // Dark Stone
    RefineSpecial,    // Refine Special
    HorseArmour,      // Horse Armour
    Flower,
    CompanionFood,    // Companion Food
    CompanionBag,     // Companion Bag
    CompanionHead,    // Companion Head
    CompanionBack,    // Companion Back
    System,
    ItemPart,         // Item Part
    Emblem,
    Shield,
    Wings
};

enum class MirAction : uint8_t
{
    Standing,
    Moving,
    Pushed,
    Attack,
    RangeAttack,
    Spell,
    Harvest,
    Die,
    Dead,
    Show,
    Hide,
    Mount,
    Mining,
};

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
};

enum class MessageAction : int
{
    None,
    Revive,
};

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
};

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
};

enum class MagicSchool : int
{
    None,
    Passive,
    WeaponSkills,
    Neutral,
    Fire,
    Ice,
    Lightning,
    Wind,
    Holy,
    Dark,
    Phantom,
    Combat,
    Assassination
};

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

enum class MagicType : int
{
    None,

    Swordsmanship = 100,
    PotionMastery = 101,
    Slaying = 102,
    Thrusting = 103,
    HalfMoon = 104,
    ShoulderDash = 105,
    FlamingSword = 106,
    DragonRise = 107,
    BladeStorm = 108,
    DestructiveSurge = 109,
    Interchange = 110,
    Defiance = 111,
    Beckon = 112,
    Might = 113,
    SwiftBlade = 114,
    Assault = 115,
    Endurance = 116,
    ReflectDamage = 117,
    Fetter = 118,
    SwirlingBlade = 119,
    ReigningStep = 120,
    MaelstromBlade = 121,
    AdvancedPotionMastery = 122,
    MassBeckon = 123,
    SeismicSlam = 124,

    FireBall = 201,
    LightningBall = 202,
    IceBolt = 203,
    GustBlast = 204,
    Repulsion = 205,
    ElectricShock = 206,
    Teleportation = 207,
    AdamantineFireBall = 208,
    ThunderBolt = 209,
    IceBlades = 210,
    Cyclone = 211,
    ScortchedEarth = 212,
    LightningBeam = 213,
    FrozenEarth = 214,
    BlowEarth = 215,
    FireWall = 216,
    ExpelUndead = 217,
    GeoManipulation = 218,
    MagicShield = 219,
    FireStorm = 220,
    LightningWave = 221,
    IceStorm = 222,
    DragonTornado = 223,
    GreaterFrozenEarth = 224,
    ChainLightning = 225,
    MeteorShower = 226,
    Renounce = 227,
    Tempest = 228,
    JudgementOfHeaven = 229,
    ThunderStrike = 230,
    RayOfLight = 231,
    BurstOfEnergy = 232,
    ShieldOfPreservation = 233,
    RetrogressionOfEnergy = 234,
    FuryBlast = 235,
    TempestOfUnstableEnergy = 236,
    MirrorImage = 237,
    AdvancedRenounce = 238,
    FrostBite = 239,
    Asteroid = 240,

    Heal = 300,
    SpiritSword = 301,
    PoisonDust = 302,
    ExplosiveTalisman = 303,
    EvilSlayer = 304,
    Invisibility = 305,
    MagicResistance = 306,
    MassInvisibility = 307,
    GreaterEvilSlayer = 308,
    Resilience = 309,
    TrapOctagon = 310,
    TaoistCombatKick = 311,
    ElementalSuperiority = 312,
    MassHeal = 313,
    BloodLust = 314,
    Resurrection = 315,
    Purification = 316,
    Transparency = 317,
    CelestialLight = 318,
    EmpoweredHealing = 319,
    LifeSteal = 320,
    ImprovedExplosiveTalisman = 321,
    GreaterPoisonDust = 322,
    Scarecrow = 323,
    ThunderKick = 324,
    DragonBreath = 325,
    MassTransparency = 326,
    GreaterHolyStrike = 327,
    AugmentExplosiveTalisman = 328,
    AugmentEvilSlayer = 329,
    AugmentPurification = 330,
    OathOfThePerished = 331,
    SummonSkeleton = 332,
    SummonShinsu = 333,
    SummonJinSkeleton = 334,
    StrengthOfFaith = 335,
    SummonDemonicCreature = 336,
    DemonExplosion = 337,
    Infection = 338,
    DemonicRecovery = 339,

    WillowDance = 401,
    VineTreeDance = 402,
    Discipline = 403,
    PoisonousCloud = 404,
    FullBloom = 405,
    Cloak = 406,
    WhiteLotus = 407,
    CalamityOfFullMoon = 408,
    WraithGrip = 409,
    RedLotus = 410,
    HellFire = 411,
    PledgeOfBlood = 412,
    Rake = 413,
    SweetBrier = 414,
    SummonPuppet = 415,
    Karma = 416,
    TouchOfTheDeparted = 417,
    WaningMoon = 418,
    GhostWalk = 419,
    ElementalPuppet = 420,
    Rejuvenation = 421,
    Resolution = 422,
    ChangeOfSeasons = 423,
    Release = 424,
    FlameSplash = 425,
    BloodyFlower = 426,
    TheNewBeginning = 427,
    DanceOfSwallow = 428,
    DarkConversion = 429,
    DragonRepulse = 430,
    AdventOfDemon = 431,
    AdventOfDevil = 432,
    Abyss = 433,
    FlashOfLight = 434,
    Stealth = 435,
    Evasion = 436,
    RagingWind = 437,
    AdvancedBloodyFlower = 438,
    Massacre = 439,
    ArtOfShadows = 440,

    MonsterScortchedEarth = 501,
    MonsterIceStorm = 502,
    MonsterDeathCloud = 503,
    MonsterThunderStorm = 504,

    SamaGuardianFire = 505,
    SamaGuardianIce = 506,
    SamaGuardianLightning = 507,
    SamaGuardianWind = 508,

    SamaPhoenixFire = 509,
    SamaBlackIce = 510,
    SamaBlueLightning = 511,
    SamaWhiteWind = 512,

    SamaProphetFire = 513,
    SamaProphetLightning = 514,
    SamaProphetWind = 515,

    DoomClawLeftPinch = 520,
    DoomClawLeftSwipe = 521,
    DoomClawRightPinch = 522,
    DoomClawRightSwipe = 523,
    DoomClawWave = 524,
    DoomClawSpit = 525,

    PinkFireBall = 530,
    GreenSludgeBall = 540,
};

enum class MonsterImage : int
{
    None,

    Guard,

    Chicken,
    Pig,
    Deer,
    Cow,
    Sheep,
    ClawCat,
    Wolf,
    ForestYeti,
    ChestnutTree,
    CarnivorousPlant,
    Oma,
    TigerSnake,
    SpittingSpider,
    Scarecrow,
    OmaHero,

    CaveBat,
    Scorpion,
    Skeleton,
    SkeletonAxeMan,
    SkeletonAxeThrower,
    SkeletonWarrior,
    SkeletonLord,

    CaveMaggot,
    GhostSorcerer,
    GhostMage,
    VoraciousGhost,
    DevouringGhost,
    CorpseRaisingGhost,
    GhoulChampion,

    ArmoredAnt,
    AntSoldier,
    AntHealer,
    AntNeedler,

    ShellNipper,
    Beetle,
    VisceralWorm,

    MutantFlea,
    PoisonousMutantFlea,
    BlasterMutantFlea,

    WasHatchling,
    Centipede,
    ButterflyWorm,
    MutantMaggot,
    Earwig,
    IronLance,
    LordNiJae,

    RottingGhoul,
    DecayingGhoul,
    BloodThirstyGhoul,

    SpinedDarkLizard,
    UmaInfidel,
    UmaFlameThrower,
    UmaAnguisher,
    UmaKing,

    SpiderBat,
    ArachnidGazer,
    Larva,
    RedMoonGuardian,
    RedMoonProtector,
    VenomousArachnid,
    DarkArachnid,
    RedMoonTheFallen,

    ZumaSharpShooter,
    ZumaFanatic,
    ZumaGuardian,
    ViciousRat,
    ZumaKing,

    EvilFanatic,
    Monkey,
    EvilElephant,
    CannibalFanatic,

    SpikedBeetle,
    NumaGrunt,
    NumaMage,
    NumaElite,
    SandShark,
    StoneGolem,
    WindfurySorceress,
    CursedCactus,
    NetherWorldGate,

    RagingLizard,
    SawToothLizard,
    MutantLizard,
    VenomSpitter,
    SonicLizard,
    GiantLizard,
    CrazedLizard,
    TaintedTerror,
    DeathLordJichon,

    Minotaur,
    FrostMinotaur,
    ShockMinotaur,
    FlameMinotaur,
    FuryMinotaur,
    BanyaLeftGuard,
    BanyaRightGuard,
    EmperorSaWoo,

    BoneArcher,
    BoneBladesman,
    BoneCaptain,
    BoneSoldier,
    ArchLichTaedu,

    WedgeMothLarva,
    LesserWedgeMoth,
    WedgeMoth,
    RedBoar,
    ClawSerpent,
    BlackBoar,
    TuskLord,
    RazorTusk,

    PinkGoddess,
    GreenGoddess,
    MutantCaptain,
    StoneGriffin,
    FlameGriffin,

    WhiteBone,
    Shinsu,
    InfernalSoldier,
    InfernalGuardian,
    InfernalWarrior,

    CorpseStalker,
    LightArmedSoldier,
    CorrosivePoisonSpitter,
    PhantomSoldier,
    MutatedOctopus,
    AquaLizard,
    Stomper,
    CrimsonNecromancer,
    ChaosKnight,
    PachonTheChaosBringer,

    NumaCavalry,
    NumaHighMage,
    NumaStoneThrower,
    NumaRoyalGuard,
    NumaArmoredSoldier,

    IcyRanger,
    IcyGoddess,
    IcySpiritWarrior,
    IcySpiritGeneral,
    GhostKnight,
    IcySpiritSpearman,
    Werewolf,
    Whitefang,
    IcySpiritSolider,
    WildBoar,
    JinamStoneGate,
    FrostLordHwa,

    Companion_Pig,
    Companion_TuskLord,
    Companion_SkeletonLord,
    Companion_Griffin,
    Companion_Dragon,
    Companion_Donkey,
    Companion_Sheep,
    Companion_BanyoLordGuzak,
    Companion_Panda,
    Companion_Rabbit,

    JinchonDevil,
    OmaWarlord,

    EscortCommander,
    FieryDancer,
    EmeraldDancer,
    QueenOfDawn,

    OYoungBeast,
    YumgonWitch,
    MaWarlord,
    JinhwanSpirit,
    JinhwanGuardian,
    YumgonGeneral,
    ChiwooGeneral,
    DragonQueen,
    DragonLord,

    FerociousIceTiger,

    SamaFireGuardian,
    SamaIceGuardian,
    SamaLightningGuardian,
    SamaWindGuardian,
    Phoenix,
    BlackTortoise,
    BlueDragon,
    WhiteTiger,
    SamaCursedBladesman,
    SamaCursedSlave,
    SamaCursedFlameMage,
    SamaProphet,
    SamaSorcerer,
    EnshrinementBox,
    BloodStone,

    OrangeTiger,
    RegularTiger,
    RedTiger,
    SnowTiger,
    BlackTiger,
    BigBlackTiger,
    BigWhiteTiger,
    OrangeBossTiger,
    BigBossTiger,
    WildMonkey,
    FrostYeti,

    EvilSnake,
    Salamander,
    SandGolem,
    SDMob4,
    SDMob5,
    SDMob6,
    SDMob7,
    OmaMage,
    SDMob9,
    SDMob10,
    SDMob11,
    SDMob12,
    SDMob13,
    SDMob14,
    CrystalGolem,
    DustDevil,
    TwinTailScorpion,
    BloodyMole,
    SDMob19,
    SDMob20,
    SDMob21,
    SDMob22,
    SDMob23,
    SDMob24,
    SDMob25,
    GangSpider,
    VenomSpider,
    SDMob26,

    LobsterLord,
    LobsterSpawn,

    NewMob1,
    NewMob2,
    NewMob3,
    NewMob4,
    NewMob5,
    NewMob6,
    NewMob7,
    NewMob8,
    NewMob9,
    NewMob10,

    MonasteryMon0,
    MonasteryMon1,
    MonasteryMon2,
    MonasteryMon3,
    MonasteryMon4,
    MonasteryMon5,
    MonasteryMon6,
};

enum class MapIcon : int
{
    None,
    Cave,
    Exit,
    Down,
    Up,
    Province,
    Building
};

enum class Effect : int
{
    TeleportOut,
    TeleportIn,

    FullBloom,
    WhiteLotus,
    RedLotus,
    SweetBrier,
    Karma,

    Puppet,
    PuppetFire,
    PuppetIce,
    PuppetLightning,
    PuppetWind,

    SummonSkeleton,
    SummonShinsu,

    ThunderBolt,
    DanceOfSwallow,
    FlashOfLight,

    DemonExplosion,
    FrostBiteEnd
};

// Flags 枚举
enum class PoisonType : uint8_t
{
    None = 0,
    Green = 1,
    Red = 2,
    Slow = 4,
    Paralysis = 8,
    WraithGrip = 16,
    HellFire = 32,
    Silenced = 64,
    Abyss = 128,
    Infection = 256,
};

// 位运算操作符
inline PoisonType operator|(PoisonType a, PoisonType b)
{
    return static_cast<PoisonType>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline PoisonType operator&(PoisonType a, PoisonType b)
{
    return static_cast<PoisonType>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline PoisonType operator^(PoisonType a, PoisonType b)
{
    return static_cast<PoisonType>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

inline PoisonType operator~(PoisonType a)
{
    return static_cast<PoisonType>(~static_cast<uint8_t>(a));
}

inline PoisonType& operator|=(PoisonType& a, PoisonType b)
{
    a = a | b;
    return a;
}

enum class SpellEffect : int
{
    None,

    SafeZone,

    FireWall,
    MonsterFireWall,
    Tempest,

    TrapOctagon,

    PoisonousCloud,

    Rubble,

    MonsterDeathCloud,
};

enum class MarketPlaceSort : int
{
    Newest,
    Oldest,
    HighestPrice,   // Highest Price
    LowestPrice,    // Lowest Price
};

enum class MarketPlaceStoreSort : int
{
    Alphabetical,
    HighestPrice,   // Highest Price
    LowestPrice,    // Lowest Price
    Favourite
};

enum class RefineType : uint8_t
{
    None,
    Durability,
    DC,
    SpellPower,
    Fire,
    Ice,
    Lightning,
    Wind,
    Holy,
    Dark,
    Phantom,
    Reset,
    Health,
    Mana,
    AC,
    MR,
    Accuracy,
    Agility,
    DCPercent,
    SPPercent,
    HealthPercent,
    ManaPercent,
};

enum class RefineQuality : uint8_t
{
    Rush,
    Quick,
    Standard,
    Careful,
    Precise,
};

enum class ItemEffect : uint8_t
{
    None,

    Gold = 1,
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

    WeaponTemplate = 60,
    WarriorWeapon = 61,
    WizardWeapon = 63,
    TaoistWeapon = 64,
    AssassinWeapon = 65,

    YellowSlot = 70,
    BlueSlot = 71,
    RedSlot = 72,
    PurpleSlot = 73,
    GreenSlot = 74,
    GreySlot = 75,

    FootballArmour = 80,
    FootBallWhistle = 81,

    StatExtractor = 90,
    SpiritBlade = 91,
    RefineExtractor = 92,
};

// Flags 枚举
enum class UserItemFlags : uint8_t
{
    None = 0,

    Locked = 1,
    Bound = 2,
    Worthless = 4,
    Refinable = 8,
    Expirable = 16,
    QuestItem = 32,
    GameMaster = 64,
    Marriage = 128,
    NonRefinable = 256
};

// 位运算操作符
inline UserItemFlags operator|(UserItemFlags a, UserItemFlags b)
{
    return static_cast<UserItemFlags>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline UserItemFlags operator&(UserItemFlags a, UserItemFlags b)
{
    return static_cast<UserItemFlags>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline UserItemFlags operator^(UserItemFlags a, UserItemFlags b)
{
    return static_cast<UserItemFlags>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

inline UserItemFlags operator~(UserItemFlags a)
{
    return static_cast<UserItemFlags>(~static_cast<uint8_t>(a));
}

inline UserItemFlags& operator|=(UserItemFlags& a, UserItemFlags b)
{
    a = a | b;
    return a;
}

enum class HorseType : uint8_t
{
    None,
    Brown,
    White,
    Red,
    Black,
};

// Flags 枚举
enum class GuildPermission : uint8_t
{
    None = 0,

    Leader = 255,  // -1 在 byte 中是 255

    EditNotice = 1,
    AddMember = 2,
    RemoveMember = 4,
    Storage = 8,
    FundsRepair = 16,
    FundsMerchant = 32,
    FundsMarket = 64,
    StartWar = 128,
};

// 位运算操作符
inline GuildPermission operator|(GuildPermission a, GuildPermission b)
{
    return static_cast<GuildPermission>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline GuildPermission operator&(GuildPermission a, GuildPermission b)
{
    return static_cast<GuildPermission>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

inline GuildPermission operator^(GuildPermission a, GuildPermission b)
{
    return static_cast<GuildPermission>(static_cast<uint8_t>(a) ^ static_cast<uint8_t>(b));
}

inline GuildPermission operator~(GuildPermission a)
{
    return static_cast<GuildPermission>(~static_cast<uint8_t>(a));
}

// Flags 枚举
enum class QuestIcon : uint8_t
{
    None = 0,

    NewQuest = 1,
    QuestIncomplete = 2,
    QuestComplete = 4,

    NewRepeatable = 8,
    RepeatableComplete = 16,
};

// 位运算操作符
inline QuestIcon operator|(QuestIcon a, QuestIcon b)
{
    return static_cast<QuestIcon>(static_cast<uint8_t>(a) | static_cast<uint8_t>(b));
}

inline QuestIcon operator&(QuestIcon a, QuestIcon b)
{
    return static_cast<QuestIcon>(static_cast<uint8_t>(a) & static_cast<uint8_t>(b));
}

enum class MovementEffect : int
{
    None = 0,

    SpecialRepair = 1,
};

enum class SpellKey : uint8_t
{
    None,

    Spell01,  // Key\n1
    Spell02,  // Key\n2
    Spell03,  // Key\n3
    Spell04,  // Key\n4
    Spell05,  // Key\n5
    Spell06,  // Key\n6
    Spell07,  // Key\n7
    Spell08,  // Key\n8
    Spell09,  // Key\n9
    Spell10,  // Key\n10
    Spell11,  // Key\n11
    Spell12,  // Key\n12

    Spell13,  // Key\n13
    Spell14,  // Key\n14
    Spell15,  // Key\n15
    Spell16,  // Key\n16
    Spell17,  // Key\n17
    Spell18,  // Key\n18
    Spell19,  // Key\n19
    Spell20,  // Key\n20
    Spell21,  // Key\n21
    Spell22,  // Key\n22
    Spell23,  // Key\n23
    Spell24,  // Key\n24
};

enum class MonsterFlag : int
{
    None = 0,

    Skeleton = 1,
    JinSkeleton = 2,
    Shinsu = 3,
    InfernalSoldier = 4,
    Scarecrow = 5,

    SummonPuppet = 6,

    MirrorImage = 7,

    Larva = 100,

    LesserWedgeMoth = 110,

    ZumaArcherMonster = 120,
    ZumaGuardianMonster = 121,
    ZumaFanaticMonster = 122,
    ZumaKeeperMonster = 123,

    BoneArcher = 130,
    BoneCaptain = 131,
    BoneBladesman = 132,
    BoneSoldier = 133,
    SkeletonEnforcer = 134,

    MatureEarwig = 140,
    GoldenArmouredBeetle = 141,
    Millipede = 142,

    FerociousFlameDemon = 150,
    FlameDemon = 151,

    GoruSpearman = 160,
    GoruArcher = 161,
    GoruGeneral = 162,

    DragonLord = 170,
    OYoungBeast = 171,
    YumgonWitch = 172,
    MaWarden = 173,
    MaWarlord = 174,
    JinhwanSpirit = 175,
    JinhwanGuardian = 176,
    OyoungGeneral = 177,
    YumgonGeneral = 178,

    BanyoCaptain = 180,

    SamaSorcerer = 190,
    BloodStone = 191,

    QuartzPinkBat = 200,
    QuartzBlueBat = 201,
    QuartzBlueCrystal = 202,
    QuartzRedHood = 203,
    QuartzMiniTurtle = 204,
    QuartzTurtleSub = 205,

    Sacrafice = 210,
};

// ========== Packet Enums ==========

enum class NewAccountResult : uint8_t
{
    Disabled,
    BadEMail,
    BadPassword,
    BadRealName,
    AlreadyExists,
    BadReferral,
    ReferralNotFound,
    ReferralNotActivated,
    Success
};

enum class ChangePasswordResult : uint8_t
{
    Disabled,
    BadEMail,
    BadCurrentPassword,
    BadNewPassword,
    AccountNotFound,
    AccountNotActivated,
    WrongPassword,
    Banned,
    Success
};

enum class RequestPasswordResetResult : uint8_t
{
    Disabled,
    BadEMail,
    AccountNotFound,
    AccountNotActivated,
    ResetDelay,
    Banned,
    Success
};

enum class ResetPasswordResult : uint8_t
{
    Disabled,
    AccountNotFound,
    BadNewPassword,
    KeyExpired,
    Success
};

enum class ActivationResult : uint8_t
{
    Disabled,
    AccountNotFound,
    Success,
};

enum class RequestActivationKeyResult : uint8_t
{
    Disabled,
    BadEMail,
    AccountNotFound,
    AlreadyActivated,
    RequestDelay,
    Success,
};

enum class LoginResult : uint8_t
{
    Disabled,
    BadEMail,
    BadPassword,
    AccountNotExists,
    AccountNotActivated,
    WrongPassword,
    Banned,
    AlreadyLoggedIn,
    AlreadyLoggedInPassword,
    AlreadyLoggedInAdmin,
    Success
};

enum class NewCharacterResult : uint8_t
{
    Disabled,
    BadCharacterName,
    BadGender,
    BadClass,
    BadHairType,
    BadHairColour,
    BadArmourColour,
    ClassDisabled,
    MaxCharacters,
    AlreadyExists,
    Success
};

enum class DeleteCharacterResult : uint8_t
{
    Disabled,
    AlreadyDeleted,
    NotFound,
    Success
};

enum class StartGameResult : uint8_t
{
    Disabled,
    Deleted,
    Delayed,
    UnableToSpawn,
    NotFound,
    Success
};

enum class DisconnectReason : uint8_t
{
    Unknown,
    TimedOut,
    WrongVersion,
    ServerClosing,
    AnotherUser,
    AnotherUserPassword,
    AnotherUserAdmin,
    Banned,
    Crashed
};

// ========== Sound Enums ==========

enum class SoundIndex : int
{
    None,
    LoginScene,
    SelectScene,

    B000,
    B2,
    B8,
    B009D,
    B009N,
    B0014D,
    B0014N,
    B100,
    B122,
    B300,
    B400,
    B14001,
    BD00,
    BD01,
    BD02,
    BD041,
    BD042,
    BD50,
    BD60,
    BD70,
    BD99,
    BD100,
    BD101,
    BD210,
    BD211,
    BDUnderseaCave,
    BDUnderseaCaveBoss,
    D3101,
    D3102,
    D3400,
    Dungeon_1,
    Dungeon_2,
    ID1_001,
    ID1_002,
    ID1_003,
    TS001,
    TS002,
    TS003,

    ButtonA,
    ButtonB,
    ButtonC,

    SelectWarriorMale,
    SelectWarriorFemale,
    SelectWizardMale,
    SelectWizardFemale,
    SelectTaoistMale,
    SelectTaoistFemale,
    SelectAssassinMale,
    SelectAssassinFemale,

    TeleportOut,
    TeleportIn,

    ItemPotion,
    ItemWeapon,
    ItemArmour,
    ItemRing,
    ItemBracelet,
    ItemNecklace,
    ItemHelmet,
    ItemShoes,
    ItemDefault,

    GoldPickUp,
    GoldGained,

    DaggerSwing,
    WoodSwing,
    IronSwordSwing,
    ShortSwordSwing,
    AxeSwing,
    ClubSwing,
    WandSwing,
    FistSwing,
    GlaiveAttack,
    ClawAttack,

    GenericStruckPlayer,
    GenericStruckMonster,

    Foot1,
    Foot2,
    Foot3,
    Foot4,
    HorseWalk1,
    HorseWalk2,
    HorseRun,

    MaleStruck,
    FemaleStruck,

    MaleDie,
    FemaleDie,

    // Magics
    SlayingMale,
    SlayingFemale,

    EnergyBlast,

    HalfMoon,

    FlamingSword,

    DragonRise,

    BladeStorm,

    DestructiveBlow,

    DefianceStart,

    AssaultStart,

    SwiftBladeEnd,

    FireBallStart,
    FireBallTravel,
    FireBallEnd,

    ThunderBoltStart,
    ThunderBoltTravel,
    ThunderBoltEnd,

    IceBoltStart,
    IceBoltTravel,
    IceBoltEnd,

    GustBlastStart,
    GustBlastTravel,
    GustBlastEnd,

    RepulsionEnd,

    ElectricShockStart,
    ElectricShockEnd,

    GreaterFireBallStart,
    GreaterFireBallTravel,
    GreaterFireBallEnd,

    LightningStrikeStart,
    LightningStrikeEnd,

    GreaterIceBoltStart,
    GreaterIceBoltTravel,
    GreaterIceBoltEnd,

    CycloneStart,
    CycloneEnd,

    TeleportationStart,

    LavaStrikeStart,

    LightningBeamEnd,

    FrozenEarthStart,
    FrozenEarthEnd,

    BlowEarthStart,
    BlowEarthEnd,
    BlowEarthTravel,

    FireWallStart,
    FireWallEnd,

    ExpelUndeadStart,
    ExpelUndeadEnd,

    MagicShieldStart,

    FireStormStart,
    FireStormEnd,

    LightningWaveStart,
    LightningWaveEnd,

    IceStormStart,
    IceStormEnd,

    DragonTornadoStart,
    DragonTornadoEnd,

    GreaterFrozenEarthStart,
    GreaterFrozenEarthEnd,

    ChainLightningStart,
    ChainLightningEnd,

    FrostBiteStart,

    HealStart,
    HealEnd,

    PoisonDustStart,
    PoisonDustEnd,

    ExplosiveTalismanStart,
    ExplosiveTalismanTravel,
    ExplosiveTalismanEnd,

    HolyStrikeStart,
    HolyStrikeTravel,
    HolyStrikeEnd,

    ImprovedHolyStrikeStart,
    ImprovedHolyStrikeTravel,
    ImprovedHolyStrikeEnd,

    MagicResistanceTravel,
    MagicResistanceEnd,

    ResilienceTravel,
    ResilienceEnd,

    ShacklingTalismanStart,
    ShacklingTalismanEnd,

    SummonSkeletonStart,
    SummonSkeletonEnd,

    InvisibilityEnd,

    MassInvisibilityTravel,
    MassInvisibilityEnd,

    TaoistCombatKickStart,

    MassHealStart,
    MassHealEnd,

    BloodLustTravel,
    BloodLustEnd,

    ResurrectionStart,

    PurificationStart,
    PurificationEnd,

    SummonShinsuStart,
    SummonShinsuEnd,

    StrengthOfFaithStart,
    StrengthOfFaithEnd,

    PoisonousCloudStart,

    CloakStart,

    WraithGripStart,
    WraithGripEnd,

    HellFireStart,

    FullBloom,
    WhiteLotus,
    RedLotus,
    SweetBrier,
    SweetBrierMale,
    SweetBrierFemale,

    Karma,

    TheNewBeginning,

    SummonPuppet,

    DanceOfSwallowsEnd,
    DragonRepulseStart,
    AbyssStart,
    FlashOfLightEnd,
    EvasionStart,
    RagingWindStart,

    // Monsters
    ChickenAttack,
    ChickenStruck,
    ChickenDie,

    PigAttack,
    PigStruck,
    PigDie,

    DeerAttack,
    DeerStruck,
    DeerDie,

    CowAttack,
    CowStruck,
    CowDie,

    SheepAttack,
    SheepStruck,
    SheepDie,

    ClawCatAttack,
    ClawCatStruck,
    ClawCatDie,

    WolfAttack,
    WolfStruck,
    WolfDie,

    ForestYetiAttack,
    ForestYetiStruck,
    ForestYetiDie,

    CarnivorousPlantAttack,
    CarnivorousPlantStruck,
    CarnivorousPlantDie,

    OmaAttack,
    OmaStruck,
    OmaDie,

    TigerSnakeAttack,
    TigerSnakeStruck,
    TigerSnakeDie,

    SpittingSpiderAttack,
    SpittingSpiderStruck,
    SpittingSpiderDie,

    ScarecrowAttack,
    ScarecrowStruck,
    ScarecrowDie,

    OmaHeroAttack,
    OmaHeroStruck,
    OmaHeroDie,

    // ... 更多怪物音效将在完整版本中添加
};

} // namespace Library
