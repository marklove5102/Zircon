#pragma once

#include "DXWindow.h"
#include "DXButton.h"
#include "DXNumberBox.h"
#include <string>

namespace Client::Controls
{
    // Forward declaration
    class DXItemCell;
    struct ClientUserItem;

    class DXItemAmountWindow : public DXWindow
    {
    public:
        // Properties
        DXButton* ConfirmButton;
        DXNumberBox* AmountBox;
        
    private:
        DXItemCell* ItemCell;

    public:
        int64_t Amount; // Don't dispose

        // Override properties
        WindowType GetType() const override { return WindowType::ItemAmountBox; }
        bool GetCustomSize() const override { return false; }
        bool GetAutomaticVisibility() const override { return false; }

        // Constructor
        DXItemAmountWindow(const std::string& caption, ClientUserItem* item);
        
        // Methods
        void OnKeyPress(KeyPressEventArgs& e);

    protected:
        void Dispose(bool disposing) override;

    private:
        void AmountBox_KeyPress(void* sender, KeyPressEventArgs& e);
        void AmountBox_ValueChanged(void* sender, void* e);
    };

} // namespace Client::Controls
