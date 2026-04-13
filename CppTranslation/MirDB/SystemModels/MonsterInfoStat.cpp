#include "MonsterInfoStat.h"
#include "MonsterInfo.h"

namespace Server::DBModels
{
    void MonsterInfoStat::SetMonster(MonsterInfo* value)
    {
        if (_Monster == value) return;
        MonsterInfo* oldValue = _Monster;
        _Monster = value;
        OnChanged(oldValue, value, "Monster");
    }

    void MonsterInfoStat::SetStat(Library::Stat value)
    {
        if (_Stat == value) return;
        Library::Stat oldValue = _Stat;
        _Stat = value;
        OnChanged(oldValue, value, "Stat");
    }

    void MonsterInfoStat::SetAmount(int value)
    {
        if (_Amount == value) return;
        int oldValue = _Amount;
        _Amount = value;
        OnChanged(oldValue, value, "Amount");
    }
} // namespace Server::DBModels
