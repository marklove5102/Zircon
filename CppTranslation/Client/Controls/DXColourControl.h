#pragma once

#include "../Common/CSharpCompat.h"
#include "DXControl.h"
#include "DXWindow.h"
#include "DXButton.h"
#include "DXNumberBox.h"
#include "DXLabel.h"

namespace Client::Controls
{
    class DXColourPicker;

    class DXColourControl : public DXControl
    {
    public:
        // Properties
        
        // AllowNoColour
        bool GetAllowNoColour() const { return _AllowNoColour; }
        void SetAllowNoColour(bool value);
        EventPtr<EventArgs> AllowNoColourChanged;
        void OnAllowNoColourChanged(bool oValue, bool nValue);

        // Constructor
        DXColourControl();

        // Destructor
        ~DXColourControl() override;

    protected:
        void Dispose(bool disposing) override;

    private:
        void DXColourControl_MouseClick(void* sender, MouseEventArgs e);

        DXColourPicker* Window;
        bool _AllowNoColour;
    };

    class DXColourPicker : public DXWindow
    {
    public:
        // Properties
        
        // SelectedColour
        Color GetSelectedColour() const { return _SelectedColour; }
        void SetSelectedColour(Color value);
        EventPtr<EventArgs> SelectedColourChanged;
        void OnSelectedColourChanged(Color oValue, Color nValue);

        // AllowNoColour
        bool GetAllowNoColour() const { return _AllowNoColour; }
        void SetAllowNoColour(bool value);
        EventPtr<EventArgs> AllowNoColourChanged;
        void OnAllowNoColourChanged(bool oValue, bool nValue);

        // Public fields
        Color PreviousColour;
        bool Updating;

        // Child controls
        DXButton* SelectButton;
        DXButton* CancelButton;
        DXButton* EmptyButton;
        DXColourControl* Target;
        DXNumberBox* RedBox;
        DXNumberBox* GreenBox;
        DXNumberBox* BlueBox;
        DXControl* ColourScaleBox;
        DXControl* ColourBox;
        DXLabel* NoColourLabel;

        // Overrides
        WindowType GetType() const override { return WindowType::None; }
        bool GetCustomSize() const override { return false; }
        bool GetAutomaticVisibility() const override { return false; }

        // Constructor
        DXColourPicker();

        // Destructor
        ~DXColourPicker() override;

    protected:
        void Dispose(bool disposing) override;

    private:
        void ColourScaleBox_MouseClick(void* sender, MouseEventArgs e);
        void CancelButton_MouseClick(void* sender, MouseEventArgs e);
        void ColourBox_ValueChanged(void* sender, EventArgs e);
        void EmptyButton_MouseClick(void* sender, MouseEventArgs e);

        Color _SelectedColour;
        bool _AllowNoColour;
    };
}
