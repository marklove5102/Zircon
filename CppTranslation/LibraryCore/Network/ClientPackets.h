#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include <memory>

namespace Library::Network
{







namespace Library.Network.ClientPackets
{
    class NewAccount : Packet
    {
        std::string EMailAddress;
        std::string Password;
        DateTime BirthDate;
        std::string RealName;
        std::string Referral;
        std::string CheckSum;
};

    class ChangePassword : Packet
    {
        std::string EMailAddress;
        std::string CurrentPassword;
        std::string NewPassword;
        std::string CheckSum;
};

    class RequestPasswordReset : Packet
    {
        std::string EMailAddress;
        std::string CheckSum;
};

    class ResetPassword : Packet
    {
        std::string ResetKey;
        std::string NewPassword;
        std::string CheckSum;
};

    class Activation : Packet
    {
        std::string ActivationKey;
        std::string CheckSum;
};

    class RequestActivationKey : Packet
    {
        std::string EMailAddress;
        std::string CheckSum;
};

    class SelectLanguage : Packet
    {
        std::string Language;
};

    class Login : Packet
    {
        std::string EMailAddress;
        std::string Password;
        std::string CheckSum;
};

    class Logout : Packet {}


    class NewCharacter : Packet
    {
        std::string CharacterName;
        MirClass Class;
        MirGender Gender;
        int32_t HairType;
        Color HairColour;
        Color ArmourColour;
        std::string CheckSum;
};

    class DeleteCharacter : Packet
    {
        int32_t CharacterIndex;
        std::string CheckSum;
};

    class StartGame : Packet
    {
        int32_t CharacterIndex;
};

    class TownRevive : Packet {}

    class Turn : Packet
    {
        MirDirection Direction;
};

    class Harvest : Packet
    {
        MirDirection Direction;
};

    class Move : Packet
    {
        MirDirection Direction;
        int32_t Distance;
};

    class Mount : Packet {}

    class FishingCast : Packet 
    { 
        FishingState State;
        MirDirection Direction;
        Point FloatLocation;
        bool CaughtFish;
};

    class Attack : Packet
    {
        MirDirection Direction;
        MirAction Action;
        MagicType AttackMagic;
};

    class RangeAttack : Packet
    {
        MirDirection Direction;
        uint32_t Target;
        int32_t DelayedTime;

};
    class Mining : Packet
    {
        MirDirection Direction;
};
    
    class Magic : Packet
    {
        MirDirection Direction;
        MirAction Action;
        MagicType Type;
        uint32_t Target;
        Point Location;
};

    class ItemMove : Packet
    {
        GridType FromGrid;
        GridType ToGrid;
        int32_t FromSlot;
        int32_t ToSlot;
        bool MergeItem;
};

    class ItemSort : Packet
    {
        GridType Grid;
};

    class ItemDelete : Packet
    {
        GridType Grid;
        int32_t Slot;
};

    class ItemSplit : Packet 
    {
        GridType Grid;
        int32_t Slot;
        int64_t Count;
};

    class ItemDrop : Packet
    {
        CellLinkInfo Link;
        int32_t Slot;
};

    class CurrencyDrop : Packet
    {
        int32_t CurrencyIndex;
        int64_t Amount;
};

    class ItemUse : Packet
    {
        CellLinkInfo Link;
};

    class ItemLock : Packet
    {
        GridType GridType;
        int32_t SlotIndex;
        bool Locked;
};

    class BeltLinkChanged : Packet
    {
        int32_t Slot;
        int32_t LinkIndex;
        int32_t LinkItemIndex;
};

    class AutoPotionLinkChanged : Packet
    {
        int32_t Slot;
        int32_t LinkIndex;
        int32_t Health;
        int32_t Mana;
        bool Enabled;
};

    class PickUp : Packet {}

    class Chat : Packet
    {
        std::string Text;
};

    class NPCCall : Packet
    {
        uint32_t ObjectID;
};

    class NPCButton : Packet
    {
        int32_t ButtonID;
};

    class NPCRoll : Packet
    {
        int32_t Type;
};

    class NPCRollResult : Packet
    {
};

    class NPCBuy : Packet
    {
        int32_t Index;
        int64_t Amount;
        bool GuildFunds;
};

    class NPCSell : Packet
    {
        std::vector<CellLinkInfo> Links;

};

    class NPCFragment : Packet
    {
        std::vector<CellLinkInfo> Links;

};

    class NPCRepair : Packet
    {
        std::vector<CellLinkInfo> Links;
        bool Special;
        bool GuildFunds;
};

    class NPCRefine : Packet
    {
        RefineType RefineType;
        RefineQuality RefineQuality;
        std::vector<CellLinkInfo> Ores;
        std::vector<CellLinkInfo> Items;
        std::vector<CellLinkInfo> Specials;
};
    class NPCMasterRefine : Packet
    {
        RefineType RefineType;
        std::vector<CellLinkInfo> Fragment1s;
        std::vector<CellLinkInfo> Fragment2s;
        std::vector<CellLinkInfo> Fragment3s;
        std::vector<CellLinkInfo> Stones;
        std::vector<CellLinkInfo> Specials;
};
    class NPCMasterRefineEvaluate : Packet
    {
        RefineType RefineType;
        std::vector<CellLinkInfo> Fragment1s;
        std::vector<CellLinkInfo> Fragment2s;
        std::vector<CellLinkInfo> Fragment3s;
        std::vector<CellLinkInfo> Stones;
        std::vector<CellLinkInfo> Specials;
};
    class NPCRefinementStone : Packet
    {
        std::vector<CellLinkInfo> IronOres;
        std::vector<CellLinkInfo> SilverOres;
        std::vector<CellLinkInfo> DiamondOres;
        std::vector<CellLinkInfo> GoldOres;
        std::vector<CellLinkInfo> Crystal;
        int64_t Gold;
};

    class NPCClose : Packet
    {
};

    class NPCRefineRetrieve : Packet
    {
        int32_t Index;
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
};

    class MagicKey : Packet
    {
        MagicType Magic;

        SpellKey Set1Key;
        SpellKey Set2Key;
        SpellKey Set3Key;
        SpellKey Set4Key;
};

    class MagicToggle : Packet
    {
        MagicType Magic;
        bool CanUse;
};

    class GroupNotify : Packet
    {
        bool Receive;
};

    class GroupSwitch : Packet
    {
        bool Allow;
};

    class GroupInvite : Packet
    {
        std::string Name;
};

    class GroupRequest : Packet
    {
        std::string Name;
};

    class GroupRemove : Packet
    {
        std::string Name;
};

    class GroupResponse : Packet
    {
        bool Accept;
};

    class GroupLFGUpdate : Packet
    {
        bool Enabled;
        std::string Name;
        std::string Type;
        int32_t MaxCount;
};

    class Inspect : Packet
    {
        int32_t Index;
        bool Ranking;
};

    class RankRequest : Packet
    {
        RequiredClass Class;
        bool OnlineOnly;
        int32_t StartIndex;
};

    class RankSearch : Packet
    {
        std::string Name;
};

    class ObserverRequest : Packet
    {
        std::string Name;
};

    class ObservableSwitch : Packet
    {
        bool Allow;
};

    class Hermit : Packet
    {
        Stat Stat;
};


    class MarketPlaceHistory : Packet
    {
        int32_t Index;
        int32_t Display;
        int32_t PartIndex;
};
    class MarketPlaceConsign : Packet
    {
        CellLinkInfo Link;

        int32_t Price;

        std::string Message;
        bool GuildFunds;
};
    class MarketPlaceSearch : Packet
    {
        std::string Name;

        bool ItemTypeFilter;
        ItemType ItemType;

        MarketPlaceSort Sort;
};
    class MarketPlaceSearchIndex : Packet
    {
        int32_t Index;
};
    class MarketPlaceCancelConsign : Packet
    {
        int32_t Index;
        int64_t Count;
};
    class MarketPlaceBuy : Packet
    {
        int64_t Index;
        int64_t Count;
        bool GuildFunds;
};
    class MarketPlaceStoreBuy : Packet
    {
        int32_t Index;
        int64_t Count;
        bool UseHuntGold;
};


    class MailOpened : Packet
    {
        int32_t Index;
};
    class MailGetItem : Packet
    {
        int32_t Index;
        int32_t Slot;
};
    class MailDelete : Packet
    {
        int32_t Index;
};
    class MailSend : Packet
    {
        std::vector<CellLinkInfo> Links;
        std::string Recipient;
        std::string Subject;
        std::string Message;
        int64_t Gold;
};


    class ChangeAttackMode : Packet
    {
        AttackMode Mode;
};
    class ChangePetMode : Packet
    {
        PetMode Mode;
};

    class GameGoldRecharge : Packet
    { }

    class TradeRequest : Packet
    {
};
    class TradeRequestResponse : Packet
    {
        bool Accept;
};
    class TradeClose : Packet
    {

};
    class TradeAddGold : Packet
    {
        int64_t Gold;
};
    class TradeAddItem : Packet
    {
        CellLinkInfo Cell;
};
    class TradeConfirm : Packet
    {

};

    class GuildCreate : Packet
    {
        std::string Name;
        bool UseGold;
        int32_t Members;
        int32_t Storage;
};
    class GuildEditNotice : Packet
    {
        std::string Notice;
};
    class GuildEditMember : Packet
    {
        int32_t Index;
        std::string Rank;
        GuildPermission Permission;

};
    class GuildInviteMember : Packet
    {
        std::string Name;
};
    class GuildKickMember : Packet
    {
        int32_t Index;
};
    class GuildTax : Packet
    {
        int64_t Tax;
};
    class GuildIncreaseMember : Packet
    {

};
    class GuildIncreaseStorage : Packet
    {

};
    class GuildResponse : Packet
    {
        bool Accept;
};

    class GuildWar : Packet
    {
        std::string GuildName;
};

    class GuildRequestConquest : Packet
    {
        int32_t Index;
};

    class GuildColour : Packet
    {
        Color Colour;
};

    class GuildFlag : Packet
    {
        int32_t Flag;
};

    class GuildToggleCastleGates : Packet
    {

};

    class GuildRepairCastleGates : Packet
    {

};

    class GuildRepairCastleGuards : Packet
    {

};

    class QuestAccept : Packet
    {
        int32_t Index;
};
    class QuestComplete : Packet
    {
        int32_t Index;

        int32_t ChoiceIndex;
};
    class QuestTrack : Packet
    {
        int32_t Index;

        bool Track;
};
    class QuestAbandon : Packet
    {
        int32_t Index;
};

    class CompanionUnlock : Packet
    {
        int32_t Index;
};
    class CompanionAdopt : Packet
    {
        int32_t Index;
        std::string Name;
};

    class CompanionRetrieve : Packet
    {
        int32_t Index;
};
    class CompanionStore : Packet
    {
        int32_t Index;
};
    class MarriageResponse : Packet
    {
        bool Accept;
};

    class MarriageMakeRing : Packet
    {
        int32_t Slot;
};

    class MarriageTeleport : Packet
    {
        
};

    class BlockAdd : Packet
    {
        std::string Name;
};
    class BlockRemove : Packet
    {
        int32_t Index;
};

    class HelmetToggle : Packet
    {
        bool HideHelmet;
};

    class GenderChange : Packet
    {
        MirGender Gender;
        int32_t HairType;
        Color HairColour;
};

    class HairChange : Packet
    {
        int32_t HairType;
        Color HairColour;
};

    class ArmourDye : Packet
    {
        Color ArmourColour;
};

    class NameChange : Packet
    {
        std::string Name;
};

    class CaptionChange : Packet
    {
        std::string Caption;
};

    class FortuneCheck : Packet
    {
        int32_t ItemIndex;
};

    class TeleportRing : Packet
    {
        Point Location;
        int32_t Index;
};

    class JoinStarterGuild : Packet
    {
        
};

    class NPCAccessoryReset : Packet
    {
        CellLinkInfo Cell;
};
    class NPCWeaponCraft : Packet
    {
        RequiredClass Class;
        CellLinkInfo Template;
        CellLinkInfo Yellow;
        CellLinkInfo Blue;
        CellLinkInfo Red;
        CellLinkInfo Purple;
        CellLinkInfo Green;
        CellLinkInfo Grey;
};
    class NPCAccessoryRefine : Packet
    {
        CellLinkInfo Target;
        CellLinkInfo OreTarget;
        std::vector<CellLinkInfo> Links;
        RefineType RefineType;
};

    class RequestInstance : Packet
    {
        int32_t Index;
};

    class JoinInstance : Packet
    {
        int32_t Index;
};

    class SendCompanionFilters : Packet
    {
        std::vector<MirClass> FilterClass;
        std::vector<Rarity> FilterRarity;
        std::vector<ItemType> FilterItemType;
};
    class ChangeOnlineState : Packet
    {
        OnlineState State;
};

    class FriendAdd : Packet
    {
        std::string Name;
};
    class FriendRemove : Packet
    {
        int32_t Index;
};

    class IncreaseDiscipline : Packet
    {
};
};

}
