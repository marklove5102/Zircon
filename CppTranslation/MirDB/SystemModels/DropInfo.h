#pragma once
#include "../DBObject.h"

namespace Server::DBModels
{
    class MonsterInfo;
    class ItemInfo;

    class DropInfo : public DBObject
    {
    private:
        MonsterInfo* _Monster = nullptr;
        ItemInfo* _Item = nullptr;
        int _Chance = 0;
        int _Amount = 1;
        int _DropSet = 0;

    public:
        // Association("Drops")
        MonsterInfo* GetMonster() const { return _Monster; }
        void SetMonster(MonsterInfo* value);

        // Association("Drops")
        ItemInfo* GetItem() const { return _Item; }
        void SetItem(ItemInfo* value);

        int GetChance() const { return _Chance; }
        void SetChance(int value);

        int GetAmount() const { return _Amount; }
        void SetAmount(int value);

        int GetDropSet() const { return _DropSet; }
        void SetDropSet(int value);

    protected:
        void OnCreated() override;
    };

} // namespace Server::DBModels
