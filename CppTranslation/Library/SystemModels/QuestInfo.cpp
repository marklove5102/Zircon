#include "QuestInfo.h"

namespace Library::SystemModels
{

    void QuestReward::OnCreated()
    {
        DBObject::OnCreated();

        Amount = 1;
        Class = RequiredClass::All;
    }

    void QuestTaskMonsterDetails::OnCreated()
    {
        DBObject::OnCreated();

        Chance = 1;
        Amount = 1;
    }

    void QuestInfo::OnCreated()
    {
        DBObject::OnCreated();

        auto requirement = Requirements->AddNew();
        requirement->Requirement = QuestRequirementType::HaveNotCompleted;
        requirement->Quest = this;
        requirement->QuestParameter = this;
    }

} // namespace Library::SystemModels
