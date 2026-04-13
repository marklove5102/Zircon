#pragma once
#include "DBObject.h"
#include "../Library/Enum.h"

namespace Server::DBModels
{
    class SetInfo;

    public sealed class SetInfoStats : public DBObject
    {
    private:
        SetInfo* _Set = nullptr;
        Stat _Stat{};
        int _Amount = 0;
        RequiredClass _Class = RequiredClass::All;
        int _Level = 0;

    public:
        // Association("SetStats")
        SetInfo* GetSet() const { return _Set; }
        void SetSet(SetInfo* value);

        Stat GetStat() const { return _Stat; }
        void SetStat(Stat value);

        int GetAmount() const { return _Amount; }
        void SetAmount(int value);

        RequiredClass GetClass() const { return _Class; }
        void SetClass(RequiredClass value);

        int GetLevel() const { return _Level; }
        void SetLevel(int value);

    protected:
        void OnCreated() override;
    };
}
