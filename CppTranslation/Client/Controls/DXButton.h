#pragma once

#include "../Common/CSharpCompat.h"
#include "DXImageControl.h"
#include "DXLabel.h"

namespace Client::Controls
{
    enum class ButtonType
    {
        Default,
        SelectedTab,
        DeselectedTab,
        SmallButton,
        AddButton,
        RemoveButton,
        LFGButton,
        SearchButton,
        OptionsButton,
    };

    class DXButton : public DXImageControl
    {
    public:
        // Properties
        
        // HasFocus
        bool GetHasFocus() const { return _HasFocus; }
        void SetHasFocus(bool value);
        EventPtr<EventArgs> HasFocusChanged;
        virtual void OnHasFocusChanged(bool oValue, bool nValue);

        // Pressed
        bool GetPressed() const { return _Pressed; }
        void SetPressed(bool value);
        EventPtr<EventArgs> PressedChanged;
        virtual void OnPressedChanged(bool oValue, bool nValue);

        // CanBePressed
        bool GetCanBePressed() const { return _CanBePressed; }
        void SetCanBePressed(bool value);
        EventPtr<EventArgs> CanBePressedChanged;
        virtual void OnCanBePressedChanged(bool oValue, bool nValue);

        // RightAligned
        bool GetRightAligned() const { return _RightAligned; }
        void SetRightAligned(bool value);
        EventPtr<EventArgs> RightAlignedChanged;
        virtual void OnRightAlignedChanged(bool oValue, bool nValue);

        // ButtonType
        ButtonType GetButtonType() const { return _ButtonType; }
        void SetButtonType(ButtonType value);
        EventPtr<EventArgs> ButtonTypeChanged;
        virtual void OnButtonTypeChanged(ButtonType oValue, ButtonType nValue);

        // HoverIndex
        int GetHoverIndex() const { return _HoverIndex; }
        void SetHoverIndex(int value);
        EventPtr<EventArgs> HoverIndexChanged;
        virtual void OnHoverIndexChanged(int oValue, int nValue);

        // PressedIndex
        int GetPressedIndex() const { return _PressedIndex; }
        void SetPressedIndex(int value);
        EventPtr<EventArgs> PressedIndexChanged;
        virtual void OnPressedIndexChanged(int oValue, int nValue);

        // Label
        DXLabel* Label;

        // Constructor
        DXButton();

        // Methods
        void UpdateDisplayArea() override;
        void OnIsEnabledChanged(bool oValue, bool nValue) override;
        void OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue) override;
        void OnOpacityChanged(float oValue, float nValue) override;
        void OnFocus() override;
        void OnLostFocus() override;
        void OnMouseEnter() override;
        void OnMouseLeave() override;
        void UpdateForeColour();

        // Destructor
        ~DXButton() override;

    protected:
        void DrawMirTexture() override;
        void Dispose(bool disposing) override;

    private:
        void DrawDefault();
        void DrawSelectedTab();
        void DrawDeselectedTab();
        void DrawSmallButton();

        bool _HasFocus;
        bool _Pressed;
        bool _CanBePressed;
        bool _RightAligned;
        ButtonType _ButtonType;
        int _HoverIndex;
        int _PressedIndex;
    };
}
