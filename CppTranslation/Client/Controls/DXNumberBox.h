#pragma once
#include "DXControl.h"
#include "DXButton.h"
#include "DXNumberTextBox.h"

namespace Client::Controls
{
    class DXNumberBox final : public DXControl
    {
    public:
        // Properties
        DXButton* UpButton;
        DXButton* DownButton;
        DXNumberTextBox* ValueTextBox;

        long GetValue() const;
        void SetValue(long value);

        long GetMinValue() const;
        void SetMinValue(long value);

        long GetMaxValue() const;
        void SetMaxValue(long value);

        long Change;

        // Constructor
        DXNumberBox();

    protected:
        void Dispose(bool disposing) override;
    };
}
