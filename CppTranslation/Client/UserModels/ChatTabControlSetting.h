#pragma once

#include "ChatTabPageSetting.h"
#include "MirDB/DBObject.h"
#include "MirDB/DBBindingList.h"
#include <drawing.h>

namespace Client::UserModels
{

    [UserObject]
    class ChatTabControlSetting : public DBObject
    {
        PROPERTY(Size, Resolution)
        PROPERTY(Point, Location)
        PROPERTY(Size, Size)

        PROPERTY_PTR(ChatTabPageSetting*, SelectedPage)

        [Association("Controls", true)]
        DBBindingList<ChatTabPageSetting*> Controls;
    };

} // namespace Client::UserModels
