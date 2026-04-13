#pragma once

#include "LibraryCore/Enums.h"
#include <drawing.h>
#include <vector>
#include <any>

namespace Client::Models
{

    class ObjectAction
    {
    public:
        MirAction Action;
        MirDirection Direction;
        Point Location;
        std::vector<std::any> Extra;

        ObjectAction(MirAction action, MirDirection direction, Point location, std::initializer_list<std::any> extra = {})
            : Action(action), Direction(direction), Location(location), Extra(extra)
        {
        }

        template<typename... Args>
        ObjectAction(MirAction action, MirDirection direction, Point location, Args&&... args)
            : Action(action), Direction(direction), Location(location)
        {
            (Extra.emplace_back(std::forward<Args>(args)), ...);
        }
    };

} // namespace Client::Models
