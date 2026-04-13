#pragma once
#include "../DBObject.h"
#include "../../Library/Enum.h"

namespace Server::DBModels
{
    struct ClientMagicInfo;

    class MagicInfo : public DBObject
    {
    private:
        std::string _Name;
        Library::MagicType _Magic = Library::MagicType::None;
        Library::MirClass _Class = Library::MirClass::Warrior;
        Library::MagicSchool _School = Library::MagicSchool::None;
        int _Icon = 0;
        int _RequiredLevel = 0;
        int _MinBasePower = 0;
        int _MaxBasePower = 0;
        int _MinLevelPower = 0;
        int _MaxLevelPower = 0;
        int _BaseCost = 0;
        int _LevelCost = 0;
        int _BaseExperience = 0;
        int _ExperienceRate = 5;
        int _MaxLevel = 0;
        int _Delay = 0;

    public:
        std::string GetName() const { return _Name; }
        void SetName(const std::string& value);

        Library::MagicType GetMagic() const { return _Magic; }
        void SetMagic(Library::MagicType value);

        Library::MirClass GetClass() const { return _Class; }
        void SetClass(Library::MirClass value);

        Library::MagicSchool GetSchool() const { return _School; }
        void SetSchool(Library::MagicSchool value);

        int GetIcon() const { return _Icon; }
        void SetIcon(int value);

        int GetRequiredLevel() const { return _RequiredLevel; }
        void SetRequiredLevel(int value);

        int GetMinBasePower() const { return _MinBasePower; }
        void SetMinBasePower(int value);

        int GetMaxBasePower() const { return _MaxBasePower; }
        void SetMaxBasePower(int value);

        int GetMinLevelPower() const { return _MinLevelPower; }
        void SetMinLevelPower(int value);

        int GetMaxLevelPower() const { return _MaxLevelPower; }
        void SetMaxLevelPower(int value);

        int GetBaseCost() const { return _BaseCost; }
        void SetBaseCost(int value);

        int GetLevelCost() const { return _LevelCost; }
        void SetLevelCost(int value);

        int GetBaseExperience() const { return _BaseExperience; }
        void SetBaseExperience(int value);

        int GetExperienceRate() const { return _ExperienceRate; }
        void SetExperienceRate(int value);

        int GetMaxLevel() const { return _MaxLevel; }
        void SetMaxLevel(int value);

        int GetDelay() const { return _Delay; }
        void SetDelay(int value);

    protected:
        void OnCreated() override;

    public:
        ClientMagicInfo ToClientInfo();
    };

} // namespace Server::DBModels
