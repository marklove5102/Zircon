#pragma once
#include "../MirDB/DBObject.h"
#include "../Enum.h"

namespace Library { namespace SystemModels {

class MonsterInfo;

// MonsterInfoStat class
class MonsterInfoStat : public MirDB::DBObject
{
public:
    // Properties
    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);
    
    Stat GetStat() const { return _Stat; }
    void SetStat(Stat value);
    
    int GetAmount() const { return _Amount; }
    void SetAmount(int value);
    
private:
    MonsterInfo* _Monster = nullptr;
    Stat _Stat;
    int _Amount = 0;
};

}} // namespace Library::SystemModels
