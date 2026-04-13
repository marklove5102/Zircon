#pragma once
#include "../MirDB/DBObject.h"

namespace Library { namespace SystemModels {

class ItemInfo;
class MonsterInfo;

// Forward declaration for ItemInfoStat
class ItemInfoStat : public MirDB::DBObject
{
public:
    // Properties
    ItemInfo* GetItem() const { return _Item; }
    void SetItem(ItemInfo* value);
    
    Stat GetStat() const { return _Stat; }
    void SetStat(Stat value);
    
    int GetAmount() const { return _Amount; }
    void SetAmount(int value);
    
private:
    ItemInfo* _Item = nullptr;
    Stat _Stat;
    int _Amount = 0;
};

}} // namespace Library::SystemModels
