#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"
#include "../DBBindingList.h"

namespace Server::DBModels
{
    class MapInfo;
    class ItemInfo;
    class NPCPage;

    struct ClientNPCInfo;

    class NPCInfo : public DBObject
    {
    private:
        MapInfo* _Map = nullptr;
        std::string _NPCName;
        int _Image = 0;
        int _X = 0;
        int _Y = 0;
        NPCPage* _EntryPage = nullptr;

    public:
        // Association("NPCs")
        MapInfo* GetMap() const { return _Map; }
        void SetMap(MapInfo* value);

        std::string GetNPCName() const { return _NPCName; }
        void SetNPCName(const std::string& value);

        int GetImage() const { return _Image; }
        void SetImage(int value);

        int GetX() const { return _X; }
        void SetX(int value);

        int GetY() const { return _Y; }
        void SetY(int value);

        // Association("NPCs")
        NPCPage* GetEntryPage() const { return _EntryPage; }
        void SetEntryPage(NPCPage* value);

        ClientNPCInfo ToClientInfo();
    };

    class NPCPage : public DBObject
    {
    private:
        std::string _Description;
        Library::NPCDialogType _DialogType = Library::NPCDialogType::None;
        std::string _Say;
        NPCPage* _SuccessPage = nullptr;
        std::string _Arguments;

        DBBindingList<class NPCCheck>* _Checks = nullptr;
        DBBindingList<class NPCAction>* _Actions = nullptr;
        DBBindingList<class NPCButton>* _Buttons = nullptr;
        DBBindingList<class NPCGood>* _Goods = nullptr;
        DBBindingList<class NPCType>* _Types = nullptr;

    public:
        std::string GetDescription() const { return _Description; }
        void SetDescription(const std::string& value);

        Library::NPCDialogType GetDialogType() const { return _DialogType; }
        void SetDialogType(Library::NPCDialogType value);

        std::string GetSay() const { return _Say; }
        void SetSay(const std::string& value);

        NPCPage* GetSuccessPage() const { return _SuccessPage; }
        void SetSuccessPage(NPCPage* value);

        std::string GetArguments() const { return _Arguments; }
        void SetArguments(const std::string& value);

        // Association("Checks", true)
        DBBindingList<NPCCheck>* GetChecks() const { return _Checks; }
        void SetChecks(DBBindingList<NPCCheck>* value);

        // Association("Actions", true)
        DBBindingList<NPCAction>* GetActions() const { return _Actions; }
        void SetActions(DBBindingList<NPCAction>* value);

        // Association("Buttons", true)
        DBBindingList<NPCButton>* GetButtons() const { return _Buttons; }
        void SetButtons(DBBindingList<NPCButton>* value);

        // Association("Goods", true)
        DBBindingList<NPCGood>* GetGoods() const { return _Goods; }
        void SetGoods(DBBindingList<NPCGood>* value);

        // Association("Types", true)
        DBBindingList<NPCType>* GetTypes() const { return _Types; }
        void SetTypes(DBBindingList<NPCType>* value);
    };

    class NPCGood : public DBObject
    {
    private:
        NPCPage* _Page = nullptr;
        ItemInfo* _Item = nullptr;
        double _Rate = 1.0;

    public:
        // Association("Goods")
        NPCPage* GetPage() const { return _Page; }
        void SetPage(NPCPage* value);

        ItemInfo* GetItem() const { return _Item; }
        void SetItem(ItemInfo* value);

        double GetRate() const { return _Rate; }
        void SetRate(double value);

    protected:
        void OnCreated() override;
    };

    class NPCType : public DBObject
    {
    private:
        NPCPage* _Page = nullptr;
        Library::ItemType _ItemType = Library::ItemType::None;

    public:
        // Association("Types")
        NPCPage* GetPage() const { return _Page; }
        void SetPage(NPCPage* value);

        Library::ItemType GetItemType() const { return _ItemType; }
        void SetItemType(Library::ItemType value);
    };

    class NPCCheck : public DBObject
    {
    private:
        NPCPage* _Page = nullptr;
        Library::NPCCheckType _CheckType = Library::NPCCheckType::Level;
        Library::Operator _Operator = Library::Operator::Equal;
        std::string _StringParameter1;
        int _IntParameter1 = 0;
        int _IntParameter2 = 0;
        NPCPage* _FailPage = nullptr;

    public:
        // Association("Checks")
        NPCPage* GetPage() const { return _Page; }
        void SetPage(NPCPage* value);

        Library::NPCCheckType GetCheckType() const { return _CheckType; }
        void SetCheckType(Library::NPCCheckType value);

        Library::Operator GetOperator() const { return _Operator; }
        void SetOperator(Library::Operator value);

        std::string GetStringParameter1() const { return _StringParameter1; }
        void SetStringParameter1(const std::string& value);

        int GetIntParameter1() const { return _IntParameter1; }
        void SetIntParameter1(int value);

        int GetIntParameter2() const { return _IntParameter2; }
        void SetIntParameter2(int value);

        // Association("Checks")
        NPCPage* GetFailPage() const { return _FailPage; }
        void SetFailPage(NPCPage* value);
    };

    class NPCAction : public DBObject
    {
    private:
        NPCPage* _Page = nullptr;
        Library::NPCActionType _ActionType = Library::NPCActionType::Teleport;
        std::string _StringParameter1;
        int _IntParameter1 = 0;
        int _IntParameter2 = 0;
        MapInfo* _MapParameter1 = nullptr;

    public:
        // Association("Actions")
        NPCPage* GetPage() const { return _Page; }
        void SetPage(NPCPage* value);

        Library::NPCActionType GetActionType() const { return _ActionType; }
        void SetActionType(Library::NPCActionType value);

        std::string GetStringParameter1() const { return _StringParameter1; }
        void SetStringParameter1(const std::string& value);

        int GetIntParameter1() const { return _IntParameter1; }
        void SetIntParameter1(int value);

        int GetIntParameter2() const { return _IntParameter2; }
        void SetIntParameter2(int value);

        // Association("Actions")
        MapInfo* GetMapParameter1() const { return _MapParameter1; }
        void SetMapParameter1(MapInfo* value);
    };

    class NPCButton : public DBObject
    {
    private:
        NPCPage* _Page = nullptr;
        int _ButtonID = 0;
        NPCPage* _DestinationPage = nullptr;

    public:
        // Association("Buttons")
        NPCPage* GetPage() const { return _Page; }
        void SetPage(NPCPage* value);

        int GetButtonID() const { return _ButtonID; }
        void SetButtonID(int value);

        // Association("Buttons")
        NPCPage* GetDestinationPage() const { return _DestinationPage; }
        void SetDestinationPage(NPCPage* value);
    };

} // namespace Server::DBModels
