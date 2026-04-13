#pragma once
#include "DXControl.h"
#include "DXButton.h"
#include <vector>
#include <EventHandler.h>

namespace Client::Controls
{
    class DXTab;

    class DXTabControl : public DXControl
    {
    public:
        // Properties
        DXTab* GetSelectedTab() const;
        void SetSelectedTab(DXTab* value);
        
        int GetMarginLeft() const;
        void SetMarginLeft(int value);
        
        int GetPadding() const;
        void SetPadding(int value);

        // Events
        event_handler<EventArgs> SelectedTabChanged;
        event_handler<EventArgs> MarginLeftChanged;
        event_handler<EventArgs> PaddingChanged;

        // Tab buttons list
        std::vector<DXButton*> TabButtons;

        // Event handlers
        void OnSelectedTabChanged(DXTab* oValue, DXTab* nValue);
        void OnMarginLeftChanged(int oValue, int nValue);
        void OnPaddingChanged(int oValue, int nValue);
        void OnDisplayAreaChanged(const Rectangle& oValue, const Rectangle& nValue) override;

        // Constructor
        DXTabControl();

        // Methods
        void SetNewTab();
        void TabsChanged();

    protected:
        // Destructor
        void Dispose(bool disposing) override;

    private:
        DXTab* _SelectedTab = nullptr;
        int _MarginLeft = 0;
        int _Padding = 1;
    };

    class DXTab : public DXControl
    {
    public:
        // Properties
        DXTabControl* GetCurrentTabControl() const;
        void SetCurrentTabControl(DXTabControl* value);
        
        bool GetDrawOtherBorder() const;
        void SetDrawOtherBorder(bool value);
        
        bool GetSelected() const;
        void SetSelected(bool value);
        
        int GetMinimumTabWidth() const;
        void SetMinimumTabWidth(int value);

        // Events
        event_handler<EventArgs> CurrentTabControlChanged;
        event_handler<EventArgs> DrawOtherBorderChanged;
        event_handler<EventArgs> SelectedChanged;
        event_handler<EventArgs> MinimumTabWidthChanged;

        // Tab button
        DXButton* TabButton;

        // State
        float* OldOpacity;
        bool Updating = false;

        // Event handlers
        void OnCurrentTabControlChanged(DXTabControl* oValue, DXTabControl* nValue);
        void OnDrawOtherBorderChanged(bool oValue, bool nValue);
        void OnSelectedChanged(bool oValue, bool nValue);
        void OnMinimumTabWidthChanged(int oValue, int nValue);
        void OnDisplayAreaChanged(const Rectangle& oValue, const Rectangle& nValue) override;
        void OnParentChanged(DXControl* oValue, DXControl* nValue) override;
        void OnSizeChanged(const Size& oValue, const Size& nValue) override;

        // Constructor
        DXTab();

        // Drawing
        void Draw() override;
        void DrawTabBorder();
        void DrawEdges();

    protected:
        void UpdateBorderInformation() override;
        void Dispose(bool disposing) override;

    private:
        DXTabControl* _CurrentTabControl = nullptr;
        bool _DrawOtherBorder = false;
        bool _Selected = false;
        int _MinimumTabWidth = 0;

        // Event handlers
        void TabButton_IsMovingChanged(void* sender, EventArgs* e);
        void TabButton_LocationChanged(void* sender, EventArgs* e);
    };
}
