#pragma once

#include "../Common/CSharpCompat.h"
#include "DBObject.h"

namespace Library::MirDB
{
    class DBRelationshipTargets;

    class DBRelationship
    {
    public:
        Type<Type>* Type;
        std::unordered_map<int, DBRelationshipTargets*> LinkTargets;

        DBRelationship(Type<Type>* type);
        ~DBRelationship();

        void ConsumeKeys(Session* session);
    };

    class DBRelationshipTargets
    {
    public:
        std::unordered_map<System::Reflection::PropertyInfo*, ConcurrentQueue<DBObject*>> PropertyTargets;
    };

} // namespace Library::MirDB
