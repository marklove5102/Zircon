#pragma once

#include "../Common/CSharpCompat.h"

// Forward declarations
namespace Client::Controls {
    class DXControl;
    class DXButton;
    class DXLabel;
    class DXListBox;
}

#include "DXControl.h"
#include "DXButton.h"
#include "DXLabel.h"
#include "DXListBox.h"

namespace Client::Controls
{
    class DXComboBox final : public DXControl
    {
    public:
        // Properties
        static std::vector<DXComboBox*> ComboBoxes;

        // NormalHeight
        int GetNormalHeight() const { return _NormalHeight; }
        void SetNormalHeight(int value);
        int Get_NormalHeight() const { return _NormalHeight; }
        
        Event<int, int> NormalHeightChanged;
        void OnNormalHeightChanged(int oValue, int nValue);

        // DropDownHeight
        int GetDropDownHeight() const { return _DropDownHeight; }
        void SetDropDownHeight(int value);
        
        Event<int, int> DropDownHeightChanged;
        void OnDropDownHeightChanged(int oValue, int nValue);

        // Showing
        bool GetShowing() const { return _Showing; }
        void SetShowing(bool value);
        
        Event<bool, bool> ShowingChanged;
        void OnShowingChanged(bool oValue, bool nValue);

        // SelectedItem
        void* GetSelectedItem() const { return _SelectedItem; }
        void SetSelectedItem(void* value);
        
        Event<void*, void*> SelectedItemChanged;
        void OnSelectedItemChanged(void* oValue, void* nValue);

        static constexpr int DefaultNormalHeight = 16;

        DXButton* DownArrow;
        DXLabel* SelectedLabel;
        DXListBox* ListBox;

        void OnSizeChanged(const Size& oValue, const Size& nValue) override;

        DXComboBox();
        ~DXComboBox() override;

    private:
        void DownArrow_MouseClick(void* sender, const MouseEventArgs& e);

        int _NormalHeight = 0;
        int _DropDownHeight = 0;
        bool _Showing = false;
        void* _SelectedItem = nullptr;
    };
}
