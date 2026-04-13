#pragma once
#include "DXWindow.h"
#include "DXTextBox.h"
#include <vector>

namespace Client::Controls
{
    // Forward declarations
    enum class DXMessageBoxButtons;
    enum class DialogAction;

    class DXMessageBox final : public DXWindow
    {
    public:
        // Properties
        DXLabel* Label;
        DXButton* OKButton;
        DXButton* CancelButton;
        DXButton* NoButton;
        DXButton* YesButton;
        DXMessageBoxButtons Buttons;
        DXTextBox* HiddenBox;

        // Event handlers
        void OnSizeChanged(const Size& oValue, const Size& nValue) override;
        void OnParentChanged(DXControl* oValue, DXControl* nValue) override;
        void OnIsVisibleChanged(bool oValue, bool nValue) override;
        void OnKeyPress(KeyPressEventArgs* e) override;
        void ResolutionChanged() override;

        // Constructor
        DXMessageBox(const std::string& message, const std::string& caption, DXMessageBoxButtons buttons = DXMessageBoxButtons::OK);

        // Static method
        static DXMessageBox* Show(const std::string& message, const std::string& caption, DialogAction action = DialogAction::None);

    protected:
        void Dispose(bool disposing) override;

        // Overrides
        WindowType GetType() const override;
        bool GetCustomSize() const override;
        bool GetAutomaticVisibility() const override;
    };

    enum class DXMessageBoxButtons
    {
        None,
        OK,
        YesNo,
        Cancel
    };

    enum class DialogAction
    {
        None,
        Close,
        ReturnToLogin
    };
}
