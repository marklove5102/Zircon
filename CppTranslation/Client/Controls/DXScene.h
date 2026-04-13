#pragma once
#include "DXControl.h"
#include <DateTime.h>
#include <MouseEventArgs.h>

namespace Client::Controls
{
    class DXScene : public DXControl
    {
    public:
        // Properties
        DXControl* ClickControl = nullptr;
        DateTime ClickTime;
        System::Windows::Forms::MouseButtons Buttons;

        // Size property override (sealed in C#)
        void SetSize(const Size& value) override;
        const Size& GetSize() const override;

        // Event handlers
        void OnLocationChanged(const Point& oValue, const Point& nValue) override;
        void OnIsVisibleChanged(bool oValue, bool nValue) override;
        void OnMouseDown(MouseEventArgs* e) override;
        void OnMouseUp(MouseEventArgs* e) override;
        void OnMouseMove(MouseEventArgs* e) override;
        void OnMouseClick(MouseEventArgs* e) override;
        void OnMouseDoubleClick(MouseEventArgs* e) override;
        void OnMouseWheel(MouseEventArgs* e) override;

    protected:
        // Constructor
        explicit DXScene(const Size& size);

        // Drawing
        void OnAfterDraw() override;

        // Visibility
        void CheckIsVisible() override;

        // Destructor
        void Dispose(bool disposing) override;
    };
}
