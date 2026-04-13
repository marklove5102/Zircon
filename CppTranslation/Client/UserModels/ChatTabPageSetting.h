#pragma once

#include "ChatTabControlSetting.h"
#include "MirDB/DBObject.h"
#include <string>

namespace Client::UserModels
{

    [UserObject]
    class ChatTabPageSetting : public DBObject
    {
        [Association("Controls")]
        PROPERTY_PTR(ChatTabControlSetting*, Parent)

        PROPERTY(std::string, Name)

        PROPERTY(bool, Transparent)
        PROPERTY(bool, Alert)
        PROPERTY(bool, HideTab)
        PROPERTY(bool, ReverseList)
        PROPERTY(bool, CleanUp)
        PROPERTY(bool, FadeOut)

        PROPERTY(bool, LocalChat)
        PROPERTY(bool, WhisperChat)
        PROPERTY(bool, GroupChat)
        PROPERTY(bool, GuildChat)
        PROPERTY(bool, ShoutChat)
        PROPERTY(bool, GlobalChat)
        PROPERTY(bool, ObserverChat)
        PROPERTY(bool, HintChat)
        PROPERTY(bool, SystemChat)
        PROPERTY(bool, GainsChat)
    };

} // namespace Client::UserModels
