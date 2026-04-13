#include "DBRelationship.h"
#include "Session.h"

namespace Library::MirDB
{
    DBRelationship::DBRelationship(Type<Type>* type)
        : Type(type)
    {
    }

    DBRelationship::~DBRelationship()
    {
        for (auto& pair : LinkTargets)
        {
            delete pair.second;
        }
        LinkTargets.clear();
    }

    void DBRelationship::ConsumeKeys(Session* session)
    {
        for (auto& pair : LinkTargets)
        {
            DBObject* linkOb = session->GetObject(Type, pair.first);

            for (auto& targetPair : pair.second->PropertyTargets)
            {
                while (!targetPair.second->IsEmpty())
                {
                    DBObject* targetOb = nullptr;
                    if (targetPair.second->TryDequeue(targetOb))
                    {
                        targetPair.first->SetValue(targetOb, linkOb);
                    }
                }
            }
            pair.second->PropertyTargets.clear();
        }
        LinkTargets.clear();
    }

} // namespace Library::MirDB
