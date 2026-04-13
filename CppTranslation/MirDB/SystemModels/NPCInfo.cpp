// NPCInfo.cpp - MirDB SystemModels NPC 相关类实现
// 对应 C# Server.DBModels.NPCInfo

#include "NPCInfo.h"
#include "../DBObject.h"

namespace Server::DBModels
{

// ============================================================================
// NPCInfo 实现
// ============================================================================

void NPCInfo::SetMap(MapInfo* value)
{
    if (_Map == value) return;
    
    MapInfo* oldValue = _Map;
    _Map = value;
    
    // TODO: OnChanged(oldValue, value, "Map");
}

void NPCInfo::SetNPCName(const std::string& value)
{
    if (_NPCName == value) return;
    
    std::string oldValue = _NPCName;
    _NPCName = value;
    
    // TODO: OnChanged(oldValue, value, "NPCName");
}

void NPCInfo::SetImage(int value)
{
    if (_Image == value) return;
    
    int oldValue = _Image;
    _Image = value;
    
    // TODO: OnChanged(oldValue, value, "Image");
}

void NPCInfo::SetX(int value)
{
    if (_X == value) return;
    
    int oldValue = _X;
    _X = value;
    
    // TODO: OnChanged(oldValue, value, "X");
}

void NPCInfo::SetY(int value)
{
    if (_Y == value) return;
    
    int oldValue = _Y;
    _Y = value;
    
    // TODO: OnChanged(oldValue, value, "Y");
}

void NPCInfo::SetEntryPage(NPCPage* value)
{
    if (_EntryPage == value) return;
    
    NPCPage* oldValue = _EntryPage;
    _EntryPage = value;
    
    // TODO: OnChanged(oldValue, value, "EntryPage");
}

ClientNPCInfo NPCInfo::ToClientInfo()
{
    ClientNPCInfo info;
    // TODO: 实现转换逻辑
    // info.Index = Index;
    // info.CurrentLocation = Point(X, Y);
    // info.Image = Image;
    // info.NPCName = NPCName;
    return info;
}

// ============================================================================
// NPCPage 实现
// ============================================================================

void NPCPage::SetDescription(const std::string& value)
{
    if (_Description == value) return;
    
    std::string oldValue = _Description;
    _Description = value;
    
    // TODO: OnChanged(oldValue, value, "Description");
}

void NPCPage::SetDialogType(Library::NPCDialogType value)
{
    if (_DialogType == value) return;
    
    Library::NPCDialogType oldValue = _DialogType;
    _DialogType = value;
    
    // TODO: OnChanged(oldValue, value, "DialogType");
}

void NPCPage::SetSay(const std::string& value)
{
    if (_Say == value) return;
    
    std::string oldValue = _Say;
    _Say = value;
    
    // TODO: OnChanged(oldValue, value, "Say");
}

void NPCPage::SetSuccessPage(NPCPage* value)
{
    if (_SuccessPage == value) return;
    
    NPCPage* oldValue = _SuccessPage;
    _SuccessPage = value;
    
    // TODO: OnChanged(oldValue, value, "SuccessPage");
}

void NPCPage::SetArguments(const std::string& value)
{
    if (_Arguments == value) return;
    
    std::string oldValue = _Arguments;
    _Arguments = value;
    
    // TODO: OnChanged(oldValue, value, "Arguments");
}

void NPCPage::SetChecks(DBBindingList<NPCCheck>* value)
{
    if (_Checks == value) return;
    
    DBBindingList<NPCCheck>* oldValue = _Checks;
    _Checks = value;
    
    // TODO: OnChanged(oldValue, value, "Checks");
}

void NPCPage::SetActions(DBBindingList<NPCAction>* value)
{
    if (_Actions == value) return;
    
    DBBindingList<NPCAction>* oldValue = _Actions;
    _Actions = value;
    
    // TODO: OnChanged(oldValue, value, "Actions");
}

void NPCPage::SetButtons(DBBindingList<NPCButton>* value)
{
    if (_Buttons == value) return;
    
    DBBindingList<NPCButton>* oldValue = _Buttons;
    _Buttons = value;
    
    // TODO: OnChanged(oldValue, value, "Buttons");
}

void NPCPage::SetGoods(DBBindingList<NPCGood>* value)
{
    if (_Goods == value) return;
    
    DBBindingList<NPCGood>* oldValue = _Goods;
    _Goods = value;
    
    // TODO: OnChanged(oldValue, value, "Goods");
}

void NPCPage::SetTypes(DBBindingList<NPCType>* value)
{
    if (_Types == value) return;
    
    DBBindingList<NPCType>* oldValue = _Types;
    _Types = value;
    
    // TODO: OnChanged(oldValue, value, "Types");
}

// ============================================================================
// NPCGood 实现
// ============================================================================

void NPCGood::SetPage(NPCPage* value)
{
    if (_Page == value) return;
    
    NPCPage* oldValue = _Page;
    _Page = value;
    
    // TODO: OnChanged(oldValue, value, "Page");
}

void NPCGood::SetItem(ItemInfo* value)
{
    if (_Item == value) return;
    
    ItemInfo* oldValue = _Item;
    _Item = value;
    
    // TODO: OnChanged(oldValue, value, "Item");
}

void NPCGood::SetRate(double value)
{
    if (_Rate == value) return;
    
    double oldValue = _Rate;
    _Rate = value;
    
    // TODO: OnChanged(oldValue, value, "Rate");
}

void NPCGood::OnCreated()
{
    // base.OnCreated();
    _Rate = 1.0;
}

// ============================================================================
// NPCType 实现
// ============================================================================

void NPCType::SetPage(NPCPage* value)
{
    if (_Page == value) return;
    
    NPCPage* oldValue = _Page;
    _Page = value;
    
    // TODO: OnChanged(oldValue, value, "Page");
}

void NPCType::SetItemType(Library::ItemType value)
{
    if (_ItemType == value) return;
    
    Library::ItemType oldValue = _ItemType;
    _ItemType = value;
    
    // TODO: OnChanged(oldValue, value, "ItemType");
}

// ============================================================================
// NPCCheck 实现
// ============================================================================

void NPCCheck::SetPage(NPCPage* value)
{
    if (_Page == value) return;
    
    NPCPage* oldValue = _Page;
    _Page = value;
    
    // TODO: OnChanged(oldValue, value, "Page");
}

void NPCCheck::SetCheckType(Library::NPCCheckType value)
{
    if (_CheckType == value) return;
    
    Library::NPCCheckType oldValue = _CheckType;
    _CheckType = value;
    
    // TODO: OnChanged(oldValue, value, "CheckType");
}

void NPCCheck::SetOperator(Library::Operator value)
{
    if (_Operator == value) return;
    
    Library::Operator oldValue = _Operator;
    _Operator = value;
    
    // TODO: OnChanged(oldValue, value, "Operator");
}

void NPCCheck::SetStringParameter1(const std::string& value)
{
    if (_StringParameter1 == value) return;
    
    std::string oldValue = _StringParameter1;
    _StringParameter1 = value;
    
    // TODO: OnChanged(oldValue, value, "StringParameter1");
}

void NPCCheck::SetIntParameter1(int value)
{
    if (_IntParameter1 == value) return;
    
    int oldValue = _IntParameter1;
    _IntParameter1 = value;
    
    // TODO: OnChanged(oldValue, value, "IntParameter1");
}

void NPCCheck::SetIntParameter2(int value)
{
    if (_IntParameter2 == value) return;
    
    int oldValue = _IntParameter2;
    _IntParameter2 = value;
    
    // TODO: OnChanged(oldValue, value, "IntParameter2");
}

void NPCCheck::SetFailPage(NPCPage* value)
{
    if (_FailPage == value) return;
    
    NPCPage* oldValue = _FailPage;
    _FailPage = value;
    
    // TODO: OnChanged(oldValue, value, "FailPage");
}

// ============================================================================
// NPCAction 实现
// ============================================================================

void NPCAction::SetPage(NPCPage* value)
{
    if (_Page == value) return;
    
    NPCPage* oldValue = _Page;
    _Page = value;
    
    // TODO: OnChanged(oldValue, value, "Page");
}

void NPCAction::SetActionType(Library::NPCActionType value)
{
    if (_ActionType == value) return;
    
    Library::NPCActionType oldValue = _ActionType;
    _ActionType = value;
    
    // TODO: OnChanged(oldValue, value, "ActionType");
}

void NPCAction::SetStringParameter1(const std::string& value)
{
    if (_StringParameter1 == value) return;
    
    std::string oldValue = _StringParameter1;
    _StringParameter1 = value;
    
    // TODO: OnChanged(oldValue, value, "StringParameter1");
}

void NPCAction::SetIntParameter1(int value)
{
    if (_IntParameter1 == value) return;
    
    int oldValue = _IntParameter1;
    _IntParameter1 = value;
    
    // TODO: OnChanged(oldValue, value, "IntParameter1");
}

void NPCAction::SetIntParameter2(int value)
{
    if (_IntParameter2 == value) return;
    
    int oldValue = _IntParameter2;
    _IntParameter2 = value;
    
    // TODO: OnChanged(oldValue, value, "IntParameter2");
}

void NPCAction::SetMapParameter1(MapInfo* value)
{
    if (_MapParameter1 == value) return;
    
    MapInfo* oldValue = _MapParameter1;
    _MapParameter1 = value;
    
    // TODO: OnChanged(oldValue, value, "MapParameter1");
}

// ============================================================================
// NPCButton 实现
// ============================================================================

void NPCButton::SetPage(NPCPage* value)
{
    if (_Page == value) return;
    
    NPCPage* oldValue = _Page;
    _Page = value;
    
    // TODO: OnChanged(oldValue, value, "Page");
}

void NPCButton::SetButtonID(int value)
{
    if (_ButtonID == value) return;
    
    int oldValue = _ButtonID;
    _ButtonID = value;
    
    // TODO: OnChanged(oldValue, value, "ButtonID");
}

void NPCButton::SetDestinationPage(NPCPage* value)
{
    if (_DestinationPage == value) return;
    
    NPCPage* oldValue = _DestinationPage;
    _DestinationPage = value;
    
    // TODO: OnChanged(oldValue, value, "DestinationPage");
}

} // namespace Server::DBModels
