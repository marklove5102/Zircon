#pragma once
#include "../MirDB/DBObject.h"

namespace Library { namespace SystemModels {

class ItemInfo;
class MonsterInfo;

// DropInfo class
class DropInfo : public MirDB::DBObject
{
public:
    // Properties
    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);
    
    ItemInfo* GetItem() const { return _Item; }
    void SetItem(ItemInfo* value);
    
    int GetChance() const { return _Chance; }
    void SetChance(int value);
    
    int GetAmount() const { return _Amount; }
    void SetAmount(int value);
    
    int GetDropSet() const { return _DropSet; }
    void SetDropSet(int value);
    
    bool GetPartOnly() const { return _PartOnly; }
    void SetPartOnly(bool value);
    
    bool GetEasterEvent() const { return _EasterEvent; }
    void SetEasterEvent(bool value);
    
protected:
    void OnCreated() override;
    
private:
    MonsterInfo* _Monster = nullptr;
    ItemInfo* _Item = nullptr;
    int _Chance = 0;
    int _Amount = 1;
    int _DropSet = 0;
    bool _PartOnly = false;
    bool _EasterEvent = false;
};

}} // namespace Library::SystemModels
