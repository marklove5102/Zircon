#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library::Network
{






namespace Library.Network.ServerPackets
{
    class NewAccount : Packet
    {
        NewAccountResult Result;
};
    class ChangePassword : Packet
    {
        ChangePasswordResult Result;

        std::string Message;
        TimeSpan Duration;
};
    class Login : Packet
    {
        LoginResult Result;

        std::string Message;
        TimeSpan Duration;

        std::vector<SelectInfo> Characters;
        std::vector<ClientUserItem> Items;

        std::vector<ClientBlockInfo> BlockList;

        std::string Address;

        bool TestServer;
};
    class RequestPasswordReset : Packet
    {
        RequestPasswordResetResult Result;
        std::string Message;
        TimeSpan Duration;
};
    class ResetPassword : Packet
    {
        ResetPasswordResult Result;
};
    class Activation : Packet
    {
        ActivationResult Result;
};
    class RequestActivationKey : Packet
    {
        RequestActivationKeyResult Result;
        TimeSpan Duration;
};
    class SelectLogout : Packet
    {
};
    class GameLogout : Packet
    {
        std::vector<SelectInfo> Characters;
};
    class NewCharacter : Packet
    {
        NewCharacterResult Result;

        SelectInfo Character;
};
    class DeleteCharacter : Packet
    {
        DeleteCharacterResult Result;

        int32_t DeletedIndex;
};
    class StartGame : Packet
    {
        StartGameResult Result;

        std::string Message;
        TimeSpan Duration;

        StartInformation StartInformation;
};
    class MapChanged : Packet
    {
        int32_t MapIndex;
        int32_t InstanceIndex;
};
    class UserLocation : Packet
    {
        MirDirection Direction;
        Point Location;
};
    class ObjectRemove : Packet
    {
        uint32_t ObjectID;
};
    class ObjectTurn : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        TimeSpan Slow;
};
    class ObjectHarvest : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        TimeSpan Slow;
};
    class ObjectMount : Packet
    {
        uint32_t ObjectID;
        HorseType Horse;
};
    class ObjectFishing : Packet
    {
        uint32_t ObjectID;
        FishingState State;
        MirDirection Direction;
        Point FloatLocation;
        bool FishFound;
};
    class FishingStats : Packet
    {
        bool CanAutoCast;
        int32_t CurrentPoints;

        int32_t ThrowQuality; //1 time
        int32_t RequiredPoints; //1 time
        int32_t MovementSpeed; //1 time
        int32_t RequiredAccuracy; //1 time
};
    class ObjectMove : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        int32_t Distance;
        TimeSpan Slow;
};
    class ObjectDash : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        int32_t Distance;
        MagicType Magic;
};
    class ObjectPushed : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
};
    class ObjectAttack : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point Location;

        MagicType AttackMagic;
        Element AttackElement;

        uint32_t TargetID;

        TimeSpan Slow;
};
    class ObjectRangeAttack : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point Location;

        MagicType AttackMagic;
        Element AttackElement;

        std::vector<uint32_t> Targets; = new std::vector<uint32_t>();
};
    class ObjectMagic : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point CurrentLocation;

        MagicType Type;
        std::vector<uint32_t> Targets; = new std::vector<uint32_t>();
        std::vector<Point> Locations; = new std::vector<Point>();
        bool Cast;
        Element AttackElement;

        TimeSpan Slow;
};
    class ObjectProjectile : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point CurrentLocation;

        MagicType Type;
        std::vector<uint32_t> Targets; = new std::vector<uint32_t>();
        std::vector<Point> Locations; = new std::vector<Point>();
};

    class ObjectMining : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point Location;

        TimeSpan Slow;
        bool Effect;
};
    class ObjectPetOwnerChanged : Packet
    {
        uint32_t ObjectID;
        std::string PetOwner;
};
    class ObjectShow : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point Location;
};
    class ObjectHide : Packet
    {
        uint32_t ObjectID;

        MirDirection Direction;
        Point Location;
};
    class ObjectEffect : Packet
    {
        uint32_t ObjectID;

        Effect Effect;
};
    class MapEffect : Packet
    {
        Point Location;
        Effect Effect;
        MirDirection Direction;
};
    class ObjectBuffAdd : Packet
    {
        uint32_t ObjectID;
        BuffType Type;
};
    class ObjectBuffRemove : Packet
    {
        uint32_t ObjectID;
        BuffType Type;
};
    class ObjectPoison : Packet
    {
        uint32_t ObjectID;
        PoisonType Poison;
};
    class ObjectPlayer : Packet
    {
        int32_t Index;

        uint32_t ObjectID;
        std::string Name;

        std::string Caption;
        Color NameColour;
        std::string GuildName;

        MirDirection Direction;
        Point Location;

        MirClass Class;
        MirGender Gender;

        int32_t HairType;
        Color HairColour;
        int32_t Weapon;
        int32_t Shield;
        int32_t Armour;
        int32_t Costume;
        Color ArmourColour;
        ExteriorEffect ArmourEffect;
        ExteriorEffect EmblemEffect;
        ExteriorEffect WeaponEffect;
        ExteriorEffect ShieldEffect;

        int32_t Light;

        bool Dead;
        PoisonType Poison;

        std::vector<BuffType> Buffs;

        HorseType Horse;

        int32_t Helmet;

        int32_t HorseShape;

        public std::string FiltersClass;
        public std::string FiltersRarity;
        public std::string FiltersItemType;

        public bool HideHead;
};
    class ObjectMonster : Packet
    {
        uint32_t ObjectID;
        int32_t MonsterIndex;
        std::string CustomName;
        Color NameColour;
        std::string PetOwner;

        MirDirection Direction;
        Point Location;

        bool Dead;
        bool Skeleton;

        PoisonType Poison;

        bool EasterEvent;
        bool HalloweenEvent;
        bool ChristmasEvent;

        std::vector<BuffType> Buffs;
        bool Extra;

        int32_t Extra1;
        Color Colour;

        ClientCompanionObject CompanionObject;
};

    class ObjectNPC : Packet
    {
        uint32_t ObjectID;

        int32_t NPCIndex;
        Point CurrentLocation;

        MirDirection Direction;
};
    class ObjectItem : Packet
    {
        uint32_t ObjectID;

        ClientUserItem Item;

        Point Location;
};
    class ObjectSpell : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        SpellEffect Effect;
        int32_t Power;

};
    class ObjectSpellChanged : Packet
    {
        uint32_t ObjectID;
        int32_t Power;
};
    class ObjectNameColour : Packet
    {
        uint32_t ObjectID;
        Color Colour;
};

    class PlayerUpdate : Packet
    {
        uint32_t ObjectID;
        int32_t Weapon;
        int32_t Shield;
        int32_t Armour;
        int32_t Costume;
        Color ArmourColour;
        ExteriorEffect ArmourEffect;
        ExteriorEffect EmblemEffect;
        ExteriorEffect WeaponEffect;
        ExteriorEffect ShieldEffect;

        int32_t HorseArmour;
        int32_t Helmet;
        int32_t Light;

        bool HideHead;
};


    class MagicToggle : Packet
    {
        MagicType Magic;
        bool CanUse;
};


    class DayChanged : Packet
    {
        float DayTime;
};

    class InformMaxExperience : Packet
    {
        decimal MaxExperience;
};

    class LevelChanged : Packet
    {
        int32_t Level;
        decimal Experience;
        decimal MaxExperience;
};
    class ObjectLeveled : Packet
    {
        uint32_t ObjectID;
};
    class ObjectRevive : Packet
    {
        uint32_t ObjectID;
        Point Location;
        bool Effect;
};
    class GainedExperience : Packet
    {
        decimal Amount;
};

    class NewMagic : Packet
    {
        ClientUserMagic Magic;
};
    class MagicLeveled : Packet
    {
        int32_t InfoIndex;
        public MagicInfo Info;
        int32_t Level;
        int64_t Experience;

        [CompleteObject]
        public void Complete()
        {
            Info = Globals.MagicInfoList.Binding.FirstOrDefault(x => x.Index == InfoIndex);
};
};
    class MagicCooldown : Packet
    {
        int32_t InfoIndex;
        int32_t Delay;
        public MagicInfo Info;

        [CompleteObject]
        public void Complete()
        {
            Info = Globals.MagicInfoList.Binding.FirstOrDefault(x => x.Index == InfoIndex);
};
};

    class StatsUpdate : Packet
    {
        Stats Stats;
        Stats HermitStats;
        int32_t HermitPoints;
};
    class HealthChanged : Packet
    {
        uint32_t ObjectID;
        int32_t Change;
        bool Miss;
        bool Block;
        bool Critical;
};
    class ObjectStats : Packet
    {
        uint32_t ObjectID;
        Stats Stats;
};

    class ManaChanged : Packet
    {
        uint32_t ObjectID;
        int32_t Change;
};

    class FocusChanged : Packet
    {
        uint32_t ObjectID;
        int32_t Change;
};

    class ObjectStruck : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
        uint32_t AttackerID;
        Element Element;
};
    class ObjectDied : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
};
    class ObjectHarvested : Packet
    {
        uint32_t ObjectID;
        MirDirection Direction;
        Point Location;
};



    class ItemsGained : Packet
    {
        std::vector<ClientUserItem> Items;
};
    class ItemMove : Packet
    {
        GridType FromGrid;
        GridType ToGrid;
        int32_t FromSlot;
        int32_t ToSlot;
        bool MergeItem;

        bool Success;
};

    class ItemSort : Packet
    {
        GridType Grid;
        std::vector<ClientUserItem> Items;
        bool Success;
};

    class ItemSplit : Packet
    {
        GridType Grid;
        int32_t Slot;
        int64_t Count;
        int32_t NewSlot;

        bool Success;
};

    class ItemDelete : Packet
    {
        GridType Grid;
        int32_t Slot;
        bool Success;
};

    class ItemLock : Packet
    {
        GridType Grid;
        int32_t Slot;
        bool Locked;

};

    class ItemUseDelay : Packet
    {
        TimeSpan Delay;
};
    class ItemChanged : Packet
    {
        CellLinkInfo Link;
        bool Success;
};

    class ItemStatsChanged : Packet
    {
        GridType GridType;
        int32_t Slot;
        Stats NewStats;
};
    class ItemStatsRefreshed : Packet
    {
        GridType GridType;
        int32_t Slot;
        Stats NewStats;
};
    class ItemDurability : Packet
    {
        GridType GridType;
        int32_t Slot;
        int32_t CurrentDurability;
};
    class ItemExperience : Packet
    {
        CellLinkInfo Target;
        decimal Experience;
        int32_t Level;
        UserItemFlags Flags;
};

    class Chat : Packet
    {
        uint32_t ObjectID;
        std::string Text;
        MessageType Type;
        std::vector<ClientUserItem> LinkedItems;
};

    class NPCResponse : Packet
    {
        uint32_t ObjectID;
        int32_t Index;
        std::vector<ClientNPCValues> Values;

        public NPCPage Page;

        [CompleteObject]
        public void Complete()
        {
            Page = Globals.NPCPageList.Binding.FirstOrDefault(x => x.Index == Index);
};
};
    class ItemsChanged : Packet
    {
        std::vector<CellLinkInfo> Links;
        bool Success;
};
    class NPCRepair : Packet
    {
        std::vector<CellLinkInfo> Links;
        bool Special;
        bool Success;
        TimeSpan SpecialRepairDelay;
};
    class NPCRefinementStone : Packet
    {
        std::vector<CellLinkInfo> IronOres;
        std::vector<CellLinkInfo> SilverOres;
        std::vector<CellLinkInfo> DiamondOres;
        std::vector<CellLinkInfo> GoldOres;
        std::vector<CellLinkInfo> Crystal;
};
    class NPCRefine : Packet
    {
        RefineType RefineType;
        RefineQuality RefineQuality;
        std::vector<CellLinkInfo> Ores;
        std::vector<CellLinkInfo> Items;
        std::vector<CellLinkInfo> Specials;
        bool Success;
};
    class NPCMasterRefine : Packet
    {
        std::vector<CellLinkInfo> Fragment1s;
        std::vector<CellLinkInfo> Fragment2s;
        std::vector<CellLinkInfo> Fragment3s;
        std::vector<CellLinkInfo> Stones;
        std::vector<CellLinkInfo> Specials;

        bool Success;
};
    class NPCClose : Packet
    {
};

    class NPCAccessoryLevelUp : Packet
    {
        CellLinkInfo Target;
        std::vector<CellLinkInfo> Links;
};

    class NPCAccessoryUpgrade : Packet
    {
        CellLinkInfo Target;
        RefineType RefineType;
        bool Success;
};


    class NPCRefineRetrieve : Packet
    {
        int32_t Index;
};
    class RefineList : Packet
    {
        std::vector<ClientRefineInfo> List;
};

    class GroupSwitch : Packet
    {
        bool Allow;
};

    class GroupMember : Packet
    {
        uint32_t ObjectID;
        std::string Name;
};

    class GroupRemove : Packet
    {
        uint32_t ObjectID;
};

    class GroupInvite : Packet
    {
        std::string Name;
};

    class GroupRequest : Packet
    {
        std::string Name;
};

    class GroupLFG : Packet
    {
        std::vector<ClientGroup> List; = new std::vector<ClientGroup>();
};

    class GroupUpdate : Packet
    {
        ClientGroup Group;
};

    class BuffAdd : Packet
    {
        ClientBuffInfo Buff;
};
    class BuffRemove : Packet
    {
        int32_t Index;
};
    class BuffChanged : Packet
    {
        int32_t Index;
        Stats Stats;
};
    class BuffTime : Packet
    {
        int32_t Index;
        TimeSpan Time;
};
    class BuffPaused : Packet
    {
        int32_t Index;
        bool Paused;
};
    class SafeZoneChanged : Packet
    {
        bool InSafeZone;
};
    class CombatTime : Packet
    {

};
    class Inspect : Packet
    {
        std::string Name;
        std::string GuildName;
        std::string GuildRank;
        int32_t GuildFlag; = -1;
        Color GuildColour;
        std::string Partner;
        MirClass Class;
        int32_t Level;
        MirGender Gender;
        //Stats Stats;
        //Stats HermitStats;
        //int32_t HermitPoints;
        std::vector<ClientUserItem> Items;
        int32_t Hair;
        Color HairColour;
        int32_t Fame;

        //int32_t WearWeight;
        //int32_t HandWeight;

        bool Ranking;
};
    class Rankings : Packet
    {
        bool OnlineOnly;
        RequiredClass Class;
        int32_t StartIndex;
        int32_t Total;
        bool AllowObservation;

        std::vector<RankInfo> Ranks;
};
    class RankSearch : Packet
    {
        RankInfo Rank;
};

    class StartObserver : Packet
    {
        StartInformation StartInformation;
        std::vector<ClientUserItem> Items;
};
    class ObservableSwitch : Packet
    {
        bool Allow;
};

    class MarketPlaceHistory : Packet
    {
        int32_t Index;
        int64_t SaleCount;
        int64_t LastPrice;
        int64_t AveragePrice;
        int32_t Display;
};

    class MarketPlaceConsign : Packet
    {
        std::vector<ClientMarketPlaceInfo> Consignments;
};

    class MarketPlaceSearch : Packet
    {
        int32_t Count;
        std::vector<ClientMarketPlaceInfo> Results;
};
    class MarketPlaceSearchCount : Packet
    {
        int32_t Count;
};

    class MarketPlaceSearchIndex : Packet
    {
        int32_t Index;
        ClientMarketPlaceInfo Result;
};

    class MarketPlaceBuy : Packet
    {
        int32_t Index;
        int64_t Count;
        bool Success;
};
    class MarketPlaceStoreBuy : Packet
    {
};

    class MarketPlaceConsignChanged : Packet
    {
        int32_t Index;
        int64_t Count;
};


    class MailList : Packet
    {
        std::vector<ClientMailInfo> Mail;
};
    class MailNew : Packet
    {
        ClientMailInfo Mail;
};
    class MailDelete : Packet
    {
        int32_t Index;
};
    class MailItemDelete : Packet
    {
        int32_t Index;
        int32_t Slot;
};
    class MailSend : Packet
    {
};

    class ChangeAttackMode : Packet
    {
        AttackMode Mode;
};
    class ChangePetMode : Packet
    {
        PetMode Mode;
};

    class CurrencyChanged : Packet
    {
        int32_t CurrencyIndex;
        int64_t Amount;
};

    class MountFailed : Packet
    {
        HorseType Horse;
};

    class WeightUpdate : Packet
    {
        int32_t BagWeight;
        int32_t WearWeight;
        int32_t HandWeight;
};


    class TradeRequest : Packet
    {
        std::string Name;
};
    class TradeOpen : Packet
    {
        std::string Name;
};

    class TradeClose : Packet { }

    class TradeAddItem : Packet
    {
        CellLinkInfo Cell;
        bool Success;
};

    class TradeAddGold : Packet
    {
        int64_t Gold;
};

    class TradeItemAdded : Packet
    {
        ClientUserItem Item;
};

    class TradeGoldAdded : Packet
    {
        int64_t Gold;
};
    class TradeUnlock : Packet { }


    class GuildCreate : Packet
    {

};
    class GuildInfo : Packet
    {
        ClientGuildInfo Guild;
};
    class GuildNoticeChanged : Packet
    {
        std::string Notice;
};
    class GuildNewItem : Packet
    {
        int32_t Slot;
        ClientUserItem Item;
        //int32_t Count;
};
    class GuildGetItem : Packet
    {
        GridType Grid;
        int32_t Slot;
        ClientUserItem Item;
};
    class GuildUpdate : Packet
    {
        int32_t MemberLimit;
        int32_t StorageLimit;

        int64_t GuildFunds;
        int64_t DailyGrowth;

        int32_t GuildLevel;
        int32_t Tax;

        int64_t TotalContribution;
        int64_t DailyContribution;

        std::string DefaultRank;
        GuildPermission DefaultPermission;

        Color Colour;
        int32_t Flag;

        std::vector<ClientGuildMemberInfo> Members;
};
    class GuildKick : Packet
    {
        int32_t Index;
};
    class GuildTax : Packet
    {

};
    class GuildIncreaseMember : Packet
    {

};
    class GuildIncreaseStorage : Packet
    {

};
    class GuildInviteMember : Packet
    {

};
    class GuildInvite : Packet
    {
        std::string Name;
        std::string GuildName;
};
    class GuildStats : Packet
    {
        int32_t Index;
        Stats Stats;

};

    class GuildMemberOffline : Packet
    {
        int32_t Index;
};
    class GuildMemberOnline : Packet
    {
        int32_t Index;

        std::string Name;
        uint32_t ObjectID;
};
    class GuildMemberContribution : Packet
    {
        int32_t Index;

        int64_t Contribution;
};
    class GuildDayReset : Packet
    {

};
    class GuildFundsChanged : Packet
    {
        int64_t Change;
};
    class GuildChanged : Packet
    {
        uint32_t ObjectID;
        std::string GuildName;
        std::string GuildRank;
};

    class GuildWarFinished : Packet
    {
        std::string GuildName;
};

    class GuildWar : Packet
    {
        bool Success;
};

    class GuildWarStarted : Packet
    {
        std::string GuildName;
        TimeSpan Duration;
};
    class GuildConquestDate : Packet
    {
        int32_t Index;
        TimeSpan WarTime;

        public DateTime WarDate;

        [CompleteObject]
        public void Update()
        {
            if (WarTime == TimeSpan.MinValue)
                WarDate = DateTime.MinValue;
            else
                WarDate = Time.Now + WarTime;
};
};
    class GuildCastleInfo : Packet
    {
        int32_t Index;
        std::string Owner;
};

    class GuildConquestStarted : Packet
    {
        int32_t Index;
};

    class GuildConquestFinished : Packet
    {
        int32_t Index;
};

    class ReviveTimers : Packet
    {
        TimeSpan ItemReviveTime;
        TimeSpan ReincarnationPillTime;
};

    class QuestChanged : Packet
    {
        ClientUserQuest Quest;
};

    class QuestCancelled : Packet
    {
        int32_t Index;
};

    class CompanionUnlock : Packet
    {
        int32_t Index;
};
    class CompanionAdopt : Packet
    {
        ClientUserCompanion UserCompanion;
};
    class CompanionRetrieve : Packet
    {
        int32_t Index;
};
    class CompanionStore : Packet
    {
};
    class CompanionWeightUpdate : Packet
    {
        int32_t BagWeight;
        int32_t MaxBagWeight;
        int32_t InventorySize;
};
    class CompanionShapeUpdate : Packet
    {
        uint32_t ObjectID;
        int32_t HeadShape;
        int32_t BackShape;
};
    class CompanionItemsGained : Packet
    {
        std::vector<ClientUserItem> Items;
};
    class CompanionUpdate : Packet
    {
        int32_t Level;
        int32_t Experience;
        int32_t Hunger;
};
    class CompanionSkillUpdate : Packet
    {
        Stats Level3;
        Stats Level5;
        Stats Level7;
        Stats Level10;
        Stats Level11;
        Stats Level13;
        Stats Level15;
};


    class MarriageInvite : Packet
    {
        std::string Name;
};
    class MarriageInfo : Packet
    {
        ClientPlayerInfo Partner;
};
    class MarriageRemoveRing : Packet
    {

};
    class MarriageMakeRing : Packet
    {

};

    class MarriageOnlineChanged : Packet
    {
        uint32_t ObjectID;
};

    class DataObjectRemove : Packet
    {
        uint32_t ObjectID;
};
    class DataObjectPlayer : Packet
    {
        uint32_t ObjectID;
        int32_t MapIndex;
        Point CurrentLocation;

        std::string Name;

        int32_t Health;
        int32_t Mana;
        bool Dead;

        int32_t MaxHealth;
        int32_t MaxMana;
};
    class DataObjectMonster : Packet
    {
        uint32_t ObjectID;

        int32_t MapIndex;
        Point CurrentLocation;

        public MonsterInfo MonsterInfo;
        int32_t MonsterIndex;
        std::string PetOwner;

        int32_t Health;
        Stats Stats;
        bool Dead;

        [CompleteObject]
        public void OnComplete()
        {
            MonsterInfo = Globals.MonsterInfoList.Binding.First(x => x.Index == MonsterIndex);
};
};
    class DataObjectItem : Packet
    {
        uint32_t ObjectID;

        int32_t MapIndex;
        Point CurrentLocation;

        public ItemInfo ItemInfo;
        int32_t ItemIndex;

        [CompleteObject]
        public void OnComplete()
        {
            ItemInfo = Globals.ItemInfoList.Binding.First(x => x.Index == ItemIndex);
};
};
    class DataObjectLocation : Packet
    {
        uint32_t ObjectID;
        int32_t MapIndex;
        Point CurrentLocation;
};
    class DataObjectHealthMana : Packet
    {
        uint32_t ObjectID;

        int32_t Health;
        int32_t Mana;
        bool Dead;
};
    class DataObjectMaxHealthMana : Packet
    {
        uint32_t ObjectID;

        int32_t MaxHealth;
        int32_t MaxMana;
        Stats Stats;
};
    class BlockAdd : Packet
    {
        ClientBlockInfo Info;
};

    class BlockRemove : Packet
    {
        int32_t Index;
};

    class HelmetToggle : Packet
    {
        bool HideHelmet;
};

    class StorageSize : Packet
    {
        int32_t Size;
};

    class PlayerChangeUpdate : Packet
    {

        uint32_t ObjectID;
        std::string Name;
        std::string Caption;
        MirGender Gender;
        int32_t HairType;

        Color HairColour;
        Color ArmourColour;

};

    class FortuneUpdate : Packet
    {
        std::vector<ClientFortuneInfo> Fortunes;

};
    class NPCWeaponCraft : Packet
    {
        CellLinkInfo Template;
        CellLinkInfo Yellow;
        CellLinkInfo Blue;
        CellLinkInfo Red;
        CellLinkInfo Purple;
        CellLinkInfo Green;
        CellLinkInfo Grey;

        bool Success;
};

    class NPCAccessoryRefine : Packet
    {
        CellLinkInfo Target;
        CellLinkInfo OreTarget;
        std::vector<CellLinkInfo> Links;
        RefineType RefineType;
        bool Success;
};

    class ItemAcessoryRefined : Packet
    {
        GridType GridType;
        int32_t Slot;
        Stats NewStats;
};

    class RequestInstance : Packet
    {
        int32_t Index;
        InstanceResult Result;
        bool Success;
};

    class JoinInstance : Packet
    {
        InstanceResult Result;
        bool Success;
};

    class SendCompanionFilters : Packet
    {
        std::vector<MirClass> FilterClass;
        std::vector<Rarity> FilterRarity;
        std::vector<ItemType> FilterItemType;
};

    class FriendUpdate : Packet
    {
        ClientFriendInfo Info;
};

    class FriendAdd : Packet
    {
        ClientFriendInfo Info;
};
    class FriendRemove : Packet
    {
        int32_t Index;
};

    class DisciplineUpdate : Packet
    {
        ClientUserDiscipline Discipline;
};

    class DisciplineExperienceChanged : Packet
    {
        int64_t Experience;
};

    class NPCRoll : Packet
    {
        int32_t Type;
        int32_t Result;
};

    class SetTimer : Packet
    {
        std::string Key;
        uint8_t Type;
        int32_t Seconds;
};
};


}
