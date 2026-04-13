#pragma once
#include "DBObject.h"
#include "../Library/Enum.h"
#include <string>

namespace Server::DBModels
{
    class MapInfo;

    public sealed class SafeZoneInfo : public DBObject
    {
    private:
        MapInfo* _Map = nullptr;
        int _X = 0;
        int _Y = 0;
        int _Size = 0;
        bool _BindPoint = false;
        RequiredClass _StartClass = RequiredClass::All;

    public:
        // Association("SafeZones")
        MapInfo* GetMap() const { return _Map; }
        void SetMap(MapInfo* value);

        int GetX() const { return _X; }
        void SetX(int value);

        int GetY() const { return _Y; }
        void SetY(int value);

        int GetSize() const { return _Size; }
        void SetSize(int value);

        bool GetBindPoint() const { return _BindPoint; }
        void SetBindPoint(bool value);

        RequiredClass GetStartClass() const { return _StartClass; }
        void SetStartClass(RequiredClass value);
    };
}
