#include "DXNumberTextBox.h"
#include <msclr/marshal_cppstd.h>

using namespace System;
using namespace System::Globalization;
using namespace System::Threading;
using namespace Client::Controls;

DXNumberTextBox::DXNumberTextBox()
{
    TextBox->TextChanged += gcnew EventHandler(this, &DXNumberTextBox::TextBox_TextChanged);
    TextBox->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &DXNumberTextBox::TextBox_KeyPress);
    TextBox->Text = "0";
}

void DXNumberTextBox::OnValueChanged(long long oValue, long long nValue)
{
    ValueChanged?.Invoke(this, EventArgs::Empty);

    TextBox->Text = Value.ToString("#,##0", Thread::CurrentThread->CurrentCulture->NumberFormat);
    TextBox->SelectionStart = TextBox->Text->Length;
    ValueChanged?.Invoke(this, EventArgs::Empty);
}

void DXNumberTextBox::OnMaxValueChanged(long long oValue, long long nValue)
{
    MaxValueChanged?.Invoke(this, EventArgs::Empty);

    if (Value >= MaxValue)
        TextBox->Text = MaxValue.ToString();
}

void DXNumberTextBox::OnMinValueChanged(long long oValue, long long nValue)
{
    MinValueChanged?.Invoke(this, EventArgs::Empty);

    if (Value < MinValue)
        TextBox->Text = MinValue.ToString();
}

void DXNumberTextBox::TextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
{
    if (!char::IsControl(e->KeyChar) && !char::IsDigit(e->KeyChar))
        e->Handled = true;
}

void DXNumberTextBox::TextBox_TextChanged(System::Object^ sender, EventArgs^ e)
{
    long long vol;

    if (long long::TryParse(TextBox->Text, 
                            NumberStyles::Integer | NumberStyles::AllowThousands, 
                            Thread::CurrentThread->CurrentCulture->NumberFormat, 
                            [out] vol))
    {
        if (vol < MinValue)
            vol = MinValue;

        if (vol > MaxValue)
            vol = MaxValue;

        Value = vol;
        TextBox->Text = Value.ToString("#,##0", Thread::CurrentThread->CurrentCulture->NumberFormat);
    }
    else
    {
        Value = MinValue;
        TextBox->Text = Value.ToString("#,##0", Thread::CurrentThread->CurrentCulture->NumberFormat);
    }
}

DXNumberTextBox::~DXNumberTextBox()
{
    Dispose(true);
    DXTextBox::~DXTextBox();
}

void DXNumberTextBox::Dispose(bool disposing)
{
    if (disposing)
    {
        _Value = 0;
        _MaxValue = 0;
        _MinValue = 0;

        ValueChanged = nullptr;
        MaxValueChanged = nullptr;
        MinValueChanged = nullptr;
    }
}
