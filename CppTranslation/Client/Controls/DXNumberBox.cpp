#include "DXNumberBox.h"

namespace Client::Controls
{
    // DXNumberBox Implementation

    long DXNumberBox::GetValue() const
    {
        return ValueTextBox->GetValue();
    }

    void DXNumberBox::SetValue(long value)
    {
        ValueTextBox->SetValue(value);
    }

    long DXNumberBox::GetMinValue() const
    {
        return ValueTextBox->GetMinValue();
    }

    void DXNumberBox::SetMinValue(long value)
    {
        ValueTextBox->SetMinValue(value);
    }

    long DXNumberBox::GetMaxValue() const
    {
        return ValueTextBox->GetMaxValue();
    }

    void DXNumberBox::SetMaxValue(long value)
    {
        ValueTextBox->SetMaxValue(value);
    }

    DXNumberBox::DXNumberBox()
    {
        Change = 10;
        SetSize(Size(90, 20));

        ValueTextBox = new DXNumberTextBox();
        ValueTextBox->SetSize(Size(50, 20));
        ValueTextBox->SetLocation(Point(19, 1));
        ValueTextBox->Parent = this;
        ValueTextBox->TextBox->SetText("0");

        ValueTextBox->TextBox->KeyPress += [](void* sender, KeyPressEventArgs* e)
        {
            if (!isdigit(e->KeyChar) && !iscntrl(e->KeyChar))
                e->Handled = true;
        };

        DownButton = new DXButton();
        DownButton->LibraryFile = LibraryFile::GameInter;
        DownButton->Index = 1011;
        DownButton->SetLocation(Point(0, 3));
        DownButton->Parent = this;
        DownButton->MouseClick += [this](void* sender, MouseEventArgs* e)
        {
            ValueTextBox->TextBox->SetText(std::to_string(GetValue() - Change));
        };

        UpButton = new DXButton();
        UpButton->LibraryFile = LibraryFile::GameInter;
        UpButton->Index = 1010;
        UpButton->SetLocation(Point(73, 3));
        UpButton->Parent = this;
        UpButton->MouseClick += [this](void* sender, MouseEventArgs* e)
        {
            ValueTextBox->TextBox->SetText(std::to_string(GetValue() + Change));
        };
    }

    void DXNumberBox::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            Change = 0;

            if (UpButton != nullptr)
            {
                if (!UpButton->IsDisposed)
                    UpButton->Dispose();
                UpButton = nullptr;
            }

            if (DownButton != nullptr)
            {
                if (!DownButton->IsDisposed)
                    DownButton->Dispose();
                DownButton = nullptr;
            }

            if (ValueTextBox != nullptr)
            {
                if (!ValueTextBox->IsDisposed)
                    ValueTextBox->Dispose();
                ValueTextBox = nullptr;
            }
        }
    }
}
