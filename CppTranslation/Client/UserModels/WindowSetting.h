#pragma once

#include "LibraryCore/Enums.h"
#include "MirDB/DBObject.h"
#include <drawing.h>

namespace Client::UserModels
{

    [UserObject]
    class WindowSetting : public DBObject
    {
        PROPERTY(WindowType, Window)
        PROPERTY(Size, Resolution)
        PROPERTY(bool, Visible)
        PROPERTY(Point, Location)
        PROPERTY(Size, Size)
        PROPERTY(int, Extra)
        PROPERTY(int, Extra2)
    };

} // namespace Client::UserModels
