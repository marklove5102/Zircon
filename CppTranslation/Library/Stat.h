#pragma once

#include <cstdint>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>
#include <vector>
#include "Enum.h"

namespace Library
{

// StatDescription 属性 - C++ 中用结构体表示
enum class StatType
{
    None,
    Default,
    Min,
    Max,
    Percent,
    Text,
    Time,
    SpellPower,
    AttackElement,
    ElementResistance,
};

struct StatDescription
{
    std::string Title;
    std::string Format;
    StatType Mode;
    Stat MinStat = Stat::None;
    Stat MaxStat = Stat::None;
};

// Stat 枚举（从 C# 的 enum 转换）
enum class Stat : int32_t
{
    // Base stats (Mode = None)
    BaseHealth,
    BaseMana,

    // Primary stats
    Health,
    Mana,

    // AC (Armor Class)
    MinAC,
    MaxAC,
    
    // MR (Magic Resistance)
    MinMR,
    MaxMR,
    
    // DC (Damage Class)
    MinDC,
    MaxDC,
    
    // MC (Magic Class - Nature)
    MinMC,
    MaxMC,
    
    // SC (Spirit Class)
    MinSC,
    MaxSC,

    // Combat stats
    Accuracy,
    Agility,
    AttackSpeed,

    // Utility stats
    Light,
    Strength,  // Also known as Inten (Intensity)
    Luck,      // does nothing at the moment

    // Elemental Attack/Resistance
    FireAttack,
    FireResistance,

    IceAttack,
    IceResistance,

    LightningAttack,
    LightningResistance,

    WindAttack,
    WindResistance,

    HolyAttack,
    HolyResistance,

    DarkAttack,
    DarkResistance,

    PhantomAttack,
    PhantomResistance,

    // Affinity
    FireAffinity,
    IceAffinity,
    LightningAffinity,
    WindAffinity,
    HolyAffinity,
    DarkAffinity,
    PhantomAffinity,

    // Special stats
    PhysicalResistance,

    PoisonResistance,
    PoisonRecovery,

    HealthRecovery,
    ManaRecovery,

    CriticalHitChance,
    CriticalHitDamage,

    BlockChance,
    BlockDamage,

    ParryChance,
    ParryDamage,

    SkillBonus,
    SkillPenalty,

    DamageBonus,
    DamageReduction,

    MagicBonus,
    MagicReduction,

    PotionBonus,
    PotionPenalty,

    ExperienceBonus,
    GoldBonus,

    DropRateBonus,
    DropRatePenalty,

    MoveSpeed,
    MountSpeed,

    MaxWeight,
    BagWeight,

    WearWeight,
    HandWeight,

    FreezingPoisoning,
    Poisoning,
    Blessing,

    Level,
    MaxLevel,

    CompanionLevel,
    MaxCompanionLevel,

    RebirthLevel,
    MaxRebirthLevel,

    ItemDropRate,
    ItemReviveTime,

    WeaponElement,
    WeaponStrong,
    WeaponLuck,

    ArmourElement,
    ArmourStrong,
    ArmourLuck,

    HelmetElement,
    HelmetStrong,
    HelmetLuck,

    NecklaceElement,
    NecklaceStrong,
    NecklaceLuck,

    BraceletElement,
    BraceletStrong,
    BraceletLuck,

    RingElement,
    RingStrong,
    RingLuck,

    ShoesElement,
    ShoesStrong,
    ShoesLuck,

    // Helper constants for min/max stat pairs
    // (在 C++ 中作为单独的枚举值，通过代码关联)
};

// Stat 描述信息表
inline const StatDescription& GetStatDescription(Stat stat)
{
    static const std::map<Stat, StatDescription> descriptions = {
        {Stat::BaseHealth, {"Base Health", "{0:+#0;-#0;#0}", StatType::None}},
        {Stat::BaseMana, {"Base Mana", "{0:+#0;-#0;#0}", StatType::None}},
        
        {Stat::Health, {"Health", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Mana, {"Mana", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::MinAC, {"AC", "{0}-0", StatType::Min, Stat::MinAC, Stat::MaxAC}},
        {Stat::MaxAC, {"AC", "{0}-{1}", StatType::Max, Stat::MinAC, Stat::MaxAC}},
        {Stat::MinMR, {"MR", "{0}-0", StatType::Min, Stat::MinMR, Stat::MaxMR}},
        {Stat::MaxMR, {"MR", "{0}-{1}", StatType::Max, Stat::MinMR, Stat::MaxMR}},
        {Stat::MinDC, {"DC", "{0}-0", StatType::Min, Stat::MinDC, Stat::MaxDC}},
        {Stat::MaxDC, {"DC", "{0}-{1}", StatType::Max, Stat::MinDC, Stat::MaxDC}},
        {Stat::MinMC, {"SP (Nature)", "{0}-0", StatType::SpellPower, Stat::MinMC, Stat::MaxMC}},
        {Stat::MaxMC, {"SP (Nature)", "{0}-{1}", StatType::SpellPower, Stat::MinMC, Stat::MaxMC}},
        {Stat::MinSC, {"SP (Spirit)", "{0}-0", StatType::SpellPower, Stat::MinSC, Stat::MaxSC}},
        {Stat::MaxSC, {"SP (Spirit)", "{0}-{1}", StatType::SpellPower, Stat::MinSC, Stat::MaxSC}},
        
        {Stat::Accuracy, {"Accuracy", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Agility, {"Agility", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::AttackSpeed, {"Attack Speed", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::Light, {"Light Radius", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Strength, {"Strength", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Luck, {"Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::FireAttack, {"Fire", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::FireResistance, {"Fire", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::IceAttack, {"Ice", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::IceResistance, {"Ice", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::LightningAttack, {"Lightning", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::LightningResistance, {"Lightning", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::WindAttack, {"Wind", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::WindResistance, {"Wind", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::HolyAttack, {"Holy", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::HolyResistance, {"Holy", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::DarkAttack, {"Dark", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::DarkResistance, {"Dark", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::PhantomAttack, {"Phantom", "{0:+#0;-#0;#0}", StatType::AttackElement}},
        {Stat::PhantomResistance, {"Phantom", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::FireAffinity, {"Fire Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::IceAffinity, {"Ice Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::LightningAffinity, {"Lightning Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::WindAffinity, {"Wind Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::HolyAffinity, {"Holy Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::DarkAffinity, {"Dark Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::PhantomAffinity, {"Phantom Affinity", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::PhysicalResistance, {"Physical", "{0:+#0;-#0;#0}", StatType::ElementResistance}},
        
        {Stat::PoisonResistance, {"Poison Resistance", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::PoisonRecovery, {"Poison Recovery", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::HealthRecovery, {"Health Recovery", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::ManaRecovery, {"Mana Recovery", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::CriticalHitChance, {"Critical Hit Chance", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::CriticalHitDamage, {"Critical Hit Damage", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::BlockChance, {"Block Chance", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::BlockDamage, {"Block Damage", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::ParryChance, {"Parry Chance", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::ParryDamage, {"Parry Damage", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::SkillBonus, {"Skill Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::SkillPenalty, {"Skill Penalty", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::DamageBonus, {"Damage Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::DamageReduction, {"Damage Reduction", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::MagicBonus, {"Magic Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::MagicReduction, {"Magic Reduction", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::PotionBonus, {"Potion Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::PotionPenalty, {"Potion Penalty", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::ExperienceBonus, {"Experience Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::GoldBonus, {"Gold Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::DropRateBonus, {"Drop Rate Bonus", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::DropRatePenalty, {"Drop Rate Penalty", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::MoveSpeed, {"Move Speed", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::MountSpeed, {"Mount Speed", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::MaxWeight, {"Max Weight", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::BagWeight, {"Bag Weight", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::WearWeight, {"Wear Weight", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::HandWeight, {"Hand Weight", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::FreezingPoisoning, {"Freezing/Poisoning", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Poisoning, {"Poisoning", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::Blessing, {"Blessing", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::Level, {"Level", "{0}", StatType::Default}},
        {Stat::MaxLevel, {"Max Level", "{0}", StatType::Default}},
        
        {Stat::CompanionLevel, {"Companion Level", "{0}", StatType::Default}},
        {Stat::MaxCompanionLevel, {"Max Companion Level", "{0}", StatType::Default}},
        
        {Stat::RebirthLevel, {"Rebirth Level", "{0}", StatType::Default}},
        {Stat::MaxRebirthLevel, {"Max Rebirth Level", "{0}", StatType::Default}},
        
        {Stat::ItemDropRate, {"Item Drop Rate", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::ItemReviveTime, {"Item Revive Time", "{0}", StatType::Time}},
        
        {Stat::WeaponElement, {"Weapon Element", "{0}", StatType::Default}},
        {Stat::WeaponStrong, {"Weapon Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::WeaponLuck, {"Weapon Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::ArmourElement, {"Armour Element", "{0}", StatType::Default}},
        {Stat::ArmourStrong, {"Armour Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::ArmourLuck, {"Armour Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::HelmetElement, {"Helmet Element", "{0}", StatType::Default}},
        {Stat::HelmetStrong, {"Helmet Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::HelmetLuck, {"Helmet Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::NecklaceElement, {"Necklace Element", "{0}", StatType::Default}},
        {Stat::NecklaceStrong, {"Necklace Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::NecklaceLuck, {"Necklace Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::BraceletElement, {"Bracelet Element", "{0}", StatType::Default}},
        {Stat::BraceletStrong, {"Bracelet Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::BraceletLuck, {"Bracelet Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::RingElement, {"Ring Element", "{0}", StatType::Default}},
        {Stat::RingStrong, {"Ring Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::RingLuck, {"Ring Luck", "{0:+#0;-#0;#0}", StatType::Default}},
        
        {Stat::ShoesElement, {"Shoes Element", "{0}", StatType::Default}},
        {Stat::ShoesStrong, {"Shoes Strong", "{0:+#0;-#0;#0}", StatType::Default}},
        {Stat::ShoesLuck, {"Shoes Luck", "{0:+#0;-#0;#0}", StatType::Default}},
    };

    static const StatDescription empty{"", "", StatType::None};
    auto it = descriptions.find(stat);
    return it != descriptions.end() ? it->second : empty;
}

// Stats 类 - 对应 C# 的 sealed class Stats
class Stats
{
public:
    std::map<Stat, int32_t> Values;

    // 索引操作符：this[Stat stat]
    int32_t& operator[](Stat stat)
    {
        return Values[stat];  // 如果不存在会自动创建并初始化为 0
    }

    int32_t Get(Stat stat) const
    {
        auto it = Values.find(stat);
        return it != Values.end() ? it->second : 0;
    }

    void Set(Stat stat, int32_t value)
    {
        if (value == 0)
        {
            Values.erase(stat);
        }
        else
        {
            Values[stat] = value;
        }
    }

    // Count 属性
    int32_t Count() const
    {
        int32_t sum = 0;
        for (const auto& pair : Values)
        {
            sum += std::abs(pair.second);
        }
        return sum;
    }

    // 构造函数
    Stats() = default;

    Stats(const Stats& other)
    {
        for (const auto& pair : other.Values)
        {
            Set(pair.first, Get(pair.first) + pair.second);
        }
    }

    // Add 方法
    void Add(const Stats& stats, bool addElements = true)
    {
        for (const auto& pair : stats.Values)
        {
            switch (pair.first)
            {
                case Stat::FireAttack:
                case Stat::LightningAttack:
                case Stat::IceAttack:
                case Stat::WindAttack:
                case Stat::HolyAttack:
                case Stat::DarkAttack:
                case Stat::PhantomAttack:
                    if (addElements)
                        Set(pair.first, Get(pair.first) + pair.second);
                    break;
                case Stat::ItemReviveTime:
                    if (pair.second == 0) continue;

                    if (Get(pair.first) == 0)
                        Set(pair.first, pair.second);
                    else
                        Set(pair.first, std::min(Get(pair.first), pair.second));
                    break;
                default:
                    Set(pair.first, Get(pair.first) + pair.second);
                    break;
            }
        }
    }

    // Clear 方法
    void Clear()
    {
        Values.clear();
    }

    // Compare 方法
    bool Compare(const Stats& s2) const
    {
        if (Values.size() != s2.Values.size()) return false;

        for (const auto& value : Values)
        {
            if (s2.Get(value.first) != value.second) return false;
        }

        return true;
    }

    // HasElementalWeakness 方法
    bool HasElementalWeakness() const
    {
        return Get(Stat::FireResistance) <= 0 && 
               Get(Stat::IceResistance) <= 0 && 
               Get(Stat::LightningResistance) <= 0 && 
               Get(Stat::WindResistance) <= 0 &&
               Get(Stat::HolyResistance) <= 0 && 
               Get(Stat::DarkResistance) <= 0 &&
               Get(Stat::PhantomResistance) <= 0 && 
               Get(Stat::PhysicalResistance) <= 0;
    }

    // GetWeaponElement 方法
    Stat GetWeaponElement() const
    {
        Element weaponElement = static_cast<Element>(Get(Stat::WeaponElement));
        switch (weaponElement)
        {
            case Element::Fire: return Stat::FireAttack;
            case Element::Ice: return Stat::IceAttack;
            case Element::Lightning: return Stat::LightningAttack;
            case Element::Wind: return Stat::WindAttack;
            case Element::Holy: return Stat::HolyAttack;
            case Element::Dark: return Stat::DarkAttack;
            case Element::Phantom: return Stat::PhantomAttack;
            default: break;
        }

        for (const auto& pair : Values)
        {
            switch (pair.first)
            {
                case Stat::FireAttack: return Stat::FireAttack;
                case Stat::IceAttack: return Stat::IceAttack;
                case Stat::LightningAttack: return Stat::LightningAttack;
                case Stat::WindAttack: return Stat::WindAttack;
                case Stat::HolyAttack: return Stat::HolyAttack;
                case Stat::DarkAttack: return Stat::DarkAttack;
                case Stat::PhantomAttack: return Stat::PhantomAttack;
                default: break;
            }
        }

        return Stat::None;
    }

    // GetWeaponElementValue 方法
    int32_t GetWeaponElementValue() const
    {
        return Get(Stat::FireAttack) + Get(Stat::IceAttack) + 
               Get(Stat::LightningAttack) + Get(Stat::WindAttack) + 
               Get(Stat::HolyAttack) + Get(Stat::DarkAttack) + 
               Get(Stat::PhantomAttack);
    }

    // GetElementValue 方法
    int32_t GetElementValue(Element element) const
    {
        switch (element)
        {
            case Element::Fire: return Get(Stat::FireAttack);
            case Element::Ice: return Get(Stat::IceAttack);
            case Element::Lightning: return Get(Stat::LightningAttack);
            case Element::Wind: return Get(Stat::WindAttack);
            case Element::Holy: return Get(Stat::HolyAttack);
            case Element::Dark: return Get(Stat::DarkAttack);
            case Element::Phantom: return Get(Stat::PhantomAttack);
            default: return 0;
        }
    }

    // GetAffinityValue 方法
    int32_t GetAffinityValue(Element element) const
    {
        switch (element)
        {
            case Element::Fire: return Get(Stat::FireAffinity);
            case Element::Ice: return Get(Stat::IceAffinity);
            case Element::Lightning: return Get(Stat::LightningAffinity);
            case Element::Wind: return Get(Stat::WindAffinity);
            case Element::Holy: return Get(Stat::HolyAffinity);
            case Element::Dark: return Get(Stat::DarkAffinity);
            case Element::Phantom: return Get(Stat::PhantomAffinity);
            default: return 0;
        }
    }

    // GetResistanceValue 方法
    int32_t GetResistanceValue(Element element) const
    {
        switch (element)
        {
            case Element::Fire: return Get(Stat::FireResistance);
            case Element::Ice: return Get(Stat::IceResistance);
            case Element::Lightning: return Get(Stat::LightningResistance);
            case Element::Wind: return Get(Stat::WindResistance);
            case Element::Holy: return Get(Stat::HolyResistance);
            case Element::Dark: return Get(Stat::DarkResistance);
            case Element::Phantom: return Get(Stat::PhantomResistance);
            case Element::None: return Get(Stat::PhysicalResistance);
            default: return 0;
        }
    }

    // GetAffinityElement 方法
    Element GetAffinityElement() const
    {
        std::vector<Element> elements;

        if (Get(Stat::FireAffinity) > 0) elements.push_back(Element::Fire);
        if (Get(Stat::IceAffinity) > 0) elements.push_back(Element::Ice);
        if (Get(Stat::LightningAffinity) > 0) elements.push_back(Element::Lightning);
        if (Get(Stat::WindAffinity) > 0) elements.push_back(Element::Wind);
        if (Get(Stat::HolyAffinity) > 0) elements.push_back(Element::Holy);
        if (Get(Stat::DarkAffinity) > 0) elements.push_back(Element::Dark);
        if (Get(Stat::PhantomAffinity) > 0) elements.push_back(Element::Phantom);

        if (elements.empty()) return Element::None;

        // 使用 Globals.Random (需要引用 Globals.h)
        // 这里暂时返回第一个元素
        return elements[0];
    }
};

} // namespace Library
