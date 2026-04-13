#pragma once
#include "Network/Packet.h"
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <numeric>

namespace Library
{

    public static class Globals
    {
        public static ItemInfo GoldInfo;

        public static DBCollection<ItemInfo> ItemInfoList;
        public static DBCollection<MagicInfo> MagicInfoList;
        public static DBCollection<MapInfo> MapInfoList;
        public static DBCollection<InstanceInfo> InstanceInfoList;
        public static DBCollection<NPCPage> NPCPageList;
        public static DBCollection<MonsterInfo> MonsterInfoList;
        public static DBCollection<FishingInfo> FishingInfoList;
        public static DBCollection<StoreInfo> StoreInfoList;
        public static DBCollection<NPCInfo> NPCInfoList;
        public static DBCollection<MovementInfo> MovementInfoList;
        public static DBCollection<QuestInfo> QuestInfoList;
        public static DBCollection<QuestTask> QuestTaskList;
        public static DBCollection<CompanionInfo> CompanionInfoList;
        public static DBCollection<CompanionLevelInfo> CompanionLevelInfoList;
        public static DBCollection<CurrencyInfo> CurrencyInfoList;
        public static DBCollection<DisciplineInfo> DisciplineInfoList;
        public static DBCollection<FameInfo> FameInfoList;

        public static Random Random = new Random();

        public static readonly Regex EMailRegex = new Regex(@"\w+([-+.]\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*", RegexOptions.Compiled);
        public static readonly Regex PasswordRegex = new Regex(@"^[\S]{" + MinPasswordLength + "," + MaxPasswordLength + "}$", RegexOptions.Compiled);
        public static readonly Regex CharacterReg = new Regex(@"^[A-Za-z0-9]{" + MinCharacterNameLength + "," + MaxCharacterNameLength + @"}$", RegexOptions.Compiled);
        public static readonly Regex GuildNameRegex = new Regex(@"^[A-Za-z0-9]{" + MinGuildNameLength + "," + MaxGuildNameLength + "}$", RegexOptions.Compiled);
        public static readonly Regex GuildTaxReg = new Regex(@"^(0|[1-9][0-9]?|100)$", RegexOptions.Compiled);
        public static readonly Regex CaptionReg = new Regex(@"^[A-Za-z0-9]{" + MinCaptionLength + "," + MaxCaptionLength + @"}$", RegexOptions.Compiled);

        public static Color NoneColour = Color.White,
                            FireColour = Color.OrangeRed,
                            IceColour = Color.PaleTurquoise,
                            LightningColour = Color.LightSkyBlue,
                            WindColour = Color.LightSeaGreen,
                            HolyColour = Color.DarkKhaki,
                            DarkColour = Color.SaddleBrown,
                            PhantomColour = Color.Purple,
                            BrownNameColour = Color.Brown,
                            RedNameColour = Color.Red,

                            PlayerLightColour = Color.FromArgb(120, 255, 255, 255);

        public const std::string ClientName = "Legend of Mir 3";

        public const int32_t
            MinPasswordLength = 5,
            MaxPasswordLength = 15,

            MinRealNameLength = 3,
            MaxRealNameLength = 20,


            MinCaptionLength = 3,
            MaxCaptionLength = 25,

            MaxEMailLength = 50,

            MinCharacterNameLength = 3,
            MaxCharacterNameLength = 15,
            MaxCharacterCount = 4,

            MinGuildNameLength = 2,
            MaxGuildNameLength = 15,

            MaxChatLength = 120,
            MaxGuildNoticeLength = 4000,

            MaxBeltCount = 10,
            MaxAutoPotionCount = 8,

            MagicRange = 10,
            MagicMaxLevel = 4,

            InstanceUnloadTimeInMinutes = 5,

            DuraLossRate = 15,

            GroupLimit = 12,

            MaxGrowthLevel = 3,

            MaxMailStorage = 50,

            CloakRange = 3,
            MarketPlaceFee = 0,
            AccessoryLevelCost = 0,
            AccessoryResetCost = 1000000,

            CraftWeaponPercentCost = 1000000,

            CommonCraftWeaponPercentCost = 30000000,
            SuperiorCraftWeaponPercentCost = 60000000,
            EliteCraftWeaponPercentCost = 80000000,

            ShurikenLibraryWeaponShape = 33;

        public static decimal MarketPlaceTax = 0.07M;  //2.5x Item cost

        public static Regex LinkedItemRegex = new Regex(@"\[(?<Text>.*?):(?<ID>.+?)\]", RegexOptions.Compiled);

        public static int64_t
            GuildCreationCost = 7500000,
            GuildMemberCost = 1000000,
            GuildStorageCost = 350000,
            GuildWarCost = 200000;

        public static int64_t
            MasterRefineCost = 50000,
            MasterRefineEvaluateCost = 250000;

        public static int32_t
            PhysicalPoisonRate = 200,
            MagicalPoisonRate = 100;

        public static std::vector<std::string> Languages = new std::vector<std::string>
        {
            "English",
            "Chinese",
};

        public static std::vector<decimal> ExperienceList = new std::vector<decimal>
        {
            0,
            100,
            200,
            300,
            400,
            600,
            900,
            1200,
            1700,
            2500,
            6000,
            8000,
            10000,
            15000,
            30000,
            40000,
            50000,
            70000,
            100000,
            120000,
            140000,
            250000,
            300000,
            350000,
            400000,
            500000,
            700000,
            1000000,
            1400000,
            1800000,
            2000000,
            2400000,
            2800000,
            3200000,
            3600000,
            4000000,
            4800000,
            5600000,
            8200000,
            9000000,
            11000000,
            14000000,
            18000000,
            22000000,
            25000000,
            30000000,
            35000000,
            40000000,
            50000000,
            60000000,
            70000000,
            85000000,
            110000000,
            135000000,
            145000000,
            150000000,
            175000000,
            180000000,
            200000000,
            220000000,
            230000000,
            240000000,
            250000000,
            260000000,
            270000000,
            280000000,
            300000000,
            320000000,
            340000000,
            360000000,
            380000000,
            400000000,
            800000000,
            1400000000,
            2200000000,
            6530000000,
            12000000000,
            30000000000,
            75000000000,
            150000000000,
            175000000000,
            300000000000,
            430000000000,
            570000000000,
            700000000000,
            800000000000,
            900000000000,
            3000000000000,
            6000000000000,
            9000000000000,
            13000000000000,
            17000000000000,
            144000000000000,
            146000000000000,
            149000000000000,
            162000000000000,
            166000000000000,
            172000000000000,
            180000000000000,
            188000000000000,
            200000000000000,
};

        public static std::vector<decimal> WeaponExperienceList = new std::vector<decimal>
        {
            0, //0

            300000,
            350000,
            400000,
            450000,
            500000,
            550000,
            600000,
            650000,
            700000,
            750000, //10

            800000,
            850000,
            900000,
            1000000,
            1300000,
            2000000,
};

        public static std::vector<decimal> AccessoryExperienceList = new std::vector<decimal>
        {
            0,

            5,
            20,
            80,
            350,
            1500,
            6200,
            26500,
            114000,
            490000,
            2090000,
};

        public const int32_t InventorySize = 48,
                         EquipmentSize = 22,
                         CompanionInventorySize = 30,
                         CompanionEquipmentSize = 4,
                         EquipmentOffSet = 1000,
                         StorageSize = 100,
                         PartsStorageOffset = 2000;

        public const int32_t AttackDelay = 1500,
                         ASpeedRate = 47,
                         ProjectileSpeed = 48;

        public static TimeSpan TurnTime = TimeSpan.FromMilliseconds(300),
                               HarvestTime = TimeSpan.FromMilliseconds(600),
                               MoveTime = TimeSpan.FromMilliseconds(600),
                               AttackTime = TimeSpan.FromMilliseconds(600),
                               CastTime = TimeSpan.FromMilliseconds(600),
                               MagicDelay = TimeSpan.FromMilliseconds(2000);

        public static bool RealNameRequired = false,
                           BirthDateRequired = false;

        public static std::unordered_map<RefineQuality, TimeSpan> RefineTimes = new std::unordered_map<RefineQuality, TimeSpan>
        {
            [RefineQuality.Rush] = TimeSpan.FromMinutes(1),
            [RefineQuality.Quick] = TimeSpan.FromMinutes(30),
            [RefineQuality.Standard] = TimeSpan.FromHours(1),
            [RefineQuality.Careful] = TimeSpan.FromHours(6),
            [RefineQuality.Precise] = TimeSpan.FromDays(1),
};

        public static std::string PluginPath(std::string assemblyName)
        {
            return "Plugins" + "\\" + assemblyName + "\\";
};
};

    class SelectInfo
    {
        int32_t CharacterIndex;
        std::string CharacterName;
        std::string Caption;
        int32_t Level;
        MirGender Gender;
        MirClass Class;
        int32_t Location;
        DateTime LastLogin;
};

    class StartInformation
    {
        int32_t Index;
        uint32_t ObjectID;
        std::string Name;

        std::string Caption;
        Color NameColour;
        std::string GuildName;
        std::string GuildRank;

        MirClass Class;
        MirGender Gender;
        Point Location;
        MirDirection Direction;

        int32_t MapIndex;
        int32_t InstanceIndex;

        int32_t Level;
        int32_t HairType;
        Color HairColour;
        int32_t Weapon;
        int32_t Armour;
        int32_t Costume;
        int32_t Shield;
        Color ArmourColour;

        ExteriorEffect ArmourEffect;
        ExteriorEffect EmblemEffect;
        ExteriorEffect WeaponEffect;
        ExteriorEffect ShieldEffect;

        decimal Experience;

        int32_t CurrentHP;
        int32_t CurrentMP;
        int32_t CurrentFP;

        AttackMode AttackMode;
        PetMode PetMode;

        OnlineState OnlineState;

        ClientUserDiscipline Discipline;

        int32_t HermitPoints;

        float DayTime;
        bool AllowGroup;

        std::vector<ClientFriendInfo> Friends;

        std::vector<ClientUserItem> Items;
        std::vector<ClientBeltLink> BeltLinks;
        std::vector<ClientAutoPotionLink> AutoPotionLinks;

        std::vector<ClientUserMagic> Magics;
        std::vector<ClientBuffInfo> Buffs;

        std::vector<ClientUserCurrency> Currencies;

        PoisonType Poison;

        bool InSafeZone;
        bool Observable;

        bool Dead;

        HorseType Horse; //Horse Armour too

        int32_t HelmetShape;
        int32_t HorseShape;

        bool HideHead;

        std::vector<ClientUserQuest> Quests;

        std::vector<int32_t> CompanionUnlocks;
        public std::vector<CompanionInfo> AvailableCompanions = new std::vector<CompanionInfo>();

        std::vector<ClientUserCompanion> Companions;

        int32_t Companion;

        int32_t StorageSize;

        std::string FiltersClass;
        std::string FiltersRarity;
        std::string FiltersItemType;

        //Server settings
        bool StruckEnabled;
        bool HermitEnabled;

        [CompleteObject]
        public void OnComplete()
        {
            foreach (int32_t index in CompanionUnlocks)
                AvailableCompanions.Add(Globals.CompanionInfoList.Binding.First(x => x.Index == index));
};
};

    class ClientUserItem
    {
        public ItemInfo Info;

        int32_t Index; //ItemID
        int32_t InfoIndex;

        int32_t CurrentDurability;
        int32_t MaxDurability;

        int64_t Count;

        int32_t Slot;

        int32_t Level;
        decimal Experience;

        Color Colour;

        TimeSpan SpecialRepairCoolDown;
        TimeSpan ResetCoolDown;

        public bool New;
        public DateTime NextSpecialRepair, NextReset;

        Stats AddedStats;

        UserItemFlags Flags;
        TimeSpan ExpireTime;
    // IgnorePropertyPacket
    public int32_t Weight
        {
            get
            {
                switch (Info.ItemType)
                {
                    case ItemType.Poison:
                    case ItemType.Amulet:
                        return Info.Weight;
                    default:
                        return (int32_t)std::min(int32_t.MaxValue, Info.Weight * Count);
};
};
};

        [CompleteObject]
        public void Complete()
        {
            Info = Globals.ItemInfoList.Binding.FirstOrDefault(x => x.Index == InfoIndex);

            NextSpecialRepair = Time.Now + SpecialRepairCoolDown;
            NextReset = Time.Now + ResetCoolDown;
};

        public ClientUserItem()
        { }
        public ClientUserItem(ItemInfo info, int64_t count)
        {
            Info = info;
            Count = count;
            MaxDurability = info.Durability;
            CurrentDurability = info.Durability;
            Level = 1;
            AddedStats = new Stats();
};
        public ClientUserItem(ClientUserItem item, int64_t count)
        {
            Info = item.Info;

            Index = item.Index;
            InfoIndex = item.InfoIndex;

            CurrentDurability = item.CurrentDurability;
            MaxDurability = item.MaxDurability;

            Count = count;

            Slot = item.Slot;

            Level = item.Level;
            Experience = item.Experience;

            Colour = item.Colour;

            SpecialRepairCoolDown = item.SpecialRepairCoolDown;

            Flags = item.Flags;
            ExpireTime = item.ExpireTime;

            New = item.New;
            NextSpecialRepair = item.NextSpecialRepair;

            AddedStats = new Stats(item.AddedStats);
};


        public int64_t Price(int64_t count)
        {
            if ((Flags & UserItemFlags.Worthless) == UserItemFlags.Worthless) return 0;

            decimal p = Info.Price;

            if (Info.Durability > 0)
            {
                decimal r = Info.Price / 2M / Info.Durability;

                p = MaxDurability * r;

                r = MaxDurability > 0 ? CurrentDurability / (decimal)MaxDurability : 0;

                p = Math.Floor(p / 2M + p / 2M * r + Info.Price / 2M);
};

            p = p * (AddedStats.Count * 0.1M + 1M);

            if (Info.Stats[Stat.SaleBonus20] > 0 && Info.Stats[Stat.SaleBonus20] <= count)
                p *= 1.2M;
            else if (Info.Stats[Stat.SaleBonus15] > 0 && Info.Stats[Stat.SaleBonus15] <= count)
                p *= 1.15M;
            else if (Info.Stats[Stat.SaleBonus10] > 0 && Info.Stats[Stat.SaleBonus10] <= count)
                p *= 1.1M;
            else if (Info.Stats[Stat.SaleBonus5] > 0 && Info.Stats[Stat.SaleBonus5] <= count)
                p *= 1.05M;

            return (int64_t)(p * count * Info.SellRate);
};

        public int32_t RepairCost(bool special)
        {
            if (Info.Durability == 0 || CurrentDurability >= MaxDurability) return 0;

            int32_t rate = special ? 2 : 1;

            decimal p = Math.Floor(MaxDurability * (Info.Price / 2M / Info.Durability) + Info.Price / 2M);
            p = p * (AddedStats.Count * 0.1M + 1M);

            return (int32_t)(p * Count - Price(Count)) * rate;


};
        public bool CanAccessoryUpgrade()
        {
            switch (Info.ItemType)
            {
                case ItemType.Ring:
                case ItemType.Bracelet:
                case ItemType.Necklace:
                    break;
                default: return false;

};

            return (Flags & UserItemFlags.NonRefinable) != UserItemFlags.NonRefinable && (Flags & UserItemFlags.Refinable) == UserItemFlags.Refinable;
};
        public bool CanFragment()
        {
            if ((Flags & UserItemFlags.NonRefinable) == UserItemFlags.NonRefinable || (Flags & UserItemFlags.Worthless) == UserItemFlags.Worthless) return false;

            switch (Info.Rarity)
            {
                case Rarity.Common:
                    if (Info.RequiredAmount <= 15) return false;
                    break;
                case Rarity.Superior:
                    break;
                case Rarity.Elite:
                    break;
};

            switch (Info.ItemType)
            {
                case ItemType.Weapon:
                case ItemType.Armour:
                case ItemType.Helmet:
                case ItemType.Necklace:
                case ItemType.Bracelet:
                case ItemType.Ring:
                case ItemType.Shoes:
                    break;
                default:
                    return false;
};

            return true;
};
        public int32_t FragmentCost()
        {
            switch (Info.Rarity)
            {
                case Rarity.Common:
                    switch (Info.ItemType)
                    {
                        case ItemType.Armour:
                        case ItemType.Weapon:
                        case ItemType.Helmet:
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                        case ItemType.Shoes:
                            return Info.RequiredAmount * 10000 / 9;
                        /* case ItemType.Helmet:
                         case ItemType.Necklace:
                         case ItemType.Bracelet:
                         case ItemType.Ring:
                         case ItemType.Shoes:
                             return Info.RequiredAmount * 7000 / 9;*/
                        default:
                            return 0;
};
                case Rarity.Superior:
                    switch (Info.ItemType)
                    {
                        case ItemType.Weapon:
                        case ItemType.Armour:
                        case ItemType.Helmet:
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                        case ItemType.Shoes:
                            return Info.RequiredAmount * 10000 / 2;
                        /*  case ItemType.Helmet:
                          case ItemType.Necklace:
                          case ItemType.Bracelet:
                          case ItemType.Ring:
                          case ItemType.Shoes:
                              return Info.RequiredAmount * 10000 / 10;*/
                        default:
                            return 0;
};
                case Rarity.Elite:
                    switch (Info.ItemType)
                    {
                        case ItemType.Weapon:
                        case ItemType.Armour:
                            return 250000;
                        case ItemType.Helmet:
                            return 50000;
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                            return 150000;
                        case ItemType.Shoes:
                            return 30000;
                        default:
                            return 0;
};
                default:
                    return 0;
};
};
        public int32_t FragmentCount()
        {
            switch (Info.Rarity)
            {
                case Rarity.Common:
                    switch (Info.ItemType)
                    {
                        case ItemType.Armour:
                        case ItemType.Weapon:
                        case ItemType.Helmet:
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                        case ItemType.Shoes:
                            return std::max(1, Info.RequiredAmount / 2 + 5);
                        /*  case ItemType.Helmet:
                              return std::max(1, (Info.RequiredAmount - 30) / 6);
                          case ItemType.Necklace:
                              return std::max(1, Info.RequiredAmount / 8);
                          case ItemType.Bracelet:
                              return std::max(1, Info.RequiredAmount / 15);
                          case ItemType.Ring:
                              return std::max(1, Info.RequiredAmount / 9);
                          case ItemType.Shoes:
                              return std::max(1, (Info.RequiredAmount - 35) / 6);*/
                        default:
                            return 0;
};
                case Rarity.Superior:
                    switch (Info.ItemType)
                    {
                        case ItemType.Armour:
                        case ItemType.Weapon:
                        case ItemType.Helmet:
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                        case ItemType.Shoes:
                            return std::max(1, Info.RequiredAmount / 2 + 5);
                        /*  case ItemType.Helmet:
                              return std::max(1, (Info.RequiredAmount - 30) / 6);
                          case ItemType.Necklace:
                              return std::max(1, Info.RequiredAmount / 10);
                          case ItemType.Bracelet:
                              return std::max(1, Info.RequiredAmount / 15);
                          case ItemType.Ring:
                              return std::max(1, Info.RequiredAmount / 10);
                          case ItemType.Shoes:
                              return std::max(1, (Info.RequiredAmount - 35) / 6);*/
                        default:
                            return 0;
};
                case Rarity.Elite:
                    switch (Info.ItemType)
                    {
                        case ItemType.Armour:
                        case ItemType.Weapon:
                            return 50;
                        case ItemType.Helmet:
                            return 5;
                        case ItemType.Necklace:
                        case ItemType.Bracelet:
                        case ItemType.Ring:
                            return 10;
                        case ItemType.Shoes:
                            return 3;
                        default:
                            return 0;
};
                default:
                    return 0;
};
};
};

    class ClientBeltLink
    {
        int32_t Slot;
        int32_t LinkInfoIndex;
        int32_t LinkItemIndex;
};

    class ClientAutoPotionLink
    {
        int32_t Slot;
        int32_t LinkInfoIndex;
        int32_t Health;
        int32_t Mana;
        bool Enabled;
};

    class ClientUserMagic
    {
        int32_t Index;
        int32_t InfoIndex;
        public MagicInfo Info;

        SpellKey Set1Key;
        SpellKey Set2Key;
        SpellKey Set3Key;
        SpellKey Set4Key;

        int32_t Level;
        int64_t Experience;
        bool ItemRequired;

        TimeSpan Cooldown;

        public DateTime NextCast;
    // IgnorePropertyPacket
    int32_t GetCost() const { return Info.BaseCost + Level * Info.LevelCost / 3; }

        [CompleteObject]
        public void Complete()
        {
            NextCast = Time.Now + Cooldown;
            Info = Globals.MagicInfoList.Binding.FirstOrDefault(x => x.Index == InfoIndex);
};
};

    class ClientNPCValues
    {
        int32_t ID;
        std::string Value;
};

    class CellLinkInfo
    {
        GridType GridType;
        int32_t Slot;
        int64_t Count;
};

    class ClientBuffInfo
    {
        int32_t Index;
        BuffType Type;
        TimeSpan RemainingTime;
        TimeSpan TickFrequency;
        Stats Stats;
        bool Pause;
        int32_t ItemIndex;
};

    class ClientRefineInfo
    {
        int32_t Index;
        ClientUserItem Weapon;
        RefineType Type;
        RefineQuality Quality;
        int32_t Chance;
        int32_t MaxChance;
        TimeSpan ReadyDuration;

        public DateTime RetrieveTime;

        [CompleteObject]
        public void Complete()
        {
            RetrieveTime = Time.Now + ReadyDuration;
};
};


    class RankInfo
    {
        int32_t Rank;
        int32_t Index;
        std::string Name;
        MirClass Class;
        int32_t Level;
        decimal Experience;
        decimal MaxExperience;
        bool Online;
        bool Observable;
        int32_t Rebirth;
        int32_t RankChange;
};

    class ClientMarketPlaceInfo
    {
        int32_t Index;
        ClientUserItem Item;

        int32_t Price;

        std::string Seller;
        std::string Message;
        bool IsOwner;

        public bool Loading;
};

    class ClientMailInfo
    {
        int32_t Index;
        bool Opened;
        bool HasItem;
        DateTime Date;

        std::string Sender;
        std::string Subject;
        std::string Message;

        int32_t Gold;
        std::vector<ClientUserItem> Items;
};

    class ClientGuildInfo
    {
        std::string GuildName;

        std::string Notice;

        int32_t MemberLimit;

        int64_t GuildFunds;
        int64_t DailyGrowth;

        int64_t TotalContribution;
        int64_t DailyContribution;

        int32_t UserIndex;

        int32_t StorageLimit;
        int32_t Tax;

        std::string DefaultRank;
        GuildPermission DefaultPermission;

        Color Colour;
        int32_t Flag;

        std::vector<ClientGuildMemberInfo> Members;

        std::vector<ClientUserItem> Storage;
    // IgnorePropertyPacket
    GuildPermission GetPermission() const { return Members.FirstOrDefault(x => x.Index == UserIndex)?.Permission ?? GuildPermission.None; }
};

    class ClientGuildMemberInfo
    {
        int32_t Index;
        std::string Name;
        std::string Rank;
        int64_t TotalContribution;
        int64_t DailyContribution;
        TimeSpan Online;

        GuildPermission Permission;

        public DateTime LastOnline;
        uint32_t ObjectID;

        [CompleteObject]
        public void Complete()
        {
            if (Online == TimeSpan.MinValue)
                LastOnline = DateTime.MaxValue;
            else
                LastOnline = Time.Now - Online;
};

};

    class ClientUserQuest
    {
        int32_t Index;
    // IgnorePropertyPacket
    QuestInfo Quest;

        int32_t QuestIndex;

        bool Track;

        bool Completed;

        int32_t SelectedReward;

        DateTime DateTaken;
        DateTime DateCompleted;
    // IgnorePropertyPacket
    bool GetIsComplete() const { return Tasks.Count == Quest.Tasks.Count && Tasks.All(x => x.Completed); }

        std::vector<ClientUserQuestTask> Tasks;

        [CompleteObject]
        public void Complete()
        {
            Quest = Globals.QuestInfoList.Binding.First(x => x.Index == QuestIndex);
};
};

    class ClientUserQuestTask
    {
        int32_t Index;
    // IgnorePropertyPacket
    QuestTask Task;

        int32_t TaskIndex;

        int64_t Amount;
    // IgnorePropertyPacket
    bool GetCompleted() const { return Amount >= Task.Amount; }

        [CompleteObject]
        public void Complete()
        {
            Task = Globals.QuestTaskList.Binding.First(x => x.Index == TaskIndex);
};
};

    class ClientCompanionObject
    {
        std::string Name;

        int32_t HeadShape;
        int32_t BackShape;
};

    class ClientUserCompanion
    {
        int32_t Index;
        std::string Name;

        int32_t CompanionIndex;
        public CompanionInfo CompanionInfo;

        int32_t Level;
        int32_t Hunger;
        int32_t Experience;

        Stats Level3;
        Stats Level5;
        Stats Level7;
        Stats Level10;
        Stats Level11;
        Stats Level13;
        Stats Level15;

        std::string CharacterName;

        std::vector<ClientUserItem> Items;

        public ClientUserItem[] EquipmentArray = new ClientUserItem[Globals.CompanionEquipmentSize], InventoryArray = new ClientUserItem[Globals.CompanionInventorySize];


        [CompleteObject]
        public void OnComplete()
        {
            CompanionInfo = Globals.CompanionInfoList.Binding.First(x => x.Index == CompanionIndex);

            foreach (ClientUserItem item in Items)
            {
                if (item.Slot < Globals.EquipmentOffSet)
                    InventoryArray[item.Slot] = item;
                else
                    EquipmentArray[item.Slot - Globals.EquipmentOffSet] = item;
};
};

};

    class ClientPlayerInfo
    {
        uint32_t ObjectID;

        std::string Name;
};
    class ClientObjectData
    {
        public uint32_t ObjectID;

        public int32_t MapIndex;
        public Point Location;

        public std::string Name;

        //Guild/Group
        public MonsterInfo MonsterInfo;
        public ItemInfo ItemInfo;

        public std::string PetOwner;

        public int32_t Health;
        public int32_t MaxHealth;

        public int32_t Mana;
        public int32_t MaxMana;
        Stats Stats;

        public bool Dead;
};

    class ClientBlockInfo
    {
        int32_t Index;
        std::string Name;
};

    class ClientFriendInfo
    {
        int32_t Index;
        std::string Name;
        OnlineState State;
};

    class ClientFortuneInfo
    {
        int32_t ItemIndex;
        public ItemInfo ItemInfo;

        TimeSpan CheckTime;
        int64_t DropCount;
        decimal Progress;

        public DateTime CheckDate;

        [CompleteObject]
        public void OnComplete()
        {
            ItemInfo = Globals.ItemInfoList.Binding.First(x => x.Index == ItemIndex);

            CheckDate = Time.Now - CheckTime;
};
};

    class CompanionFiltersInfo
    {
        std::string FilterClass;
        std::string FilterRarity;
        std::string FilterItemType;
};

    class ClientUserCurrency
    {
        int32_t CurrencyIndex;
        public CurrencyInfo Info;
        int64_t Amount;
    // IgnorePropertyPacket
    public bool CanPickup
        {
            get { return Info != null && Info.DropItem != null && Info.DropItem.CanDrop; }
};
};

    class ClientUserDiscipline
    {
        int32_t InfoIndex;
        public DisciplineInfo DisciplineInfo;
        int32_t Level;
        int64_t Experience;
        std::vector<ClientUserMagic> Magics;
};

    class ClientGroup
    {
        std::string LeaderName;
        std::string GroupName;
        std::string Description;
        std::string GroupType;
        int32_t CurrentCount;
        int32_t MaxCount;
        bool Enabled;
};

}
