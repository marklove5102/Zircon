#pragma once

#include "../Common/CSharpCompat.h"
#include "DXControl.h"
#include "DXLabel.h"
#include "DXImageControl.h"

namespace Client::Controls
{
    class DXCheckBox : public DXControl
    {
    public:
        // Properties
        
        // Checked
        bool GetChecked() const { return _Checked; }
        void SetChecked(bool value);
        EventPtr<EventArgs> CheckedChanged;
        void OnCheckedChanged(bool oValue, bool nValue);

        // ReadOnly
        bool GetReadOnly() const { return _ReadOnly; }
        void SetReadOnly(bool value);
        EventPtr<EventArgs> ReadOnlyChanged;
        void OnReadOnlyChanged(bool oValue, bool nValue);

        // Child controls
        DXLabel* Label;
        DXImageControl* Box;

        // Constructor
        DXCheckBox();

        // Methods
        void OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue) override;
        void OnMouseClick(MouseEventArgs e) override;
        void SetSilentState(bool check);

        // Destructor
        ~DXCheckBox() override;

    protected:
        void Dispose(bool disposing) override;

    private:
        void UpdateControl();

        bool _Checked;
        bool _ReadOnly;
    };
}
