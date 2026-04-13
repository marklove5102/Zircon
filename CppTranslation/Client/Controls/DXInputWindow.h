#pragma once

#include "DXWindow.h"
#include "DXButton.h"
#include "DXLabel.h"
#include "DXTextBox.h"
#include "../Envir/CEnvir.h"
#include <string>

namespace Client::Controls
{
    class DXInputWindow : public DXWindow
    {
    public:
        // Properties
        DXLabel* Label;
        DXButton* ConfirmButton;
        DXButton* CancelButton;
        DXTextBox* ValueTextBox;
        
        std::string Value; // Don't Dispose

        // Override properties
        WindowType GetType() const override { return WindowType::InputWindow; }
        bool GetCustomSize() const override { return false; }
        bool GetAutomaticVisibility() const override { return false; }

        // Constructor
        DXInputWindow(const std::string& message, const std::string& caption);
        
        // Methods
        void OnKeyDown(KeyEventArgs& e) override;
        void OnKeyUp(KeyEventArgs& e) override;
        void OnKeyPress(KeyPressEventArgs& e) override;

    protected:
        void Dispose(bool disposing) override;

    private:
        void TextBox_TextChanged(void* sender, void* e);
    };

} // namespace Client::Controls
