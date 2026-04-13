#pragma once

#include "MirEffect.h"
#include "LibraryCore/Enums.h"
#include <drawing.h>

namespace Client::Models::Particles { class ParticleEmitter; }

namespace Client::Models
{

    class MirProjectile : public MirEffect
    {
    public:
        Point Origin{};
        int Speed = 0;
        bool Explode = false;
        int Delay = 0;
        int Direction16 = 0;
        bool Has16Directions = false;

        MirProjectile(int startIndex, int frameCount, std::chrono::milliseconds frameDelay, 
                      LibraryFile file, int startlight, int endLight, Color lightColour, 
                      Point origin, Particles::ParticleEmitter* particleEmitter = nullptr);

        void Process() override;
        void Remove() override;

    protected:
        int GetFrame() override;
    };

} // namespace Client::Models
