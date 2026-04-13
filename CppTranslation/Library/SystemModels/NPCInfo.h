#pragma once
#include "MirDB/DBObject.h"
#include "MirDB/DBBindingList.h"
#include "Enum.h"

namespace Library::SystemModels
{
    class MapRegion;
    class NPCPage;
    class QuestInfo;

    public sealed class NPCInfo : public DBObject
    {
    public:
        PROPERTY(MapRegion*, Region);
        PROPERTY(std::string, NPCName);
        PROPERTY(int, Image);
        PROPERTY(NPCPage*, EntryPage);
        
        [IgnoreProperty]
        std::string GetRegionName() const;
        
        DBBindingList<QuestInfo*> StartQuests;
        DBBindingList<QuestInfo*> FinishQuests;
        
        QuestIcon CurrentIcon;
    };
    
    class NPCDialogType;
    class NPCAction;
    class NPCCheck;
    class NPCButton;
    class NPCGood;
    class NPCType;

    public sealed class NPCPage : public DBObject
    {
    public:
        PROPERTY(std::string, Description);
        PROPERTY(NPCDialogType, DialogType);
        PROPERTY(std::string, Say);
        PROPERTY(NPCPage*, SuccessPage);
        PROPERTY(std::string, Arguments);
        
        DBBindingList<NPCCheck*> Checks;
        DBBindingList<NPCAction*> Actions;
        DBBindingList<NPCButton*> Buttons;
        DBBindingList<NPCGood*> Goods;
        DBBindingList<NPCType*> Types;
    };

    public sealed class NPCGood : public DBObject
    {
    public:
        PROPERTY(NPCPage*, Page);
        PROPERTY(ItemInfo*, Item);
        PROPERTY(int, Count);
        PROPERTY(int, MaxCount);
        PROPERTY(int, Price);
        PROPERTY(int, StockLevel);
        PROPERTY(int, DelayRate);
        PROPERTY(int, DropSet);
        PROPERTY(int, ClassSet);
    };

    public sealed class NPCType : public DBObject
    {
    public:
        PROPERTY(NPCPage*, Page);
        PROPERTY(std::string, Name);
        PROPERTY(bool, CanBuy);
        PROPERTY(bool, CanSell);
        PROPERTY(bool, CanRepair);
        PROPERTY(bool, CanRefine);
        PROPERTY(bool, CanReplaceWeddingRing);
        PROPERTY(bool, CanInsure);
        PROPERTY(bool, CanUnlockBag);
        PROPERTY(bool, CanTradeCompanion);
        PROPERTY(int, Type);
    };

    public sealed class NPCCheck : public DBObject
    {
    public:
        PROPERTY(NPCPage*, Page);
        PROPERTY(CheckType, Type);
        PROPERTY(std::string, Parameter);
        PROPERTY(std::string, Message);
        PROPERTY(bool, Enabled);
    };

    public sealed class NPCAction : public DBObject
    {
    public:
        PROPERTY(NPCPage*, Page);
        PROPERTY(ActionType, Type);
        PROPERTY(std::string, Parameter);
        PROPERTY(bool, Enabled);
    };

    public sealed class NPCButton : public DBObject
    {
    public:
        PROPERTY(NPCPage*, Page);
        PROPERTY(std::string, Text);
        PROPERTY(NPCPage*, LinkPage);
        PROPERTY(int, Image);
        PROPERTY(bool, Enabled);
    };
}
