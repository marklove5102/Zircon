#include "DXCheckBox.h"

namespace Client::Controls
{
    DXCheckBox::DXCheckBox()
    {
        _Checked = false;
        _ReadOnly = false;
        
        Label = new DXLabel();
        Label->SetParent(this);
        Label->SetIsControl(false);
        Label->SetLocation(Point(0, 0));

        Label->DisplayAreaChanged += [this](void* sender, EventArgs e)
        {
            SetSize(Size(Label->GetDisplayArea().Width + Box->GetDisplayArea().Width, Box->GetDisplayArea().Height));
            Box->SetLocation(Point(Label->GetDisplayArea().Width, 1));
        };

        Box = new DXImageControl();
        Box->SetLocation(Point(Label->GetSize().Width + 2, 1));
        Box->SetIndex(161);
        // Box->SetLibraryFile(LibraryFile.GameInter); // Requires LibraryFile enum
        Box->SetParent(this);
        Box->SetIsControl(false);
        
        Box->DisplayAreaChanged += [this](void* sender, EventArgs e)
        {
            SetSize(Size(Label->GetDisplayArea().Width + Box->GetDisplayArea().Width, Box->GetDisplayArea().Height));
            Box->SetLocation(Point(Label->GetDisplayArea().Width, 1));
        };

        SetSize(Size(18, 18));
    }

    DXCheckBox::~DXCheckBox()
    {
        Dispose(true);
    }

    void DXCheckBox::SetChecked(bool value)
    {
        if (_Checked == value) return;

        bool oldValue = _Checked;
        _Checked = value;

        OnCheckedChanged(oldValue, value);
    }

    void DXCheckBox::OnCheckedChanged(bool oValue, bool nValue)
    {
        if (CheckedChanged) CheckedChanged->Invoke(this, EventArgs::Empty());

        Box->SetIndex(GetChecked() ? 162 : 161);
    }

    void DXCheckBox::SetReadOnly(bool value)
    {
        if (_ReadOnly == value) return;

        bool oldValue = _ReadOnly;
        _ReadOnly = value;

        OnReadOnlyChanged(oldValue, value);
    }

    void DXCheckBox::OnReadOnlyChanged(bool oValue, bool nValue)
    {
        if (ReadOnlyChanged) ReadOnlyChanged->Invoke(this, EventArgs::Empty());
    }

    void DXCheckBox::OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue)
    {
        DXControl::OnDisplayAreaChanged(oValue, nValue);
        UpdateControl();
    }

    void DXCheckBox::UpdateControl()
    {
        if (Label == nullptr) return;

        Label->SetLocation(Point(0, 0));
        SetSize(Size(Label->GetDisplayArea().Width + Box->GetDisplayArea().Width, Box->GetDisplayArea().Height));
        Box->SetLocation(Point(Label->GetDisplayArea().Width, 0));
    }

    void DXCheckBox::OnMouseClick(MouseEventArgs e)
    {
        if (!GetIsEnabled()) return;

        DXControl::OnMouseClick(e);

        if (GetReadOnly()) return;

        SetChecked(!GetChecked());
    }

    void DXCheckBox::SetSilentState(bool check)
    {
        _Checked = check;
        Box->SetIndex(GetChecked() ? 162 : 161);
    }

    void DXCheckBox::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            if (Label != nullptr)
            {
                if (!Label->GetIsDisposed())
                    Label->Dispose();
                delete Label;
                Label = nullptr;
            }

            if (Box != nullptr)
            {
                if (!Box->GetIsDisposed())
                    Box->Dispose();
                delete Box;
                Box = nullptr;
            }

            _Checked = false;
            CheckedChanged.reset();

            _ReadOnly = false;
            ReadOnlyChanged.reset();
        }
    }
}
