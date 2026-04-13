#pragma once

#include "LibraryCore/Enum.h"
#include "LibraryCore/Stat.h"
#include "LibraryCore/SystemModels/ItemInfo.h"
#include "LibraryCore/SystemModels/MagicInfo.h"
#include "LibraryCore/SystemModels/MapInfo.h"
#include "LibraryCore/SystemModels/NPCInfo.h"
#include "LibraryCore/SystemModels/MonsterInfo.h"
#include "LibraryCore/SystemModels/StoreInfo.h"
#include "LibraryCore/SystemModels/MovementInfo.h"
#include "LibraryCore/SystemModels/QuestInfo.h"
#include "LibraryCore/SystemModels/CompanionInfo.h"
#include "LibraryCore/SystemModels/CompanionLevelInfo.h"
#include "LibraryCore/MirDB/DBCollection.h"
#include <list>
#include <map>
#include <regex>

namespace Library
{
    class ClientUserItem;
    class ClientBeltLink;
    class ClientAutoPotionLink;
    class ClientUserMagic;
    class ClientBuffInfo;
    class ClientRefineInfo;
    class RankInfo;
    class ClientMarketPlaceInfo;
    class ClientMailInfo;
    class ClientGuildInfo;
    class ClientGuildMemberInfo;
    class ClientUserQuest;
    class ClientUserQuestTask;
    class ClientCompanionObject;
    class ClientUserCompanion;
    class ClientPlayerInfo;
    class ClientObjectData;
    class ClientBlockInfo;
    class ClientFortuneInfo;

    class Globals
    {
    public:
        static ItemInfo* GoldInfo;

        static DBCollection<ItemInfo>* ItemInfoList;
        static DBCollection<MagicInfo>* MagicInfoList;
        static DBCollection<MapInfo>* MapInfoList;
        static DBCollection<NPCPage>* NPCPageList;
        static DBCollection<MonsterInfo>* MonsterInfoList;
        static DBCollection<StoreInfo>* StoreInfoList;
        static DBCollection<NPCInfo>* NPCInfoList;
        static DBCollection<MovementInfo>* MovementInfoList;
        static DBCollection<QuestInfo>* QuestInfoList;
        static DBCollection<QuestTask>* QuestTaskList;
        static DBCollection<CompanionInfo>* CompanionInfoList;
        static DBCollection<CompanionLevelInfo>* CompanionLevelInfoList;

        static int RandomValue();
        static void SetRandomSeed(int seed);

        static const std::regex EMailRegex;
        static const std::regex PasswordRegex;
        static const std::regex CharacterReg;
        static const std::regex GuildNameRegex;

        // Colors
        static Color NoneColour;
        static Color FireColour;
        static Color IceColour;
        static Color LightningColour;
        static Color WindColour;
        static Color HolyColour;
        static Color DarkColour;
        static Color PhantomColour;
        static Color BrownNameColour;
        static Color RedNameColour;

        // Constants
        static const int MinPasswordLength = 5;
        static const int MaxPasswordLength = 15;

        static const int MinRealNameLength = 3;
        static const int MaxRealNameLength = 20;

        static const int MaxEMailLength = 50;

        static const int MinCharacterNameLength = 3;
        static const int MaxCharacterNameLength = 15;
        static const int MaxCharacterCount = 4;

        static const int MinGuildNameLength = 2;
        static const int MaxGuildNameLength = 15;

        static const int MaxChatLength = 120;
        static const int MaxGuildNoticeLength = 4000;

        static const int MaxBeltCount = 10;
        static const int MaxAutoPotionCount = 8;

        static const int MagicRange = 10;

        static const int DuraLossRate = 15;

        static const int GroupLimit = 15;

        static const int CloakRange = 3;
        static const int MarketPlaceFee = 0;
        static const int AccessoryLevelCost = 0;
        static const int AccessoryResetCost = 1000000;

        static const int CraftWeaponPercentCost = 1000000;

        static const int CommonCraftWeaponPercentCost = 30000000;
        static const int SuperiorCraftWeaponPercentCost = 60000000;
        static const int EliteCraftWeaponPercentCost = 80000000;

        static const decimal MarketPlaceTax = decimal(0.07); // 2.5x Item cost

        static long GuildCreationCost;
        static long GuildMemberCost;
        static long GuildStorageCost;
        static long GuildWarCost;

        static long MasterRefineCost;
        static long MasterRefineEvaluateCost;

        static std::list<Size> ValidResolutions;
        static std::list<std::string> Languages;

        static std::list<decimal> ExperienceList;
        static std::list<decimal> OldExperienceList;
        static std::list<decimal> WeaponExperienceList;
        static std::list<decimal> AccessoryExperienceList;

        static const int InventorySize = 49;
        static const int EquipmentSize = 17;
        static const int CompanionInventorySize = 40;
        static const int CompanionEquipmentSize = 4;
        static const int PartsStorageOffset = 2000;
        static const int EquipmentOffSet = 1000;
        static const int StorageSize = 100;

        static const int AttackDelay = 1500;
        static const int ASpeedRate = 47;
        static const int ProjectileSpeed = 48;

        static TimeSpan TurnTime;
        static TimeSpan HarvestTime;
        static TimeSpan MoveTime;
        static TimeSpan AttackTime;
        static TimeSpan CastTime;
        static TimeSpan MagicDelay;

        static bool RealNameRequired;
        static bool BirthDateRequired;

        static std::map<RefineQuality, TimeSpan> RefineTimes;

        static void Initialize();
    };

    class SelectInfo
    {
    public:
        int CharacterIndex = 0;
        std::string CharacterName;
        int Level = 0;
        MirGender Gender = MirGender::Male;
        MirClass Class = MirClass::Warrior;
        int Location = 0;
        DateTime LastLogin;
    };

    class StartInformation
    {
    public:
        int Index = 0;
        uint32_t ObjectID = 0;
        std::string Name;
        Color NameColour;
        std::string GuildName;
        std::string GuildRank;

        MirClass Class = MirClass::Warrior;
        MirGender Gender = MirGender::Male;
        Point Location;
        MirDirection Direction = MirDirection::Up;

        int MapIndex = 0;

        long Gold = 0;
        int GameGold = 0;

        int Level = 0;
        int HairType = 0;
        Color HairColour;
        int Weapon = 0;
        int Armour = 0;
        int Shield = 0;
        Color ArmourColour;
        int ArmourImage = 0;

        int EmblemShape = 0;
        int WingsShape = 0;

        decimal Experience = decimal(0);

        int CurrentHP = 0;
        int CurrentMP = 0;

        AttackMode AttackMode = AttackMode::Peace;
        PetMode PetMode = PetMode::Attack;

        int HermitPoints = 0;

        float DayTime = 0.0f;
        bool AllowGroup = false;

        std::vector<ClientUserItem*> Items;
        std::vector<ClientBeltLink*> BeltLinks;
        std::vector<ClientAutoPotionLink*> AutoPotionLinks;

        std::vector<ClientUserMagic*> Magics;
        std::vector<ClientBuffInfo*> Buffs;

        PoisonType Poison = PoisonType::None;

        bool InSafeZone = false;
        bool Observable = true;

        bool Dead = false;

        HorseType Horse = HorseType::None;

        int HelmetShape = 0;
        int HorseShape = 0;

        std::vector<ClientUserQuest*> Quests;

        std::vector<int> CompanionUnlocks;
        std::vector<CompanionInfo*> AvailableCompanions;

        std::vector<ClientUserCompanion*> Companions;

        int Companion = 0;

        int StorageSize = 0;

        void OnComplete();
    };

    class ClientUserItem
    {
    public:
        ItemInfo* Info = nullptr;

        int Index = 0; // ItemID
        int InfoIndex = 0;

        int CurrentDurability = 0;
        int MaxDurability = 0;

        long Count = 0;

        int Slot = 0;

        int Level = 0;
        decimal Experience = decimal(0);

        Color Colour;

        TimeSpan SpecialRepairCoolDown;
        TimeSpan ResetCoolDown;

        bool New = false;
        DateTime NextSpecialRepair;
        DateTime NextReset;

        Stats AddedStats;

        UserItemFlags Flags = UserItemFlags::None;
        TimeSpan ExpireTime;

        int GetWeight() const;

        void Complete();

        ClientUserItem();
        ClientUserItem(ItemInfo* info, long count);
        ClientUserItem(ClientUserItem* item, long count);

        long Price(long count) const;
        int RepairCost(bool special) const;
        bool CanAccessoryUpgrade() const;
        bool CanFragment() const;
        int FragmentCost() const;
        int FragmentCount() const;
    };

    class ClientBeltLink
    {
    public:
        int Slot = 0;
        int LinkInfoIndex = 0;
        int LinkItemIndex = 0;
    };

    class ClientAutoPotionLink
    {
    public:
        int Slot = 0;
        int LinkInfoIndex = 0;
        int Health = 0;
        int Mana = 0;
        bool Enabled = false;
    };

    class ClientUserMagic
    {
    public:
        int Index = 0;
        int InfoIndex = 0;
        MagicInfo* Info = nullptr;

        SpellKey Set1Key;
        SpellKey Set2Key;
        SpellKey Set3Key;
        SpellKey Set4Key;

        int Level = 0;
        long Experience = 0;

        TimeSpan Cooldown;

        DateTime NextCast;

        int GetCost() const;

        void Complete();
    };

    class CellLinkInfo
    {
    public:
        GridType GridType = GridType::Inventory;
        int Slot = 0;
        long Count = 0;
    };

    class ClientBuffInfo
    {
    public:
        int Index = 0;
        BuffType Type = BuffType::None;
        TimeSpan RemainingTime;
        TimeSpan TickFrequency;
        Stats Stats;
        bool Pause = false;
        int ItemIndex = 0;
    };

    class ClientRefineInfo
    {
    public:
        int Index = 0;
        ClientUserItem* Weapon = nullptr;
        RefineType Type = RefineType::None;
        RefineQuality Quality = RefineQuality::Standard;
        int Chance = 0;
        int MaxChance = 0;
        TimeSpan ReadyDuration;

        DateTime RetrieveTime;

        void Complete();
    };

    class RankInfo
    {
    public:
        int Rank = 0;
        int Index = 0;
        std::string Name;
        MirClass Class = MirClass::Warrior;
        int Level = 0;
        decimal Experience = decimal(0);
        decimal MaxExperience = decimal(0);
        bool Online = false;
        bool Observable = true;
        int Rebirth = 0;
    };

    class ClientMarketPlaceInfo
    {
    public:
        int Index = 0;
        ClientUserItem* Item = nullptr;

        int Price = 0;

        std::string Seller;
        std::string Message;
        bool IsOwner = false;

        bool Loading = false;
    };

    class ClientMailInfo
    {
    public:
        int Index = 0;
        bool Opened = false;
        bool HasItem = false;
        DateTime Date;

        std::string Sender;
        std::string Subject;
        std::string Message;

        int Gold = 0;
        std::vector<ClientUserItem*> Items;
    };

    class ClientGuildInfo
    {
    public:
        std::string GuildName;

        std::string Notice;

        int MemberLimit = 0;

        long GuildFunds = 0;
        long DailyGrowth = 0;

        long TotalContribution = 0;
        long DailyContribution = 0;

        int UserIndex = 0;

        int StorageLimit = 0;
        int Tax = 0;

        std::string DefaultRank;
        GuildPermission DefaultPermission = GuildPermission::None;

        std::vector<ClientGuildMemberInfo*> Members;

        std::vector<ClientUserItem*> Storage;

        GuildPermission GetPermission() const;
    };

    class ClientGuildMemberInfo
    {
    public:
        int Index = 0;
        std::string Name;
        std::string Rank;
        long TotalContribution = 0;
        long DailyContribution = 0;
        TimeSpan Online;

        GuildPermission Permission = GuildPermission::None;

        DateTime LastOnline;
        uint32_t ObjectID = 0;

        void Complete();
    };

    class ClientUserQuest
    {
    public:
        int Index = 0;

        QuestInfo* Quest = nullptr;

        int QuestIndex = 0;

        bool Track = false;

        bool Completed = false;

        int SelectedReward = 0;

        bool GetIsComplete() const;

        std::vector<ClientUserQuestTask*> Tasks;

        void Complete();
    };

    class ClientUserQuestTask
    {
    public:
        int Index = 0;

        QuestTask* Task = nullptr;

        int TaskIndex = 0;

        long Amount = 0;

        bool GetCompleted() const;

        void Complete();
    };

    class ClientCompanionObject
    {
    public:
        std::string Name;

        int HeadShape = 0;
        int BackShape = 0;
    };

    class ClientUserCompanion
    {
    public:
        int Index = 0;
        std::string Name;

        int CompanionIndex = 0;
        CompanionInfo* CompanionInfo = nullptr;

        int Level = 0;
        int Hunger = 0;
        int Experience = 0;

        Stats Level3;
        Stats Level5;
        Stats Level7;
        Stats Level10;
        Stats Level11;
        Stats Level13;
        Stats Level15;

        std::string CharacterName;

        std::vector<ClientUserItem*> Items;

        std::vector<ClientUserItem*> EquipmentArray;
        std::vector<ClientUserItem*> InventoryArray;

        void OnComplete();

        ClientUserCompanion();
    };

    class ClientPlayerInfo
    {
    public:
        uint32_t ObjectID = 0;

        std::string Name;
    };

    class ClientObjectData
    {
    public:
        uint32_t ObjectID = 0;

        int MapIndex = 0;
        Point Location;

        std::string Name;

        // Guild/Group
        MonsterInfo* MonsterInfo = nullptr;
        ItemInfo* ItemInfo = nullptr;

        std::string PetOwner;

        int Health = 0;
        int MaxHealth = 0;

        int Mana = 0;
        int MaxMana = 0;
        Stats Stats;

        bool Dead = false;
    };

    class ClientBlockInfo
    {
    public:
        int Index = 0;
        std::string Name;
    };

    class ClientFortuneInfo
    {
    public:
        int ItemIndex = 0;
        ItemInfo* ItemInfo = nullptr;

        TimeSpan CheckTime;
        long DropCount = 0;
        decimal Progress = decimal(0);

        DateTime CheckDate;

        void OnComplete();
    };
}
