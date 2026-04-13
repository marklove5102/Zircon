#include "MonsterInfoStat.h"
#include "MonsterInfo.h"

namespace Library { namespace SystemModels {

void MonsterInfoStat::SetMonster(MonsterInfo* value)
{
    if (_Monster == value) return;
    
    auto oldValue = _Monster;
    _Monster = value;
    OnChanged(oldValue, value, "Monster");
}

void MonsterInfoStat::SetStat(Stat value)
{
    if (_Stat == value) return;
    
    auto oldValue = _Stat;
    _Stat = value;
    OnChanged(oldValue, value, "Stat");
}

void MonsterInfoStat::SetAmount(int value)
{
    if (_Amount == value) return;
    
    auto oldValue = _Amount;
    _Amount = value;
    OnChanged(oldValue, value, "Amount");
}

}} // namespace Library::SystemModels
