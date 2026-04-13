#include "DXComboBox.h"

namespace Client::Controls
{
    // Static member initialization
    std::vector<DXComboBox*> DXComboBox::ComboBoxes;

    void DXComboBox::SetNormalHeight(int value)
    {
        if (_NormalHeight == value) return;

        int oldValue = _NormalHeight;
        _NormalHeight = value;

        OnNormalHeightChanged(oldValue, value);
    }

    void DXComboBox::OnNormalHeightChanged(int oValue, int nValue)
    {
        NormalHeightChanged.Invoke(this, oValue, nValue);

        if (!GetShowing())
            SetSize(Size(GetSize().Width, GetNormalHeight()));
    }

    void DXComboBox::SetDropDownHeight(int value)
    {
        if (_DropDownHeight == value || value < GetNormalHeight()) return;

        int oldValue = _DropDownHeight;
        _DropDownHeight = value;

        OnDropDownHeightChanged(oldValue, value);
    }

    void DXComboBox::OnDropDownHeightChanged(int oValue, int nValue)
    {
        DropDownHeightChanged.Invoke(this, oValue, nValue);

        if (GetShowing())
            SetSize(Size(GetSize().Width, GetDropDownHeight()));
    }

    void DXComboBox::SetShowing(bool value)
    {
        if (_Showing == value) return;

        bool oldValue = _Showing;
        _Showing = value;

        OnShowingChanged(oldValue, value);
    }

    void DXComboBox::OnShowingChanged(bool oValue, bool nValue)
    {
        int newHeight = GetShowing() ? 
            std::min(ListBox->ScrollBar.GetMaxValue() + GetNormalHeight() + 2, GetDropDownHeight()) : 
            GetNormalHeight();
        SetSize(Size(GetSize().Width, newHeight));

        if (ListBox != nullptr)
            ListBox->SetVisible(GetShowing());

        ShowingChanged.Invoke(this, oValue, nValue);
    }

    void DXComboBox::SetSelectedItem(void* value)
    {
        if (_SelectedItem == value) return;

        void* oldValue = _SelectedItem;
        _SelectedItem = value;

        OnSelectedItemChanged(oldValue, value);
    }

    void DXComboBox::OnSelectedItemChanged(void* oValue, void* nValue)
    {
        SelectedItemChanged.Invoke(this, oValue, nValue);
    }

    void DXComboBox::OnSizeChanged(const Size& oValue, const Size& nValue)
    {
        DXControl::OnSizeChanged(oValue, nValue);

        if (DownArrow == nullptr || SelectedLabel == nullptr || ListBox == nullptr) return;

        SelectedLabel->SetSize(Size(GetSize().Width - 3 - DownArrow->GetSize().Height, GetNormalHeight()));

        DownArrow->SetLocation(Point(GetSize().Width - DownArrow->GetSize().Width, 
            (GetNormalHeight() - DownArrow->GetSize().Height) / 2));

        ListBox->SetLocation(Point(GetDisplayArea().Location.X + SelectedLabel->GetLocation().X, 
            GetDisplayArea().Location.Y + GetNormalHeight() + 2));
        ListBox->BringToFront();

        if (GetShowing())
            ListBox->SetSize(Size(GetSize().Width, GetSize().Height - GetNormalHeight() - 2));
    }

    DXComboBox::DXComboBox()
    {
        SetSort(true);
        SetNormalHeight(DefaultNormalHeight);
        SetDropDownHeight(123);
        SetBorder(true);
        SetBorderColour(Color::FromArgb(198, 166, 99));

        DownArrow = new DXButton();
        DownArrow->SetLibraryFile(LibraryFile::GameInter);
        DownArrow->SetIndex(795);
        DownArrow->SetParent(this);
        DownArrow->MouseClick += [this](void* sender, const MouseEventArgs& e) {
            DownArrow_MouseClick(sender, e);
        };

        SelectedLabel = new DXLabel();
        SelectedLabel->SetLocation(Point(0, -1));
        SelectedLabel->SetAutoSize(false);
        SelectedLabel->SetParent(this);
        SelectedLabel->SetForeColour(Color::White);
        SelectedLabel->SetDrawFormat(TextFormatFlags::VerticalCenter | TextFormatFlags::WordEllipsis);

        ListBox = new DXListBox();
        ListBox->SetParent(GetActiveScene());
        ListBox->SetBackColour(Color::Black);
        ListBox->SetSort(true);
        ListBox->ScrollBar.SetChange(15);
        
        ListBox->selectedItemChanged += [this](void* sender, bool e) {
            auto selectedItem = ListBox->GetSelectedItem();
            SetSelectedItem(selectedItem != nullptr ? selectedItem->GetItem() : nullptr);
            
            std::string labelText = "";
            if (selectedItem != nullptr && selectedItem->GetLabel() != nullptr)
                labelText = selectedItem->GetLabel()->GetText();
            SelectedLabel->SetText(labelText);
            
            SetShowing(false);
        };

        ComboBoxes.push_back(this);
    }

    DXComboBox::~DXComboBox()
    {
        Dispose(true);
    }

    void DXComboBox::DownArrow_MouseClick(void* sender, const MouseEventArgs& e)
    {
        SetShowing(!GetShowing());
    }

    void DXComboBox::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            // Remove from static list
            auto it = std::find(ComboBoxes.begin(), ComboBoxes.end(), this);
            if (it != ComboBoxes.end())
                ComboBoxes.erase(it);

            _NormalHeight = 0;
            _DropDownHeight = 0;
            _Showing = false;
            _SelectedItem = nullptr;

            if (DownArrow != nullptr)
            {
                if (!DownArrow->GetIsDisposed())
                    delete DownArrow;
                DownArrow = nullptr;
            }

            if (SelectedLabel != nullptr)
            {
                if (!SelectedLabel->GetIsDisposed())
                    delete SelectedLabel;
                SelectedLabel = nullptr;
            }

            if (ListBox != nullptr)
            {
                if (!ListBox->GetIsDisposed())
                    delete ListBox;
                ListBox = nullptr;
            }
        }
    }
}
