#pragma once

#include <string>
#include "Common/CSharpCompat.h"

namespace MirDB
{
    // SessionMode enum - corresponds to C# [Flags] enum
    ENUM_CLASS(SessionMode, uint8_t,
        None = 0,
        System = 1,
        Users = 2,
        Both = System | Users
    )

    // Attribute base class
    class Attribute
    {
    public:
        virtual ~Attribute() = default;
    };

    // UserObject attribute - marks user data classes
    class UserObject : public Attribute
    {
    };

    // IgnoreProperty attribute - marks properties to ignore during serialization
    class IgnoreProperty : public Attribute
    {
    };

    // Association attribute - defines relationships between DBObjects
    class Association : public Attribute
    {
    public:
        std::string Identity;
        bool Aggregate;
        bool HasIdentity;
        bool HasAggregate;

        Association() : Aggregate(false), HasIdentity(false), HasAggregate(false) {}

        explicit Association(const std::string& identity)
            : Identity(identity), Aggregate(false), HasIdentity(true), HasAggregate(false) {}

        explicit Association(bool aggregate)
            : Identity(""), Aggregate(aggregate), HasIdentity(false), HasAggregate(true) {}

        Association(const std::string& identity, bool aggregate)
            : Identity(identity), Aggregate(aggregate), HasIdentity(true), HasAggregate(true) {}
    };

} // namespace MirDB
