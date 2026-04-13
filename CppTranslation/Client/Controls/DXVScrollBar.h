#pragma once
#include "DXControl.h"
#include "DXButton.h"
#include <EventHandler.h>

namespace Client::Controls
{
    class DXVScrollBar final : public DXControl
    {
    public:
        // Properties
        int GetValue() const;
        void SetValue(int value);

        int GetMaxValue() const;
        void SetMaxValue(int value);

        int GetMinValue() const;
        void SetMinValue(int value);

        int GetVisibleSize() const;
        void SetVisibleSize(int value);

        bool GetHideWhenNoScroll() const;
        void SetHideWhenNoScroll(bool value);

        // Events
        event_handler<EventArgs> ValueChanged;
        event_handler<EventArgs> MaxValueChanged;
        event_handler<EventArgs> MinValueChanged;
        event_handler<EventArgs> VisibleSizeChanged;
        event_handler<EventArgs> HideWhenNoScrollChanged;

        // Buttons
        DXButton* UpButton;
        DXButton* DownButton;
        DXButton* PositionBar;

        // Change amount
        int Change;

        // Event handlers
        void OnValueChanged(int oValue, int nValue);
        void OnMaxValueChanged(int oValue, int nValue);
        void OnMinValueChanged(int oValue, int nValue);
        void OnVisibleSizeChanged(int oValue, int nValue);
        void OnHideWhenNoScrollChanged(bool oValue, bool nValue);
        void OnSizeChanged(const Size& oValue, const Size& nValue) override;
        void OnMouseDown(MouseEventArgs* e) override;
        void OnMouseWheel(MouseEventArgs* e) override;

        // Constructor
        DXVScrollBar();

        // Methods
        void DoMouseWheel(void* sender, MouseEventArgs* e);

    protected:
        void UpdateBorderInformation() override;
        void Dispose(bool disposing) override;

    private:
        int _Value = 0;
        int _MaxValue = 0;
        int _MinValue = 0;
        int _VisibleSize = 0;
        bool _HideWhenNoScroll = false;

        // Helper methods
        int GetScrollHeight() const;
        void UpdateScrollBar();
        void PositionBar_Moving(void* sender, MouseEventArgs* e);
    };
}
