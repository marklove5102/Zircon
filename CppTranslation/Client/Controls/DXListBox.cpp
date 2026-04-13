#include "DXListBox.h"

namespace Client::Controls
{
    // DXListBox Implementation

    DXListBoxItem* DXListBox::GetSelectedItem() const
    {
        return _SelectedItem;
    }

    void DXListBox::SetSelectedItem(DXListBoxItem* value)
    {
        if (_SelectedItem == value)
            return;

        DXListBoxItem* oldValue = _SelectedItem;
        _SelectedItem = value;

        OnselectedItemChanged(oldValue, value);
    }

    void DXListBox::OnselectedItemChanged(DXListBoxItem* oValue, DXListBoxItem* nValue)
    {
        if (oValue != nullptr)
            oValue->SetSelected(false);

        if (nValue != nullptr)
            nValue->SetSelected(true);

        selectedItemChanged.Invoke(this, EventArgs::Empty);
    }

    void DXListBox::OnSizeChanged(const Size& oValue, const Size& nValue)
    {
        DXControl::OnSizeChanged(oValue, nValue);

        if (ScrollBar == nullptr)
            return;

        for (DXControl* control : Controls)
        {
            if (dynamic_cast<DXListBoxItem*>(control) == nullptr)
                continue;

            control->SetSize(Size(nValue.Width - ScrollBar->GetSize().Width - 1, control->GetSize().Height));
        }

        ScrollBar->SetSize(Size(14, nValue.Height));
        ScrollBar->SetLocation(Point(nValue.Width - ScrollBar->GetSize().Width, 0));

        UpdateScrollBar();
    }

    DXListBox::DXListBox()
    {
        Border = true;
        DrawTexture = true;
        BorderColour = Color(198, 166, 99);

        ScrollBar = new DXVScrollBar();
        ScrollBar->VisibleSize = GetSize().Height;
        ScrollBar->SetSize(Size(14, GetSize().Height));
        ScrollBar->Parent = this;
        ScrollBar->ValueChanged += [this](void* sender, EventArgs* e) { ScrollBar_ValueChanged(sender, e); };

        MouseWheel += [this](MouseEventArgs* e) { ScrollBar->DoMouseWheel(nullptr, e); };
    }

    void DXListBox::OnMouseClick(MouseEventArgs* e)
    {
        DXControl::OnMouseClick(e);
        SetSelectedItem(nullptr);
    }

    void DXListBox::ScrollBar_ValueChanged(void* sender, EventArgs* e)
    {
        UpdateItems();
    }

    void DXListBox::UpdateItems()
    {
        for (DXControl* control : Controls)
        {
            DXListBoxItem* item = dynamic_cast<DXListBoxItem*>(control);
            if (item != nullptr)
                item->UpdateLocation();
        }
    }

    void DXListBox::UpdateScrollBar()
    {
        ScrollBar->VisibleSize = GetSize().Height;

        int height = 0;

        for (DXControl* control : Controls)
        {
            if (dynamic_cast<DXListBoxItem*>(control) == nullptr)
                continue;

            height += control->GetSize().Height;
        }

        ScrollBar->MaxValue = height;
    }

    void DXListBox::SelectItem(void* ob)
    {
        for (DXControl* control : Controls)
        {
            DXListBoxItem* listItem = dynamic_cast<DXListBoxItem*>(control);
            if (listItem == nullptr)
                continue;

            if (ob == nullptr)
            {
                if (listItem->GetItem() != nullptr)
                    continue;

                SetSelectedItem(listItem);
                break;
            }

            if (ob != listItem->GetItem())
                continue;

            SetSelectedItem(listItem);
            break;
        }
    }

    void DXListBox::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            if (_SelectedItem != nullptr)
            {
                if (!_SelectedItem->IsDisposed)
                    _SelectedItem->Dispose();
                _SelectedItem = nullptr;
            }

            if (ScrollBar != nullptr)
            {
                if (!ScrollBar->IsDisposed)
                    ScrollBar->Dispose();
                ScrollBar = nullptr;
            }
        }
    }

    // DXListBoxItem Implementation

    void* DXListBoxItem::GetItem() const
    {
        return _Item;
    }

    void DXListBoxItem::SetItem(void* value)
    {
        if (_Item == value)
            return;

        void* oldValue = _Item;
        _Item = value;

        OnItemChanged(oldValue, value);
    }

    bool DXListBoxItem::GetSelected() const
    {
        return _Selected;
    }

    void DXListBoxItem::SetSelected(bool value)
    {
        if (_Selected == value)
            return;

        bool oldValue = _Selected;
        _Selected = value;

        OnSelectedChanged(oldValue, value);
    }

    void DXListBoxItem::OnItemChanged(void* oValue, void* nValue)
    {
        ItemChanged.Invoke(this, EventArgs::Empty);
    }

    void DXListBoxItem::OnSelectedChanged(bool oValue, bool nValue)
    {
        UpdateColours();
        SelectedChanged.Invoke(this, EventArgs::Empty);
    }

    void DXListBoxItem::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        DXControl::OnParentChanged(oValue, nValue);

        DXListBox* listBox = dynamic_cast<DXListBox*>(Parent);
        if (listBox == nullptr)
            return;

        SetSize(Size(Parent->GetSize().Width - listBox->ScrollBar->GetSize().Width - 1, Label->GetSize().Height));

        UpdateLocation();
        listBox->UpdateScrollBar();

        MouseWheel += [listBox](MouseEventArgs* e) { listBox->ScrollBar->DoMouseWheel(nullptr, e); };
    }

    DXListBoxItem::DXListBoxItem()
    {
        DrawTexture = true;

        Label = new DXLabel();
        Label->Parent = this;
        Label->SetText("List Box Item");
        Label->IsControl = false;
    }

    void DXListBoxItem::OnMouseClick(MouseEventArgs* e)
    {
        DXControl::OnMouseClick(e);

        DXListBox* listBox = dynamic_cast<DXListBox*>(Parent);
        if (listBox == nullptr)
            return;

        listBox->SetSelectedItem(this);
    }

    void DXListBoxItem::OnMouseEnter()
    {
        DXControl::OnMouseEnter();
        UpdateColours();
    }

    void DXListBoxItem::OnMouseLeave()
    {
        DXControl::OnMouseLeave();
        UpdateColours();
    }

    void DXListBoxItem::UpdateLocation()
    {
        DXListBox* listBox = dynamic_cast<DXListBox*>(Parent);

        if (listBox == nullptr)
            return;

        int y = -listBox->ScrollBar->GetValue();

        for (DXControl* control : Parent->Controls)
        {
            if (dynamic_cast<DXListBoxItem*>(control) == nullptr)
                continue;

            if (control == this)
                break;

            y += control->GetSize().Height;
        }

        SetLocation(Point(0, y));
    }

    void DXListBoxItem::UpdateColours()
    {
        if (_Selected)
        {
            Label->SetForeColour(Color::White);
            BackColour = Color(128, 64, 64);
        }
        else if (MouseControl == this)
        {
            Label->SetForeColour(Color(198, 166, 99));
            BackColour = Color(64, 32, 32);
        }
        else
        {
            Label->SetForeColour(Color(198, 166, 99));
            BackColour = Color::Empty;
        }
    }

    void DXListBoxItem::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            _Item = nullptr;
            _Selected = false;

            ItemChanged.Clear();
            SelectedChanged.Clear();

            if (Label != nullptr)
            {
                if (!Label->IsDisposed)
                    Label->Dispose();

                Label = nullptr;
            }
        }
    }
}
