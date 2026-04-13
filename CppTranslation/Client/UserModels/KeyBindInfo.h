#pragma once

#include "LibraryCore/Enums.h"
#include "MirDB/DBObject.h"
#include <string>

namespace Client::UserModels
{

    [UserObject]
    class KeyBindInfo : public DBObject
    {
        PROPERTY(std::string, Category)
        PROPERTY(KeyBindAction, Action)

        PROPERTY(bool, Control1)
        PROPERTY(bool, Alt1)
        PROPERTY(bool, Shift1)
        PROPERTY(Keys, Key1)

        PROPERTY(bool, Control2)
        PROPERTY(bool, Shift2)
        PROPERTY(bool, Alt2)
        PROPERTY(Keys, Key2)
    };

} // namespace Client::UserModels
