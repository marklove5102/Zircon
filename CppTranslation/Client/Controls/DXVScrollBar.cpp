#include "DXVScrollBar.h"
#include "CEnvir.h"
#include <SystemInformation.h>
#include <cmath>

namespace Client::Controls
{
    // DXVScrollBar Implementation

    int DXVScrollBar::GetValue() const
    {
        return _Value;
    }

    void DXVScrollBar::SetValue(int value)
    {
        if (_Value == value)
            return;

        int oldValue = _Value;
        _Value = value;

        OnValueChanged(oldValue, value);
    }

    int DXVScrollBar::GetMaxValue() const
    {
        return _MaxValue;
    }

    void DXVScrollBar::SetMaxValue(int value)
    {
        if (_MaxValue == value)
            return;

        int oldValue = _MaxValue;
        _MaxValue = value;

        OnMaxValueChanged(oldValue, value);
    }

    int DXVScrollBar::GetMinValue() const
    {
        return _MinValue;
    }

    void DXVScrollBar::SetMinValue(int value)
    {
        if (_MinValue == value)
            return;

        int oldValue = _MinValue;
        _MinValue = value;

        OnMinValueChanged(oldValue, value);
    }

    int DXVScrollBar::GetVisibleSize() const
    {
        return _VisibleSize;
    }

    void DXVScrollBar::SetVisibleSize(int value)
    {
        if (_VisibleSize == value)
            return;

        int oldValue = _VisibleSize;
        _VisibleSize = value;

        OnVisibleSizeChanged(oldValue, value);
    }

    bool DXVScrollBar::GetHideWhenNoScroll() const
    {
        return _HideWhenNoScroll;
    }

    void DXVScrollBar::SetHideWhenNoScroll(bool value)
    {
        if (_HideWhenNoScroll == value)
            return;

        bool oldValue = _HideWhenNoScroll;
        _HideWhenNoScroll = value;

        OnHideWhenNoScrollChanged(oldValue, value);
    }

    void DXVScrollBar::OnValueChanged(int oValue, int nValue)
    {
        if (_Value != std::max(_MinValue, std::min(_MaxValue - _VisibleSize, _Value)))
        {
            _Value = std::max(_MinValue, std::min(_MaxValue - _VisibleSize, _Value));
            return;
        }

        UpdateScrollBar();
        ValueChanged.Invoke(this, EventArgs::Empty);
    }

    void DXVScrollBar::OnMaxValueChanged(int oValue, int nValue)
    {
        if (_Value + _VisibleSize > _MaxValue)
            _Value = _MaxValue - _VisibleSize;

        UpdateScrollBar();
        MaxValueChanged.Invoke(this, EventArgs::Empty);
    }

    void DXVScrollBar::OnMinValueChanged(int oValue, int nValue)
    {
        UpdateScrollBar();
        MinValueChanged.Invoke(this, EventArgs::Empty);
    }

    void DXVScrollBar::OnVisibleSizeChanged(int oValue, int nValue)
    {
        UpdateScrollBar();
        VisibleSizeChanged.Invoke(this, EventArgs::Empty);
    }

    void DXVScrollBar::OnHideWhenNoScrollChanged(bool oValue, bool nValue)
    {
        UpdateScrollBar();
        HideWhenNoScrollChanged.Invoke(this, EventArgs::Empty);
    }

    int DXVScrollBar::GetScrollHeight() const
    {
        return GetSize().Height - 50;
    }

    void DXVScrollBar::OnSizeChanged(const Size& oValue, const Size& nValue)
    {
        DXControl::OnSizeChanged(oValue, nValue);

        if (GetScrollHeight() < 0)
            return;

        DownButton->SetLocation(Point(UpButton->GetLocation().X, nValue.Height - 13));
        UpdateScrollBar();
    }

    DXVScrollBar::DXVScrollBar()
    {
        Border = true;
        BorderColour = Color(198, 166, 99);
        DrawTexture = true;
        BackColour = Color::Black;

        Change = 10;

        UpButton = new DXButton();
        UpButton->Index = 44;
        UpButton->LibraryFile = LibraryFile::Interface;
        UpButton->SetLocation(Point(1, 1));
        UpButton->IsEnabled = false;
        UpButton->Parent = this;
        UpButton->MouseClick += [this](void* sender, MouseEventArgs* e) { SetValue(GetValue() - Change); };
        UpButton->MouseWheel += [this](MouseEventArgs* e) { DoMouseWheel(nullptr, e); };

        DownButton = new DXButton();
        DownButton->Index = 46;
        DownButton->LibraryFile = LibraryFile::Interface;
        DownButton->SetLocation(Point(UpButton->GetLocation().X, 0));
        DownButton->IsEnabled = false;
        DownButton->Parent = this;
        DownButton->MouseClick += [this](void* sender, MouseEventArgs* e) { SetValue(GetValue() + Change); };
        DownButton->MouseWheel += [this](MouseEventArgs* e) { DoMouseWheel(nullptr, e); };

        PositionBar = new DXButton();
        PositionBar->Index = 45;
        PositionBar->LibraryFile = LibraryFile::Interface;
        PositionBar->SetLocation(Point(UpButton->GetLocation().X, UpButton->GetSize().Height + 4));
        PositionBar->IsEnabled = false;
        PositionBar->Parent = this;
        PositionBar->Movable = true;
        PositionBar->Sound = SoundIndex::None;
        PositionBar->CanBePressed = false;
        PositionBar->Moving += [this](void* sender, MouseEventArgs* e) { PositionBar_Moving(sender, e); };
        PositionBar->MouseWheel += [this](MouseEventArgs* e) { DoMouseWheel(nullptr, e); };
    }

    void DXVScrollBar::UpdateScrollBar()
    {
        UpButton->IsEnabled = _Value > _MinValue;
        DownButton->IsEnabled = _Value < _MaxValue - _VisibleSize;
        PositionBar->IsEnabled = _MaxValue - _MinValue > _VisibleSize;

        if (_MaxValue - _MinValue - _VisibleSize != 0)
        {
            int newY = 16 + static_cast<int>(GetScrollHeight() * (_Value / static_cast<float>(_MaxValue - _MinValue - _VisibleSize)));
            PositionBar->SetLocation(Point(UpButton->GetLocation().X, newY));
        }

        if (_HideWhenNoScroll)
            SetVisible(UpButton->IsEnabled || DownButton->IsEnabled);
    }

    void DXVScrollBar::DoMouseWheel(void* sender, MouseEventArgs* e)
    {
        SetValue(_Value - e->Delta / SystemInformation::MouseWheelScrollDelta * Change);
    }

    void DXVScrollBar::UpdateBorderInformation()
    {
        BorderInformation = nullptr;
        
        if (!Border || DisplayArea.Width == 0 || DisplayArea.Height == 0)
            return;

        BorderInformation = new std::vector<Vector2>{
            Vector2(0, 0),
            Vector2(GetSize().Width + 1, 0),
            Vector2(GetSize().Width + 1, GetSize().Height + 1),
            Vector2(0, GetSize().Height + 1),
            Vector2(0, 0),
            Vector2(0, 14),
            Vector2(GetSize().Width + 1, 14),
            Vector2(GetSize().Width + 1, GetSize().Height - 13),
            Vector2(0, GetSize().Height - 13)
        };
    }

    void DXVScrollBar::PositionBar_Moving(void* sender, MouseEventArgs* e)
    {
        _Value = static_cast<int>(std::round((PositionBar->GetLocation().Y - 16) * (_MaxValue - _MinValue - _VisibleSize) / static_cast<float>(GetScrollHeight())));

        if (_MaxValue - _MinValue - _VisibleSize == 0)
            return;

        int newY = 16 + static_cast<int>(GetScrollHeight() * (_Value / static_cast<float>(_MaxValue - _MinValue - _VisibleSize)));
        PositionBar->SetLocation(Point(UpButton->GetLocation().X, newY));
    }

    void DXVScrollBar::OnMouseDown(MouseEventArgs* e)
    {
        DXControl::OnMouseDown(e);

        _Value = static_cast<int>(std::round((e->Location.Y - DisplayArea.Top - 32) * (_MaxValue - _MinValue - _VisibleSize) / static_cast<float>(GetScrollHeight())));
    }

    void DXVScrollBar::OnMouseWheel(MouseEventArgs* e)
    {
        DXControl::OnMouseWheel(e);
        DoMouseWheel(this, e);
    }

    void DXVScrollBar::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            _Value = 0;
            ValueChanged.Clear();

            _MaxValue = 0;
            MaxValueChanged.Clear();

            _MinValue = 0;
            MinValueChanged.Clear();

            _VisibleSize = 0;
            VisibleSizeChanged.Clear();

            Change = 0;

            if (UpButton != nullptr)
            {
                if (!UpButton->IsDisposed)
                    UpButton->Dispose();

                UpButton = nullptr;
            }

            if (DownButton != nullptr)
            {
                if (!DownButton->IsDisposed)
                    DownButton->Dispose();

                DownButton = nullptr;
            }

            if (PositionBar != nullptr)
            {
                if (!PositionBar->IsDisposed)
                    PositionBar->Dispose();

                PositionBar = nullptr;
            }
        }
    }
}
