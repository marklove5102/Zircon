#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"

namespace Server::DBModels
{
    class MonsterInfo;

    class MonsterInfoStat : public DBObject
    {
    private:
        MonsterInfo* _Monster = nullptr;
        Library::Stat _Stat = Library::Stat::None;
        int _Amount = 0;

    public:
        // Association("MonsterInfoStats")
        MonsterInfo* GetMonster() const { return _Monster; }
        void SetMonster(MonsterInfo* value);

        Library::Stat GetStat() const { return _Stat; }
        void SetStat(Library::Stat value);

        int GetAmount() const { return _Amount; }
        void SetAmount(int value);
    };

} // namespace Server::DBModels
