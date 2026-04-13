#include "MapRegion.h"
#include "MapInfo.h"

namespace Library::SystemModels
{

std::string MapRegion::GetServerDescription() const
{
    if (Map != nullptr)
        return Map->Description + " - " + Description;
    return Description;
}

std::set<Point> MapRegion::GetPoints(int width)
{
    std::set<Point> points;
    
    if (!BitRegion.empty())
    {
        for (size_t i = 0; i < BitRegion.size(); ++i)
        {
            if (BitRegion[i])
                points.emplace_back(i % width, i / width);
        }
    }
    else if (!PointRegion.empty())
    {
        for (const auto& p : PointRegion)
            points.insert(p);
    }
    
    return points;
}

void MapRegion::CreatePoints(int width)
{
    PointList.clear();
    
    if (!BitRegion.empty())
    {
        if (width == 0) return;
        
        for (size_t i = 0; i < BitRegion.size(); ++i)
        {
            if (BitRegion[i])
                PointList.emplace_back(i % width, i / width);
        }
    }
    else if (!PointRegion.empty())
    {
        for (const auto& p : PointRegion)
            PointList.push_back(p);
    }
}

} // namespace Library::SystemModels
