#pragma once

#include "Packet.h"
#include "../Enum.h"
#include <string>
#include <vector>
#include <cstdint>

namespace Library::Network::ClientPackets
{

class NewAccount : public Packet
{
public:
    std::string EMailAddress;
    std::string Password;
    DateTime BirthDate;
    std::string RealName;
    std::string Referral;
    std::string CheckSum;
};

class ChangePassword : public Packet
{
public:
    std::string EMailAddress;
    std::string CurrentPassword;
    std::string NewPassword;
    std::string CheckSum;
};

class RequestPasswordReset : public Packet
{
public:
    std::string EMailAddress;
    std::string CheckSum;
};

class ResetPassword : public Packet
{
public:
    std::string ResetKey;
    std::string NewPassword;
    std::string CheckSum;
};

class Activation : public Packet
{
public:
    std::string ActivationKey;
    std::string CheckSum;
};

class RequestActivationKey : public Packet
{
public:
    std::string EMailAddress;
    std::string CheckSum;
};

class SelectLanguage : public Packet
{
public:
    std::string Language;
};

class Login : public Packet
{
public:
    std::string EMailAddress;
    std::string Password;
    std::string CheckSum;
};

class Logout : public Packet
{
};

class NewCharacter : public Packet
{
public:
    std::string CharacterName;
    MirClass Class;
    MirGender Gender;
    int HairType;
    Color HairColour;
    Color ArmourColour;
    std::string CheckSum;
};

class DeleteCharacter : public Packet
{
public:
    int CharacterIndex;
    std::string CheckSum;
};

class StartGame : public Packet
{
public:
    int CharacterIndex;
};

class TownRevive : public Packet
{
};

class Turn : public Packet
{
public:
    MirDirection Direction;
};

class Harvest : public Packet
{
public:
    MirDirection Direction;
};

class Move : public Packet
{
public:
    MirDirection Direction;
    int Distance;
};

class Mount : public Packet
{
};

class Attack : public Packet
{
public:
    MirDirection Direction;
    MirAction Action;
    MagicType AttackMagic;
};

class Mining : public Packet
{
public:
    MirDirection Direction;
};

class Magic : public Packet
{
public:
    MirDirection Direction;
    MirAction Action;
    MagicType Type;
    uint32_t Target;
    Point Location;
};

class ItemMove : public Packet
{
public:
    GridType FromGrid;
    GridType ToGrid;
    int FromSlot;
    int ToSlot;
    bool MergeItem;
};

class ItemSplit : public Packet
{
public:
    GridType Grid;
    int Slot;
    int64_t Count;
};

class ItemDrop : public Packet
{
public:
    CellLinkInfo Link;
};

class GoldDrop : public Packet
{
public:
    int64_t Amount;
};

class ItemUse : public Packet
{
public:
    CellLinkInfo Link;
};

class ItemLock : public Packet
{
public:
    GridType GridType;
    int SlotIndex;
    bool Locked;
};

class BeltLinkChanged : public Packet
{
public:
    int Slot;
    int LinkIndex;
    int LinkItemIndex;
};

class AutoPotionLinkChanged : public Packet
{
public:
    int Slot;
    int LinkIndex;
    int Health;
    int Mana;
    bool Enabled;
};

class PickUp : public Packet
{
};

class Chat : public Packet
{
public:
    std::string Text;
};

class NPCCall : public Packet
{
public:
    uint32_t ObjectID;
};

class NPCButton : public Packet
{
public:
    int ButtonID;
};

class NPCBuy : public Packet
{
public:
    int Index;
    int64_t Amount;
    bool GuildFunds;
};

class NPCSell : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
};

class NPCFragment : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
};

class NPCRepair : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
    bool Special;
    bool GuildFunds;
};

class NPCRefine : public Packet
{
public:
    RefineType RefineType;
    RefineQuality RefineQuality;
    std::vector<CellLinkInfo> Ores;
    std::vector<CellLinkInfo> Items;
    std::vector<CellLinkInfo> Specials;
};

class NPCMasterRefine : public Packet
{
public:
    RefineType RefineType;
    std::vector<CellLinkInfo> Fragment1s;
    std::vector<CellLinkInfo> Fragment2s;
    std::vector<CellLinkInfo> Fragment3s;
    std::vector<CellLinkInfo> Stones;
    std::vector<CellLinkInfo> Specials;
};

class NPCMasterRefineEvaluate : public Packet
{
public:
    RefineType RefineType;
    std::vector<CellLinkInfo> Fragment1s;
    std::vector<CellLinkInfo> Fragment2s;
    std::vector<CellLinkInfo> Fragment3s;
    std::vector<CellLinkInfo> Stones;
    std::vector<CellLinkInfo> Specials;
};

class NPCRefinementStone : public Packet
{
public:
    std::vector<CellLinkInfo> IronOres;
    std::vector<CellLinkInfo> SilverOres;
    std::vector<CellLinkInfo> DiamondOres;
    std::vector<CellLinkInfo> GoldOres;
    std::vector<CellLinkInfo> Crystal;
    int64_t Gold;
};

class NPCClose : public Packet
{
};

class NPCRefineRetrieve : public Packet
{
public:
    int Index;
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
};

class MagicKey : public Packet
{
public:
    MagicType Magic;
    SpellKey Set1Key;
    SpellKey Set2Key;
    SpellKey Set3Key;
    SpellKey Set4Key;
};

class MagicToggle : public Packet
{
public:
    MagicType Magic;
    bool CanUse;
};

class GroupSwitch : public Packet
{
public:
    bool Allow;
};

class GroupInvite : public Packet
{
public:
    std::string Name;
};

class GroupRemove : public Packet
{
public:
    std::string Name;
};

class GroupResponse : public Packet
{
public:
    bool Accept;
};

class Inspect : public Packet
{
public:
    int Index;
};

class RankRequest : public Packet
{
public:
    RequiredClass Class;
    bool OnlineOnly;
    int StartIndex;
};

class ObserverRequest : public Packet
{
public:
    std::string Name;
};

class ObservableSwitch : public Packet
{
public:
    bool Allow;
};

class Hermit : public Packet
{
public:
    Stat Stat;
};

class MarketPlaceHistory : public Packet
{
public:
    int Index;
    int Display;
    int PartIndex;
};

class MarketPlaceConsign : public Packet
{
public:
    CellLinkInfo Link;
    int Price;
    std::string Message;
    bool GuildFunds;
};

class MarketPlaceSearch : public Packet
{
public:
    std::string Name;
    bool ItemTypeFilter;
    ItemType ItemType;
    MarketPlaceSort Sort;
};

class MarketPlaceSearchIndex : public Packet
{
public:
    int Index;
};

class MarketPlaceCancelConsign : public Packet
{
public:
    int Index;
    int64_t Count;
};

class MarketPlaceBuy : public Packet
{
public:
    int64_t Index;
    int64_t Count;
    bool GuildFunds;
};

class MarketPlaceStoreBuy : public Packet
{
public:
    int Index;
    int64_t Count;
    bool UseHuntGold;
};

class MailOpened : public Packet
{
public:
    int Index;
};

class MailGetItem : public Packet
{
public:
    int Index;
    int Slot;
};

class MailDelete : public Packet
{
public:
    int Index;
};

class MailSend : public Packet
{
public:
    std::vector<CellLinkInfo> Links;
    std::string Recipient;
    std::string Subject;
    std::string Message;
    int64_t Gold;
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

class GameGoldRecharge : public Packet
{
};

class TradeRequest : public Packet
{
};

class TradeRequestResponse : public Packet
{
public:
    bool Accept;
};

class TradeClose : public Packet
{
};

class TradeAddGold : public Packet
{
public:
    int64_t Gold;
};

class TradeAddItem : public Packet
{
public:
    CellLinkInfo Cell;
};

class TradeConfirm : public Packet
{
};

class GuildCreate : public Packet
{
public:
    std::string Name;
    bool UseGold;
    int Members;
    int Storage;
};

class GuildEditNotice : public Packet
{
public:
    std::string Notice;
};

class GuildEditMember : public Packet
{
public:
    int Index;
    std::string Rank;
    GuildPermission Permission;
};

class GuildInviteMember : public Packet
{
public:
    std::string Name;
};

class GuildKickMember : public Packet
{
public:
    int Index;
};

class GuildTax : public Packet
{
public:
    int64_t Tax;
};

class GuildIncreaseMember : public Packet
{
};

class GuildIncreaseStorage : public Packet
{
};

class GuildResponse : public Packet
{
public:
    bool Accept;
};

class GuildWar : public Packet
{
public:
    std::string GuildName;
};

class GuildRequestConquest : public Packet
{
public:
    int Index;
};

class QuestAccept : public Packet
{
public:
    int Index;
};

class QuestComplete : public Packet
{
public:
    int Index;
    int ChoiceIndex;
};

class QuestTrack : public Packet
{
public:
    int Index;
    bool Track;
};

class CompanionUnlock : public Packet
{
public:
    int Index;
};

class CompanionAdopt : public Packet
{
public:
    int Index;
    std::string Name;
};

class CompanionRetrieve : public Packet
{
public:
    int Index;
};

class CompanionStore : public Packet
{
public:
    int Index;
};

class MarriageResponse : public Packet
{
public:
    bool Accept;
};

class MarriageMakeRing : public Packet
{
public:
    int Slot;
};

class MarriageTeleport : public Packet
{
};

class BlockAdd : public Packet
{
public:
    std::string Name;
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

class GenderChange : public Packet
{
public:
    MirGender Gender;
    int HairType;
    Color HairColour;
};

class HairChange : public Packet
{
public:
    int HairType;
    Color HairColour;
};

class ArmourDye : public Packet
{
public:
    Color ArmourColour;
};

class NameChange : public Packet
{
public:
    std::string Name;
};

class FortuneCheck : public Packet
{
public:
    int ItemIndex;
};

class TeleportRing : public Packet
{
public:
    Point Location;
    int Index;
};

class JoinStarterGuild : public Packet
{
};

class NPCAccessoryReset : public Packet
{
public:
    CellLinkInfo Cell;
};

class NPCWeaponCraft : public Packet
{
public:
    RequiredClass Class;
    CellLinkInfo Template;
    CellLinkInfo Yellow;
    CellLinkInfo Blue;
    CellLinkInfo Red;
    CellLinkInfo Purple;
    CellLinkInfo Green;
    CellLinkInfo Grey;
};

class NPCAccessoryRefine : public Packet
{
public:
    CellLinkInfo Target;
    CellLinkInfo OreTarget;
    std::vector<CellLinkInfo> Links;
    RefineType RefineType;
};

} // namespace Library::Network::ClientPackets
