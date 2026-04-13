#pragma once

#include "LibraryCore/Enums.h"
#include "Client/Models/MapObject.h"
#include <drawing.h>
#include <vector>
#include <functional>
#include <chrono>

namespace Library { class MirLibrary; }
namespace Client::Models::Particles { class ParticleEmitter; }

namespace Client::Models
{

    enum class DrawType
    {
        Floor,
        Object,
        Final
    };

    class MirEffect
    {
    public:
        MapObject* Target = nullptr;
        Point MapTarget{};

        Library::MirLibrary* Library = nullptr;

        std::chrono::system_clock::time_point StartTime;
        int StartIndex = 0;
        int FrameCount = 0;
        std::vector<std::chrono::milliseconds> Delays;

        int FrameIndex
        {
            get { return _FrameIndex; }
            set
            {
                if (_FrameIndex == value) return;
                _FrameIndex = value;
                if (FrameIndexAction) FrameIndexAction();
            }
        }

        Color DrawColour = Color::White;
        bool Blend = false;
        bool Reversed = false;
        float Opacity = 1.0f;
        float BlendRate = 0.7f;
        bool UseOffSet = true;
        bool Loop = false;

        Particles::ParticleEmitter* _particleEmitter = nullptr;

        int DrawX
        {
            get { return _DrawX; }
            set
            {
                if (_DrawX == value) return;
                _DrawX = value;
                // GameScene.Game.MapControl.TextureValid = false; // Requires forward declaration
            }
        }

        int DrawY
        {
            get { return _DrawY; }
            set
            {
                if (_DrawY == value) return;
                _DrawY = value;
                // GameScene.Game.MapControl.TextureValid = false; // Requires forward declaration
            }
        }

        int DrawFrame
        {
            get { return _DrawFrame; }
            set
            {
                if (_DrawFrame == value) return;
                _DrawFrame = value;
                // GameScene.Game.MapControl.TextureValid = false; // Requires forward declaration
                if (FrameAction) FrameAction();
            }
        }

        DrawType DrawType = DrawType::Object;

        int Skip = 0;
        MirDirection Direction = MirDirection::Up;

        std::vector<Color> LightColours;
        int StartLight = 0, EndLight = 0;

        float FrameLight();
        Color FrameLightColour() { return LightColours[FrameIndex]; }
        Point CurrentLocation() const { return Target ? Target->CurrentLocation : MapTarget; }
        Point MovingOffSet() const { return Target ? Target->MovingOffSet : Point{}; }

        std::function<void()> CompleteAction;
        std::function<void()> FrameAction;
        std::function<void()> FrameIndexAction;

        Point AdditionalOffSet{};

        std::chrono::milliseconds TotalDuration() const;

        MirEffect(int startIndex, int frameCount, std::chrono::milliseconds frameDelay, 
                  LibraryFile file, int startLight, int endLight, Color lightColour);

        virtual void Process();
        virtual void Draw();
        virtual void Remove();

    protected:
        virtual int GetFrame();

    private:
        int _FrameIndex = 0;
        int _DrawX = 0;
        int _DrawY = 0;
        int _DrawFrame = 0;
    };

} // namespace Client::Models
