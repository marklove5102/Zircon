#include "DXScene.h"
#include "CEnvir.h"
#include "DXManager.h"
#include "DXListBox.h"
#include "DXComboBox.h"
#include "MapControl.h"
#include <SystemInformation.h>

namespace Client::Controls
{
    // Size property implementation (sealed)
    void DXScene::SetSize(const Size& value)
    {
        DXControl::SetSize(value);
    }

    const Size& DXScene::GetSize() const
    {
        return DXControl::GetSize();
    }

    DXScene::DXScene(const Size& size)
    {
        DrawTexture = false;
        SetSize(size);

        DXManager::SetResolution(size);

        if (!Config::FullScreen)
            CEnvir::Target->Center();
    }

    void DXScene::OnLocationChanged(const Point& oValue, const Point& nValue)
    {
        DXControl::OnLocationChanged(oValue, nValue);

        if (DebugLabel == nullptr || PingLabel == nullptr)
            return;

        DebugLabel->SetLocation(Point(Location.X + 5, Location.Y + 5));
        PingLabel->SetLocation(Point(Location.X + 5, Location.Y + 19));
    }

    void DXScene::OnIsVisibleChanged(bool oValue, bool nValue)
    {
        DXControl::OnIsVisibleChanged(oValue, nValue);

        if (!IsVisible)
            return;

        for (DXComboBox* box : DXComboBox::ComboBoxes)
        {
            box->ListBox->Parent = this;
        }
    }

    void DXScene::OnMouseDown(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (MouseControl != nullptr && MouseControl != this)
            MouseControl->OnMouseDown(e);
        else
            DXControl::OnMouseDown(e);

        DXControl* listbox = MouseControl;

        while (listbox != nullptr)
        {
            if (dynamic_cast<DXListBox*>(listbox) != nullptr)
                break;

            listbox = listbox->Parent;
        }

        for (DXComboBox* box : DXComboBox::ComboBoxes)
        {
            if (box->ListBox != listbox)
                box->Showing = false;
        }
    }

    void DXScene::OnMouseUp(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (MouseControl != nullptr && MouseControl != this)
            MouseControl->OnMouseUp(e);
        else
            DXControl::OnMouseUp(e);
    }

    void DXScene::OnMouseMove(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (FocusControl != nullptr && FocusControl != this && dynamic_cast<MapControl*>(FocusControl) != nullptr)
            FocusControl->OnMouseMove(e);
        else if (MouseControl != nullptr && MouseControl != this && (MouseControl->IsMoving || MouseControl->IsResizing))
            MouseControl->OnMouseMove(e);
        else
            DXControl::OnMouseMove(e);
    }

    void DXScene::OnMouseClick(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (Buttons == e->Button)
        {
            if (ClickTime.AddMilliseconds(SystemInformation::DoubleClickTime) >= DateTime::Now)
            {
                OnMouseDoubleClick(e);
                return;
            }
        }
        else
            ClickTime = DateTime::MinValue;

        if (MouseControl != nullptr && MouseControl != this)
        {
            if (MouseControl == FocusControl)
                MouseControl->OnMouseClick(e);
        }
        else
            DXControl::OnMouseClick(e);

        ClickControl = MouseControl;
        ClickTime = CEnvir::Now;
        Buttons = e->Button;
    }

    void DXScene::OnMouseDoubleClick(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (MouseControl != nullptr && MouseControl != this)
        {
            if (MouseControl == ClickControl)
            {
                MouseControl->OnMouseDoubleClick(e);
                ClickTime = DateTime::MinValue;
            }
            else
            {
                MouseControl->OnMouseClick(e);
                ClickTime = CEnvir::Now;
            }
        }

        ClickControl = MouseControl;
    }

    void DXScene::OnMouseWheel(MouseEventArgs* e)
    {
        if (!IsEnabled)
            return;

        if (MouseControl != nullptr && MouseControl != this)
            MouseControl->OnMouseWheel(e);
        else
            DXControl::OnMouseWheel(e);
    }

    void DXScene::OnAfterDraw()
    {
        DXControl::OnAfterDraw();

        /*
        DXManager::Sprite->Flush();
        if (!Location.IsEmpty())
            DXManager::Device->Clear(ClearFlags::Target, Color::Black, 1, 0, std::vector<Rectangle>{
                Rectangle(0, 0, Location.X > 0 ? Location.X : ScreenSize.Width, Location.X == 0 ? Location.Y : ScreenSize.Height),
                Rectangle(Location.X > 0 ? Size.Width + Location.X : 0,
                          Location.X == 0 ? Size.Height + Location.Y : 0,
                          Location.X > 0 ? Location.X : ScreenSize.Width,
                          Location.X == 0 ? Location.Y : ScreenSize.Height)
            });
        */

        DebugLabel->Draw();

        if (!HintLabel->GetText().empty())
            HintLabel->Draw();

        if (!PingLabel->GetText().empty())
            PingLabel->Draw();
    }

    void DXScene::CheckIsVisible()
    {
        IsVisible = Visible && ActiveScene == this;

        for (DXControl* control : Controls)
            control->CheckIsVisible();
    }

    void DXScene::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            ClickControl = nullptr;
            ClickTime = DateTime::MinValue;
            Buttons = System::Windows::Forms::MouseButtons::None;
        }
    }
}
