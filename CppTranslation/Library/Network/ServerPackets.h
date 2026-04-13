#pragma once

#include "Packet.h"
#include "../Enum.h"
#include "../Stat.h"
#include <string>
#include <vector>
#include <cstdint>

namespace Library::Network::ServerPackets
{

class NewAccount : public Packet
{
public:
    NewAccountResult Result;
};

class ChangePassword : public Packet
{
public:
    ChangePasswordResult Result;
    std::string Message;
    TimeSpan Duration;
};

class Login : public Packet
{
public:
    LoginResult Result;
    std::string Message;
    TimeSpan Duration;
    std::vector<SelectInfo> Characters;
    std::vector<ClientUserItem> Items;
    std::vector<ClientBlockInfo> BlockList;
    std::string Address;
    bool TestServer;
};

class RequestPasswordReset : public Packet
{
public:
    RequestPasswordResetResult Result;
    std::string Message;
    TimeSpan Duration;
};

class ResetPassword : public Packet
{
public:
    ResetPasswordResult Result;
};

class Activation : public Packet
{
public:
    ActivationResult Result;
};

class RequestActivationKey : public Packet
{
public:
    RequestActivationKeyResult Result;
    TimeSpan Duration;
};

class SelectLogout : public Packet
{
};

class GameLogout : public Packet
{
public:
    std::vector<SelectInfo> Characters;
};

class NewCharacter : public Packet
{
public:
    NewCharacterResult Result;
    SelectInfo Character;
};

class DeleteCharacter : public Packet
{
public:
    DeleteCharacterResult Result;
    int DeletedIndex;
};

class StartGame : public Packet
{
public:
    StartGameResult Result;
    std::string Message;
    TimeSpan Duration;
    StartInformation StartInformation;
};

class MapChanged : public Packet
{
public:
    int MapIndex;
};

class UserLocation : public Packet
{
public:
    MirDirection Direction;
    Point Location;
};

class ObjectRemove : public Packet
{
public:
    uint32_t ObjectID;
};

class ObjectTurn : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    TimeSpan Slow;
};

class ObjectHarvest : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    TimeSpan Slow;
};

class ObjectMount : public Packet
{
public:
    uint32_t ObjectID;
    HorseType Horse;
};

class ObjectMove : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    int Distance;
    TimeSpan Slow;
};

class ObjectDash : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    int Distance;
    MagicType Magic;
};

class ObjectPushed : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
};

class ObjectAttack : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    MagicType AttackMagic;
    Element AttackElement;
    uint32_t TargetID;
    TimeSpan Slow;
};

class ObjectRangeAttack : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    MagicType AttackMagic;
    Element AttackElement;
    std::vector<uint32_t> Targets;
};

class ObjectMagic : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point CurrentLocation;
    MagicType Type;
    std::vector<uint32_t> Targets;
    std::vector<Point> Locations;
    bool Cast;
    TimeSpan Slow;
};

class ObjectMining : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    TimeSpan Slow;
    bool Effect;
};

class ObjectPetOwnerChanged : public Packet
{
public:
    uint32_t ObjectID;
    std::string PetOwner;
};

class ObjectShow : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
};

class ObjectHide : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
};

class ObjectEffect : public Packet
{
public:
    uint32_t ObjectID;
    Effect Effect;
};

class MapEffect : public Packet
{
public:
    Point Location;
    Effect Effect;
    MirDirection Direction;
};

class ObjectBuffAdd : public Packet
{
public:
    uint32_t ObjectID;
    BuffType Type;
};

class ObjectBuffRemove : public Packet
{
public:
    uint32_t ObjectID;
    BuffType Type;
};

class ObjectPoison : public Packet
{
public:
    uint32_t ObjectID;
    PoisonType Poison;
};

class ObjectPlayer : public Packet
{
public:
    int Index;
    uint32_t ObjectID;
    std::string Name;
    Color NameColour;
    std::string GuildName;
    MirDirection Direction;
    Point Location;
    MirClass Class;
    MirGender Gender;
    int HairType;
    Color HairColour;
    int Weapon;
    int Shield;
    int Armour;
    Color ArmourColour;
    int ArmourImage;
    int EmblemShape;
    int Wings;
    int Light;
    bool Dead;
    PoisonType Poison;
    std::vector<BuffType> Buffs;
    HorseType Horse;
    int Helmet;
    int HorseShape;
};

class ObjectMonster : public Packet
{
public:
    uint32_t ObjectID;
    int MonsterIndex;
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
    ClientCompanionObject CompanionObject;
};

class ObjectNPC : public Packet
{
public:
    uint32_t ObjectID;
    int NPCIndex;
    Point CurrentLocation;
    MirDirection Direction;
};

class ObjectItem : public Packet
{
public:
    uint32_t ObjectID;
    ClientUserItem Item;
    Point Location;
};

class ObjectSpell : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    SpellEffect Effect;
    int Power;
};

class ObjectSpellChanged : public Packet
{
public:
    uint32_t ObjectID;
    int Power;
};

class ObjectNameColour : public Packet
{
public:
    uint32_t ObjectID;
    Color Colour;
};

class PlayerUpdate : public Packet
{
public:
    uint32_t ObjectID;
    int Weapon;
    int Shield;
    int Armour;
    Color ArmourColour;
    int ArmourImage;
    int EmblemShape;
    int HorseArmour;
    int Helmet;
    int WingsShape;
    int Light;
};

class MagicToggle : public Packet
{
public:
    MagicType Magic;
    bool CanUse;
};

class DayChanged : public Packet
{
public:
    float DayTime;
};

class InformMaxExperience : public Packet
{
public:
    double MaxExperience;
};

class LevelChanged : public Packet
{
public:
    int Level;
    double Experience;
    double MaxExperience;
};

class ObjectLeveled : public Packet
{
public:
    uint32_t ObjectID;
};

class ObjectRevive : public Packet
{
public:
    uint32_t ObjectID;
    Point Location;
    bool Effect;
};

class GainedExperience : public Packet
{
public:
    double Amount;
};

class NewMagic : public Packet
{
public:
    ClientUserMagic Magic;
};

class MagicLeveled : public Packet
{
public:
    int InfoIndex;
    MagicInfo* Info;
    int Level;
    int64_t Experience;
};

class MagicCooldown : public Packet
{
public:
    int InfoIndex;
    int Delay;
    MagicInfo* Info;
};

class StatsUpdate : public Packet
{
public:
    Stats Stats;
    Stats HermitStats;
    int HermitPoints;
};

class HealthChanged : public Packet
{
public:
    uint32_t ObjectID;
    int Change;
    bool Miss;
    bool Block;
    bool Critical;
};

class ObjectStats : public Packet
{
public:
    uint32_t ObjectID;
    Stats Stats;
};

class ManaChanged : public Packet
{
public:
    uint32_t ObjectID;
    int Change;
};

class ObjectStruck : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
    uint32_t AttackerID;
    Element Element;
};

class ObjectDied : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
};

class ObjectHarvested : public Packet
{
public:
    uint32_t ObjectID;
    MirDirection Direction;
    Point Location;
};

class ItemsGained : public Packet
{
public:
    std::vector<ClientUserItem> Items;
};

class ItemMove : public Packet
{
public:
    GridType FromGrid;
    GridType ToGrid;
    int FromSlot;
    int ToSlot;
    bool MergeItem;
    bool Success;
};

class ItemSplit : public Packet
{
public:
    GridType Grid;
    int Slot;
    int64_t Count;
    int NewSlot;
    bool Success;
};

class ItemLock : public Packet
{
public:
    GridType Grid;
    int Slot;
    bool Locked;
};

class ItemUseDelay : public Packet
{
public:
    TimeSpan Delay;
};

class ItemChanged : public Packet
{
public:
    CellLinkInfo Link;
    bool Success;
};

class ItemStatsChanged : public Packet
{
public:
    GridType GridType;
    int Slot;
    Stats NewStats;
};

class ItemStatsRefreshed : public Packet
{
public:
    GridType GridType;
    int Slot;
    Stats NewStats;
};

class ItemDurability : public Packet
{
public:
    GridType GridType;
    int Slot;
    int CurrentDurability;
};

class GoldChanged : public Packet
{
public:
    int64_t Gold;
};

class ItemExperience : public Packet
{
public:
    CellLinkInfo Target;
    double Experience;
    int Level;
    UserItemFlags Flags;
};

class Chat : public Packet
{
public:
    uint32_t ObjectID;
    std::string Text;
    MessageType Type;
    std::vector<ClientUserItem> Items;
};

class NPCResponse : public Packet
{
public:
    uint32_t ObjectID;
    int Index;
    std::vector<ClientRefineInfo> Extra;
    NPCPage* Page;
};

class ItemsChanged : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
    bool Success;
};

class NPCRepair : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
    bool Special;
    bool Success;
    TimeSpan SpecialRepairDelay;
};

class NPCRefinementStone : public Packet
{
public:
    std::vector<CellLinkInfo> IronOres;
    std::vector<CellLinkInfo> SilverOres;
    std::vector<CellLinkInfo> DiamondOres;
    std::vector<CellLinkInfo> GoldOres;
    std::vector<CellLinkInfo> Crystal;
};

class NPCRefine : public Packet
{
public:
    RefineType RefineType;
    RefineQuality RefineQuality;
    std::vector<CellLinkInfo> Ores;
    std::vector<CellLinkInfo> Items;
    std::vector<CellLinkInfo> Specials;
    bool Success;
};

class NPCMasterRefine : public Packet
{
public:
    std::vector<CellLinkInfo> Fragment1s;
    std::vector<CellLinkInfo> Fragment2s;
    std::vector<CellLinkInfo> Fragment3s;
    std::vector<CellLinkInfo> Stones;
    std::vector<CellLinkInfo> Specials;
    bool Success;
};

class NPCClose : public Packet
{
};

class NPCAccessoryLevelUp : public Packet
{
public:
    CellLinkInfo Target;
    std::vector<CellLinkInfo> Links;
};

class NPCAccessoryUpgrade : public Packet
{
public:
    CellLinkInfo Target;
    RefineType RefineType;
    bool Success;
};

class NPCRefineRetrieve : public Packet
{
public:
    int Index;
};

class RefineList : public Packet
{
public:
    std::vector<ClientRefineInfo> List;
};

class GroupSwitch : public Packet
{
public:
    bool Allow;
};

class GroupMember : public Packet
{
public:
    uint32_t ObjectID;
    std::string Name;
};

class GroupRemove : public Packet
{
public:
    uint32_t ObjectID;
};

class GroupInvite : public Packet
{
public:
    std::string Name;
};

class BuffAdd : public Packet
{
public:
    ClientBuffInfo Buff;
};

class BuffRemove : public Packet
{
public:
    int Index;
};

class BuffChanged : public Packet
{
public:
    int Index;
    Stats Stats;
};

class BuffTime : public Packet
{
public:
    int Index;
    TimeSpan Time;
};

class BuffPaused : public Packet
{
public:
    int Index;
    bool Paused;
};

class SafeZoneChanged : public Packet
{
public:
    bool InSafeZone;
};

class CombatTime : public Packet
{
};

class Inspect : public Packet
{
public:
    std::string Name;
    std::string GuildName;
    std::string GuildRank;
    std::string Partner;
    MirClass Class;
    int Level;
    MirGender Gender;
    Stats Stats;
    Stats HermitStats;
    int HermitPoints;
    std::vector<ClientUserItem> Items;
    int Hair;
    Color HairColour;
    int WearWeight;
    int HandWeight;
};

class Rankings : public Packet
{
public:
    bool OnlineOnly;
    RequiredClass Class;
    int StartIndex;
    int Total;
    std::vector<RankInfo> Ranks;
};

class StartObserver : public Packet
{
public:
    StartInformation StartInformation;
    std::vector<ClientUserItem> Items;
};

class ObservableSwitch : public Packet
{
public:
    bool Allow;
};

class MarketPlaceHistory : public Packet
{
public:
    int Index;
    int64_t SaleCount;
    int64_t LastPrice;
    int64_t AveragePrice;
    int Display;
};

class MarketPlaceConsign : public Packet
{
public:
    std::vector<ClientMarketPlaceInfo> Consignments;
};

class MarketPlaceSearch : public Packet
{
public:
    int Count;
    std::vector<ClientMarketPlaceInfo> Results;
};

class MarketPlaceSearchCount : public Packet
{
public:
    int Count;
};

class MarketPlaceSearchIndex : public Packet
{
public:
    int Index;
    ClientMarketPlaceInfo Result;
};

class MarketPlaceBuy : public Packet
{
public:
    int Index;
    int64_t Count;
    bool Success;
};

class MarketPlaceStoreBuy : public Packet
{
};

class MarketPlaceConsignChanged : public Packet
{
public:
    int Index;
    int64_t Count;
};

class MailList : public Packet
{
public:
    std::vector<ClientMailInfo> Mail;
};

class MailNew : public Packet
{
public:
    ClientMailInfo Mail;
};

class MailDelete : public Packet
{
public:
    int Index;
};

class MailItemDelete : public Packet
{
public:
    int Index;
    int Slot;
};

class MailSend : public Packet
{
};

class ChangeAttackMode : public Packet
{
public:
    AttackMode Mode;
};

class ChangePetMode : public Packet
{
public:
    PetMode Mode;
};

class GameGoldChanged : public Packet
{
public:
    int GameGold;
};

class MountFailed : public Packet
{
public:
    HorseType Horse;
};

class WeightUpdate : public Packet
{
public:
    int BagWeight;
    int WearWeight;
    int HandWeight;
};

class HuntGoldChanged : public Packet
{
public:
    int HuntGold;
};

class TradeRequest : public Packet
{
public:
    std::string Name;
};

class TradeOpen : public Packet
{
public:
    std::string Name;
};

class TradeClose : public Packet
{
};

class TradeAddItem : public Packet
{
public:
    CellLinkInfo Cell;
    bool Success;
};

class TradeAddGold : public Packet
{
public:
    int64_t Gold;
};

class TradeItemAdded : public Packet
{
public:
    ClientUserItem Item;
};

class TradeGoldAdded : public Packet
{
public:
    int64_t Gold;
};

class TradeUnlock : public Packet
{
};

class GuildCreate : public Packet
{
};

class GuildInfo : public Packet
{
public:
    ClientGuildInfo Guild;
};

class GuildNoticeChanged : public Packet
{
public:
    std::string Notice;
};

class GuildNewItem : public Packet
{
public:
    int Slot;
    ClientUserItem Item;
};

class GuildGetItem : public Packet
{
public:
    GridType Grid;
    int Slot;
    ClientUserItem Item;
};

class GuildUpdate : public Packet
{
public:
    int MemberLimit;
    int StorageLimit;
    int64_t GuildFunds;
    int64_t DailyGrowth;
    int GuildLevel;
    int Tax;
    int64_t TotalContribution;
    int64_t DailyContribution;
    std::string DefaultRank;
    GuildPermission DefaultPermission;
    std::vector<ClientGuildMemberInfo> Members;
};

class GuildKick : public Packet
{
public:
    int Index;
};

class GuildTax : public Packet
{
};

class GuildIncreaseMember : public Packet
{
};

class GuildIncreaseStorage : public Packet
{
};

class GuildInviteMember : public Packet
{
};

class GuildInvite : public Packet
{
public:
    std::string Name;
    std::string GuildName;
};

class GuildStats : public Packet
{
public:
    int Index;
    Stats Stats;
};

class GuildMemberOffline : public Packet
{
public:
    int Index;
};

class GuildMemberOnline : public Packet
{
public:
    int Index;
    std::string Name;
    uint32_t ObjectID;
};

class GuildMemberContribution : public Packet
{
public:
    int Index;
    int64_t Contribution;
};

class GuildDayReset : public Packet
{
};

class GuildFundsChanged : public Packet
{
public:
    int64_t Change;
};

class GuildChanged : public Packet
{
public:
    uint32_t ObjectID;
    std::string GuildName;
    std::string GuildRank;
};

class GuildWarFinished : public Packet
{
public:
    std::string GuildName;
};

class GuildWar : public Packet
{
public:
    bool Success;
};

class GuildWarStarted : public Packet
{
public:
    std::string GuildName;
    TimeSpan Duration;
};

class GuildConquestDate : public Packet
{
public:
    int Index;
    TimeSpan WarTime;
    DateTime WarDate;
};

class GuildCastleInfo : public Packet
{
public:
    int Index;
    std::string Owner;
};

class GuildConquestStarted : public Packet
{
public:
    int Index;
};

class GuildConquestFinished : public Packet
{
public:
    int Index;
};

class ReviveTimers : public Packet
{
public:
    TimeSpan ItemReviveTime;
    TimeSpan ReincarnationPillTime;
};

class QuestChanged : public Packet
{
public:
    ClientUserQuest Quest;
};

class CompanionUnlock : public Packet
{
public:
    int Index;
};

class CompanionAdopt : public Packet
{
public:
    ClientUserCompanion UserCompanion;
};

class CompanionRetrieve : public Packet
{
public:
    int Index;
};

class CompanionStore : public Packet
{
};

class CompanionWeightUpdate : public Packet
{
public:
    int BagWeight;
    int MaxBagWeight;
    int InventorySize;
};

class CompanionShapeUpdate : public Packet
{
public:
    uint32_t ObjectID;
    int HeadShape;
    int BackShape;
};

class CompanionItemsGained : public Packet
{
public:
    std::vector<ClientUserItem> Items;
};

class CompanionUpdate : public Packet
{
public:
    int Level;
    int Experience;
    int Hunger;
};

class CompanionSkillUpdate : public Packet
{
public:
    Stats Level3;
    Stats Level5;
    Stats Level7;
    Stats Level10;
    Stats Level11;
    Stats Level13;
    Stats Level15;
};

class MarriageInvite : public Packet
{
public:
    std::string Name;
};

class MarriageInfo : public Packet
{
public:
    ClientPlayerInfo Partner;
};

class MarriageRemoveRing : public Packet
{
};

class MarriageMakeRing : public Packet
{
};

class MarriageOnlineChanged : public Packet
{
public:
    uint32_t ObjectID;
};

class DataObjectRemove : public Packet
{
public:
    uint32_t ObjectID;
};

class DataObjectPlayer : public Packet
{
public:
    uint32_t ObjectID;
    int MapIndex;
    Point CurrentLocation;
    std::string Name;
    int Health;
    int Mana;
    bool Dead;
    int MaxHealth;
    int MaxMana;
};

class DataObjectMonster : public Packet
{
public:
    uint32_t ObjectID;
    int MapIndex;
    Point CurrentLocation;
    MonsterInfo* MonsterInfo;
    int MonsterIndex;
    std::string PetOwner;
    int Health;
    Stats Stats;
    bool Dead;
};

class DataObjectItem : public Packet
{
public:
    uint32_t ObjectID;
    int MapIndex;
    Point CurrentLocation;
    ItemInfo* ItemInfo;
    int ItemIndex;
};

class DataObjectLocation : public Packet
{
public:
    uint32_t ObjectID;
    int MapIndex;
    Point CurrentLocation;
};

class DataObjectHealthMana : public Packet
{
public:
    uint32_t ObjectID;
    int Health;
    int Mana;
    bool Dead;
};

class DataObjectMaxHealthMana : public Packet
{
public:
    uint32_t ObjectID;
    int MaxHealth;
    int MaxMana;
    Stats Stats;
};

class BlockAdd : public Packet
{
public:
    ClientBlockInfo Info;
};

class BlockRemove : public Packet
{
public:
    int Index;
};

class HelmetToggle : public Packet
{
public:
    bool HideHelmet;
};

class StorageSize : public Packet
{
public:
    int Size;
};

class PlayerChangeUpdate : public Packet
{
public:
    uint32_t ObjectID;
    std::string Name;
    MirGender Gender;
    int HairType;
    Color HairColour;
    Color ArmourColour;
};

class FortuneUpdate : public Packet
{
public:
    std::vector<ClientFortuneInfo> Fortunes;
};

class NPCWeaponCraft : public Packet
{
public:
    CellLinkInfo Template;
    CellLinkInfo Yellow;
    CellLinkInfo Blue;
    CellLinkInfo Red;
    CellLinkInfo Purple;
    CellLinkInfo Green;
    CellLinkInfo Grey;
    bool Success;
};

class NPCAccessoryRefine : public Packet
{
public:
    CellLinkInfo Target;
    CellLinkInfo OreTarget;
    std::vector<CellLinkInfo> Links;
    RefineType RefineType;
    bool Success;
};

class ItemAcessoryRefined : public Packet
{
public:
    GridType GridType;
    int Slot;
    Stats NewStats;
};

} // namespace Library::Network::ServerPackets
