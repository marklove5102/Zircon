#include "DXAnimatedControl.h"

namespace Client::Controls
{
    DXAnimatedControl::DXAnimatedControl()
    {
        _Animated = false;
        _BaseIndex = -1;
        _FrameCount = 0;
        _AnimationDelay = TimeSpan::Zero();
        _Loop = false;
        
        Animated = true;
        BaseIndex = -1;
        Loop = true;
        
        AnimationStart = DateTime::MinValue();
    }

    DXAnimatedControl::~DXAnimatedControl()
    {
        Dispose(true);
    }

    void DXAnimatedControl::SetAnimated(bool value)
    {
        if (_Animated == value) return;

        bool oldValue = _Animated;
        _Animated = value;

        OnAnimatedChanged(oldValue, value);
    }

    void DXAnimatedControl::OnAnimatedChanged(bool oValue, bool nValue)
    {
        if (!GetAnimated()) SetIndex(GetBaseIndex());

        Process();

        if (AnimatedChanged) AnimatedChanged->Invoke(this, EventArgs::Empty());
    }

    void DXAnimatedControl::SetBaseIndex(int value)
    {
        if (_BaseIndex == value) return;

        int oldValue = _BaseIndex;
        _BaseIndex = value;

        OnBaseIndexChanged(oldValue, value);
    }

    void DXAnimatedControl::OnBaseIndexChanged(int oValue, int nValue)
    {
        if (!GetAnimated()) SetIndex(GetBaseIndex());

        Process();

        if (BaseIndexChanged) BaseIndexChanged->Invoke(this, EventArgs::Empty());
    }

    void DXAnimatedControl::SetFrameCount(int value)
    {
        if (_FrameCount == value) return;

        int oldValue = _FrameCount;
        _FrameCount = value;

        OnFrameCountChanged(oldValue, value);
    }

    void DXAnimatedControl::OnFrameCountChanged(int oValue, int nValue)
    {
        if (FrameCountChanged) FrameCountChanged->Invoke(this, EventArgs::Empty());
    }

    void DXAnimatedControl::SetAnimationDelay(TimeSpan value)
    {
        if (_AnimationDelay == value) return;

        TimeSpan oldValue = _AnimationDelay;
        _AnimationDelay = value;

        OnAnimationDelayChanged(oldValue, value);
    }

    void DXAnimatedControl::OnAnimationDelayChanged(TimeSpan oValue, TimeSpan nValue)
    {
        Process();

        if (AnimationDelayChanged) AnimationDelayChanged->Invoke(this, EventArgs::Empty());
    }

    void DXAnimatedControl::SetLoop(bool value)
    {
        if (_Loop == value) return;

        bool oldValue = _Loop;
        _Loop = value;

        OnLoopChanged(oldValue, value);
    }

    void DXAnimatedControl::OnLoopChanged(bool oValue, bool nValue)
    {
        if (LoopChanged) LoopChanged->Invoke(this, EventArgs::Empty());
    }

    void DXAnimatedControl::Process()
    {
        DXImageControl::Process();

        if (!GetIsVisible()) return;

        if (!GetAnimated() || GetAnimationDelay() == TimeSpan::Zero() || GetFrameCount() == 0) return;

        if (AnimationStart == DateTime::MinValue()) AnimationStart = CEnvir::Now();

        TimeSpan time = CEnvir::Now() - AnimationStart;
        int64_t frameTime = GetAnimationDelay().Ticks / GetFrameCount();
        int frame = static_cast<int>(time.Ticks / frameTime) % GetFrameCount();
        SetIndex(GetBaseIndex() + frame);

        if (time < GetAnimationDelay()) return;

        if (AfterAnimationLoop) AfterAnimationLoop->Invoke(this, EventArgs::Empty());

        if (!GetLoop())
        {
            SetAnimated(false);
            SetIndex(GetBaseIndex() + GetFrameCount() - 1);

            if (AfterAnimation) AfterAnimation->Invoke(this, EventArgs::Empty());
        }
    }

    void DXAnimatedControl::Dispose(bool disposing)
    {
        DXImageControl::Dispose(disposing);

        if (disposing)
        {
            _Animated = false;
            _BaseIndex = 0;
            _FrameCount = 0;
            _AnimationDelay = TimeSpan::Zero();
            _Loop = false;

            AnimatedChanged.reset();
            BaseIndexChanged.reset();
            FrameCountChanged.reset();
            AnimationDelayChanged.reset();
            LoopChanged.reset();

            AfterAnimation.reset();
            AnimationStart = DateTime::MinValue();
        }
    }
}
