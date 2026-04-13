#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"

namespace Server::DBModels
{
    class MapInfo;
    class MonsterInfo;

    class GuardInfo : public DBObject
    {
    private:
        MapInfo* _Map = nullptr;
        MonsterInfo* _Monster = nullptr;
        int _X = 0;
        int _Y = 0;
        Library::MirDirection _Direction = Library::MirDirection::Up;

    public:
        // Association("Guards")
        MapInfo* GetMap() const { return _Map; }
        void SetMap(MapInfo* value);

        MonsterInfo* GetMonster() const { return _Monster; }
        void SetMonster(MonsterInfo* value);

        int GetX() const { return _X; }
        void SetX(int value);

        int GetY() const { return _Y; }
        void SetY(int value);

        Library::MirDirection GetDirection() const { return _Direction; }
        void SetDirection(Library::MirDirection value);
    };

} // namespace Server::DBModels
