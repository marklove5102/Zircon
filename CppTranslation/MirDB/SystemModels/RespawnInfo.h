#pragma once
#include "DBObject.h"
#include "../Library/Enum.h"
#include <string>

namespace Server::DBModels
{
    class MonsterInfo;
    class MapInfo;

    public sealed class RespawnInfo : public DBObject
    {
    private:
        MonsterInfo* _Monster = nullptr;
        MapInfo* _Map = nullptr;
        int _X = 0;
        int _Y = 0;
        int _Delay = 0;
        int _Spread = 0;
        int _Count = 0;
        int _DropSet = 0;

    public:
        // Association("Respawns")
        MonsterInfo* GetMonster() const { return _Monster; }
        void SetMonster(MonsterInfo* value);

        // Association("Respawns")
        MapInfo* GetMap() const { return _Map; }
        void SetMap(MapInfo* value);

        int GetX() const { return _X; }
        void SetX(int value);

        int GetY() const { return _Y; }
        void SetY(int value);

        int GetDelay() const { return _Delay; }
        void SetDelay(int value);

        int GetSpread() const { return _Spread; }
        void SetSpread(int value);

        int GetCount() const { return _Count; }
        void SetCount(int value);

        int GetDropSet() const { return _DropSet; }
        void SetDropSet(int value);
    };
}
