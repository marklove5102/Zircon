#pragma once

#include "DXControl.h"
#include "DXTextBox.h"
#include "DXButton.h"

namespace Client::Controls
{
    public ref class DXNumberTextBox : DXTextBox
    {
    public:
        // Properties
        property long long Value
        {
            long long get() { return _Value; }
            void set(long long value)
            {
                if (_Value == value) return;
                long long oldValue = _Value;
                _Value = value;
                OnValueChanged(oldValue, value);
            }
        }

        property long long MaxValue
        {
            long long get() { return _MaxValue; }
            void set(long long value)
            {
                if (_MaxValue == value) return;
                long long oldValue = _MaxValue;
                _MaxValue = value;
                OnMaxValueChanged(oldValue, value);
            }
        }

        property long long MinValue
        {
            long long get() { return _MinValue; }
            void set(long long value)
            {
                if (_MinValue == value) return;
                long long oldValue = _MinValue;
                _MinValue = value;
                OnMinValueChanged(oldValue, value);
            }
        }

        // Events
        event EventHandler<EventArgs^>^ ValueChanged;
        event EventHandler<EventArgs^>^ MaxValueChanged;
        event EventHandler<EventArgs^>^ MinValueChanged;

        // Constructor
        DXNumberTextBox();

    protected:
        virtual void OnValueChanged(long long oValue, long long nValue);
        virtual void OnMaxValueChanged(long long oValue, long long nValue);
        virtual void OnMinValueChanged(long long oValue, long long nValue);
        virtual ~DXNumberTextBox() override;

    private:
        long long _Value;
        long long _MaxValue;
        long long _MinValue;

        void TextBox_TextChanged(System::Object^ sender, EventArgs^ e);
        void TextBox_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e);
        void Dispose(bool disposing);
    };
}
