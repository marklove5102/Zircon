#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"

namespace Server::DBModels
{
    class MapInfo;

    class MovementInfo : public DBObject
    {
    private:
        MapInfo* _SourceMap = nullptr;
        int _SourceX = 0;
        int _SourceY = 0;
        MapInfo* _DestinationMap = nullptr;
        int _DestinationX = 0;
        int _DestinationY = 0;
        Library::MapIcon _MapIcon = Library::MapIcon::None;

    public:
        // Association("Movements")
        MapInfo* GetSourceMap() const { return _SourceMap; }
        void SetSourceMap(MapInfo* value);

        int GetSourceX() const { return _SourceX; }
        void SetSourceX(int value);

        int GetSourceY() const { return _SourceY; }
        void SetSourceY(int value);

        // Association("Movements")
        MapInfo* GetDestinationMap() const { return _DestinationMap; }
        void SetDestinationMap(MapInfo* value);

        int GetDestinationX() const { return _DestinationX; }
        void SetDestinationX(int value);

        int GetDestinationY() const { return _DestinationY; }
        void SetDestinationY(int value);

        Library::MapIcon GetMapIcon() const { return _MapIcon; }
        void SetMapIcon(Library::MapIcon value);
    };

} // namespace Server::DBModels
