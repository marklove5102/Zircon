#pragma once

#include "../Common/CSharpCompat.h"
#include "DXImageControl.h"

namespace Client::Controls
{
    class DXAnimatedControl : public DXImageControl
    {
    public:
        // Properties
        
        // Animated
        bool GetAnimated() const { return _Animated; }
        void SetAnimated(bool value);
        EventPtr<EventArgs> AnimatedChanged;
        virtual void OnAnimatedChanged(bool oValue, bool nValue);

        // BaseIndex
        int GetBaseIndex() const { return _BaseIndex; }
        void SetBaseIndex(int value);
        EventPtr<EventArgs> BaseIndexChanged;
        virtual void OnBaseIndexChanged(int oValue, int nValue);

        // FrameCount
        int GetFrameCount() const { return _FrameCount; }
        void SetFrameCount(int value);
        EventPtr<EventArgs> FrameCountChanged;
        virtual void OnFrameCountChanged(int oValue, int nValue);

        // AnimationDelay
        TimeSpan GetAnimationDelay() const { return _AnimationDelay; }
        void SetAnimationDelay(TimeSpan value);
        EventPtr<EventArgs> AnimationDelayChanged;
        virtual void OnAnimationDelayChanged(TimeSpan oValue, TimeSpan nValue);

        // Loop
        bool GetLoop() const { return _Loop; }
        void SetLoop(bool value);
        EventPtr<EventArgs> LoopChanged;
        virtual void OnLoopChanged(bool oValue, bool nValue);

        // Events
        EventPtr<EventArgs> AfterAnimation;
        EventPtr<EventArgs> AfterAnimationLoop;
        
        DateTime AnimationStart;

        // Constructor
        DXAnimatedControl();

        // Methods
        void Process() override;

        // Destructor
        ~DXAnimatedControl() override;

    protected:
        void Dispose(bool disposing) override;

    private:
        bool _Animated;
        int _BaseIndex;
        int _FrameCount;
        TimeSpan _AnimationDelay;
        bool _Loop;
    };
}
