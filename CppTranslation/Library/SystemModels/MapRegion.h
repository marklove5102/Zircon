#pragma once
#include "MirDB/DBObject.h"
#include <vector>
#include <set>

namespace Library::SystemModels
{
    class MapInfo;

    public sealed class MapRegion : public DBObject
    {
    public:
        PROPERTY(MapInfo*, Map);
        PROPERTY(std::string, Description);
        // BitArray 用 std::vector<bool> 替代
        PROPERTY(std::vector<bool>, BitRegion);
        // Point[] 用 std::vector<Point> 替代
        PROPERTY(std::vector<Point>, PointRegion);
        
        [IgnoreProperty]
        std::string GetServerDescription() const;
        
        PROPERTY(int, Size);
        
        std::vector<Point> PointList;
        
        std::set<Point> GetPoints(int width);
        void CreatePoints(int width);
    };
}
