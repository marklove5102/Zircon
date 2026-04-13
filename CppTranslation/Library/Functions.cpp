#include "Functions.h"

namespace Library
{
    TimeSpan Functions::Max(TimeSpan value1, TimeSpan value2)
    {
        return value1 > value2 ? value1 : value2;
    }

    TimeSpan Functions::Min(TimeSpan value1, TimeSpan value2)
    {
        return value1 < value2 ? value1 : value2;
    }

    Element Functions::GetElement(const Stats& stats)
    {
        Element attackElement = Element::None;
        int value = 0;

        if (stats[Stat::FireAttack] > value)
        {
            attackElement = Element::Fire;
            value = stats[Stat::FireAttack];
        }

        if (stats[Stat::IceAttack] > value)
        {
            attackElement = Element::Ice;
            value = stats[Stat::IceAttack];
        }

        if (stats[Stat::LightningAttack] > value)
        {
            attackElement = Element::Lightning;
            value = stats[Stat::LightningAttack];
        }

        if (stats[Stat::WindAttack] > value)
        {
            attackElement = Element::Wind;
            value = stats[Stat::WindAttack];
        }

        if (stats[Stat::HolyAttack] > value)
        {
            attackElement = Element::Holy;
            value = stats[Stat::HolyAttack];
        }

        if (stats[Stat::DarkAttack] > value)
        {
            attackElement = Element::Dark;
            value = stats[Stat::DarkAttack];
        }

        if (stats[Stat::PhantomAttack] > value)
            attackElement = Element::Phantom;

        return attackElement;
    }

    int Functions::GetElement(const Stats& stats, Element& element)
    {
        element = Element::None;
        int value = 0;

        if (stats[Stat::FireAttack] > value)
        {
            element = Element::Fire;
            value = stats[Stat::FireAttack];
        }

        if (stats[Stat::IceAttack] > value)
        {
            element = Element::Ice;
            value = stats[Stat::IceAttack];
        }

        if (stats[Stat::LightningAttack] > value)
        {
            element = Element::Lightning;
            value = stats[Stat::LightningAttack];
        }

        if (stats[Stat::WindAttack] > value)
        {
            element = Element::Wind;
            value = stats[Stat::WindAttack];
        }

        if (stats[Stat::HolyAttack] > value)
        {
            element = Element::Holy;
            value = stats[Stat::HolyAttack];
        }

        if (stats[Stat::DarkAttack] > value)
        {
            element = Element::Dark;
            value = stats[Stat::DarkAttack];
        }

        if (stats[Stat::PhantomAttack] > value)
        {
            element = Element::Phantom;
            value = stats[Stat::PhantomAttack];
        }

        return value;
    }
}
