#pragma once
#include "DXControl.h"
#include "DXVScrollBar.h"
#include "DXLabel.h"
#include <EventHandler.h>

namespace Client::Controls
{
    class DXListBoxItem;

    class DXListBox final : public DXControl
    {
    public:
        // Properties
        DXListBoxItem* GetSelectedItem() const;
        void SetSelectedItem(DXListBoxItem* value);

        // Events
        event_handler<EventArgs> selectedItemChanged;

        // Scroll bar
        DXVScrollBar* ScrollBar;

        // Event handlers
        void OnselectedItemChanged(DXListBoxItem* oValue, DXListBoxItem* nValue);
        void OnSizeChanged(const Size& oValue, const Size& nValue) override;
        void OnMouseClick(MouseEventArgs* e) override;

        // Constructor
        DXListBox();

        // Methods
        void ScrollBar_ValueChanged(void* sender, EventArgs* e);
        void UpdateItems();
        void UpdateScrollBar();
        void SelectItem(void* ob);

    protected:
        void Dispose(bool disposing) override;

    private:
        DXListBoxItem* _SelectedItem = nullptr;
    };

    class DXListBoxItem : public DXControl
    {
    public:
        // Properties
        void* GetItem() const;
        void SetItem(void* value);

        bool GetSelected() const;
        void SetSelected(bool value);

        // Events
        event_handler<EventArgs> ItemChanged;
        event_handler<EventArgs> SelectedChanged;

        // Label
        DXLabel* Label;

        // Event handlers
        void OnItemChanged(void* oValue, void* nValue);
        void OnSelectedChanged(bool oValue, bool nValue);
        void OnParentChanged(DXControl* oValue, DXControl* nValue) override;
        void OnMouseClick(MouseEventArgs* e) override;
        void OnMouseEnter() override;
        void OnMouseLeave() override;

        // Constructor
        DXListBoxItem();

        // Methods
        void UpdateLocation();
        virtual void UpdateColours();

    protected:
        void Dispose(bool disposing) override;

    private:
        void* _Item = nullptr;
        bool _Selected = false;
    };
}
