#pragma once

#include "DBObject.h"
#include "ItemInfo.h"
#include "NPCInfo.h"
#include "MonsterInfo.h"
#include "MapInfo.h"
#include "../Enum.h"
#include <MirDB/DBBindingList.h>

namespace Library::SystemModels
{

    class QuestInfo;
    class QuestTask;

    class QuestReward : public DBObject
    {
        OBJECT_PROPERTY(QuestInfo*, Quest)
        OBJECT_PROPERTY(ItemInfo*, Item)
        PROPERTY(int, Amount)
        PROPERTY(bool, Choice)
        PROPERTY(bool, Bound)
        PROPERTY(int, Duration)
        PROPERTY(RequiredClass, Class)

    protected:
        void OnCreated() override;
    };

    class QuestRequirement : public DBObject
    {
        OBJECT_PROPERTY(QuestInfo*, Quest)
        PROPERTY(QuestRequirementType, Requirement)
        PROPERTY(int, IntParameter1)
        OBJECT_PROPERTY(QuestInfo*, QuestParameter)
        PROPERTY(RequiredClass, Class)
    };

    class QuestTaskMonsterDetails : public DBObject
    {
        OBJECT_PROPERTY(QuestTask*, Task)
        OBJECT_PROPERTY(MonsterInfo*, Monster)
        OBJECT_PROPERTY(MapInfo*, Map)
        PROPERTY(int, Chance)
        PROPERTY(int, Amount)
        PROPERTY(int, DropSet)

    protected:
        void OnCreated() override;
    };

    class QuestTask : public DBObject
    {
        OBJECT_PROPERTY(QuestInfo*, Quest)
        PROPERTY(QuestTaskType, Task)
        OBJECT_PROPERTY(ItemInfo*, ItemParameter)
        PROPERTY(std::string, MobDescription)
        PROPERTY(int, Amount)
        OBJECT_PROPERTY_PTR(DBBindingList<QuestTaskMonsterDetails>, MonsterDetails)
    };

    class QuestInfo : public DBObject
    {
        PROPERTY(std::string, QuestName)
        PROPERTY(std::string, AcceptText)
        PROPERTY(std::string, ProgressText)
        PROPERTY(std::string, CompletedText)
        PROPERTY(std::string, ArchiveText)

        OBJECT_PROPERTY_PTR(DBBindingList<QuestRequirement>, Requirements)
        OBJECT_PROPERTY(NPCInfo*, StartNPC)
        OBJECT_PROPERTY(NPCInfo*, FinishNPC)
        OBJECT_PROPERTY_PTR(DBBindingList<QuestReward>, Rewards)
        OBJECT_PROPERTY_PTR(DBBindingList<QuestTask>, Tasks)

    protected:
        void OnCreated() override;
    };

} // namespace Library::SystemModels
