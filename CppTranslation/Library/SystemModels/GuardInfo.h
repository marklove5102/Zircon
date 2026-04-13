#pragma once

#include "../MirDB/DBObject.h"
#include "MapInfo.h"
#include "MonsterInfo.h"
#include "../Enum.h"

namespace Library::SystemModels
{

class GuardInfo : public DBObject
{
private:
    MapInfo* _Map;
    MonsterInfo* _Monster;
    int _X;
    int _Y;
    MirDirection _Direction;

public:
    MapInfo* GetMap() const { return _Map; }
    void SetMap(MapInfo* value);

    MonsterInfo* GetMonster() const { return _Monster; }
    void SetMonster(MonsterInfo* value);

    int GetX() const { return _X; }
    void SetX(int value);

    int GetY() const { return _Y; }
    void SetY(int value);

    MirDirection GetDirection() const { return _Direction; }
    void SetDirection(MirDirection value);
};

} // namespace Library::SystemModels
