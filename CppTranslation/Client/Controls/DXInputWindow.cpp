#include "DXInputWindow.h"
#include "DXScene.h"
#include "../Envir/CEnvir.h"

namespace Client::Controls
{
    DXInputWindow::DXInputWindow(const std::string& message, const std::string& caption)
        : Label(nullptr), ConfirmButton(nullptr), CancelButton(nullptr), ValueTextBox(nullptr)
    {
        SetHasFooter(true);

        // TitleLabel->SetText(caption);
        TitleLabel->Text = caption;

        // Parent = ActiveScene;
        // MessageBoxList.Add(this);
        if (ActiveScene != nullptr)
        {
            SetParent(ActiveScene);
        }
        // Note: MessageBoxList needs to be implemented globally or in a manager class

        Label = new DXLabel();
        Label->SetAutoSize(false);
        Label->SetLocation(Point{ 10, 35 });
        Label->SetParent(this);
        Label->SetText(message);
        // DrawFormat = TextFormatFlags.VerticalCenter | TextFormatFlags.WordBreak | TextFormatFlags.HorizontalCenter
        // Note: Need to implement DrawFormat equivalent
        
        // Calculate label size
        // Label->Size = new Size(300, DXLabel::GetHeight(Label, 300).Height);
        Label->SetSize(Size{ 300, 20 }); // Placeholder

        ValueTextBox = new DXTextBox();
        ValueTextBox->SetParent(this);
        ValueTextBox->SetSize(Size{ 200, 20 });
        ValueTextBox->SetLocation(Point{ 60, 45 + Label->GetSize().Height });
        // KeepFocus = true - need to implement
        // ValueTextBox->SetKeepFocus(true);
        
        // ValueTextBox->SetFocus();
        // ValueTextBox->TextBox.TextChanged += TextBox_TextChanged;
        // ValueTextBox->TextBox.KeyPress += (o, e) => OnKeyPress(e);

        // SetClientSize(new Size(300, Label.Size.Height + 30));
        SetClientSize(Size{ 300, Label->GetSize().Height + 30 });
        // Label.Location = ClientArea.Location;
        Label->SetLocation(GetClientArea().TopLeft());

        ConfirmButton = new DXButton();
        ConfirmButton->SetLocation(Point{ (GetSize().Width) / 2 - 80 - 10, GetSize().Height - 43 });
        ConfirmButton->SetSize(Size{ 80, 25 }); // DefaultHeight placeholder
        ConfirmButton->SetParent(this);
        // ConfirmButton->Label->Text = CEnvir.Language.CommonControlConfirm
        if (ConfirmButton->Label != nullptr)
        {
            // Need to access CEnvir::Language
            ConfirmButton->Label->Text = "Confirm"; // Placeholder
        }
        // ConfirmButton.MouseClick += (o, e) => Dispose();
        // Note: Event handling needs implementation

        CancelButton = new DXButton();
        CancelButton->SetLocation(Point{ GetSize().Width / 2 + 10, GetSize().Height - 43 });
        CancelButton->SetSize(Size{ 80, 25 }); // DefaultHeight placeholder
        CancelButton->SetParent(this);
        if (CancelButton->Label != nullptr)
        {
            CancelButton->Label->Text = "Cancel"; // Placeholder
        }
        // CancelButton.MouseClick += (o, e) => Dispose();

        // Center the window
        // Location = new Point((ActiveScene.DisplayArea.Width - DisplayArea.Width) / 2, 
        //                      (ActiveScene.DisplayArea.Height - DisplayArea.Height) / 2);
        if (ActiveScene != nullptr)
        {
            RECT sceneArea = ActiveScene->GetDisplayArea();
            RECT displayArea = GetDisplayArea();
            int x = (sceneArea.right - sceneArea.left - (displayArea.right - displayArea.left)) / 2;
            int y = (sceneArea.bottom - sceneArea.top - (displayArea.bottom - displayArea.top)) / 2;
            SetLocation(Point{ x, y });
        }
    }

    void DXInputWindow::OnKeyDown(KeyEventArgs& e)
    {
        DXWindow::OnKeyDown(e);
        e.Handled = true;
    }

    void DXInputWindow::OnKeyUp(KeyEventArgs& e)
    {
        DXWindow::OnKeyUp(e);
        e.Handled = true;
    }

    void DXInputWindow::OnKeyPress(KeyPressEventArgs& e)
    {
        DXWindow::OnKeyPress(e);

        char keyChar = e.KeyChar;
        
        // Handle Escape key
        if (keyChar == (char)Keys::Escape)
        {
            if (CancelButton != nullptr && !CancelButton->GetIsDisposed())
            {
                // CancelButton->InvokeMouseClick();
                // Note: InvokeMouseClick needs implementation
            }
            e.Handled = true;
            return;
        }
        
        // Handle Enter key
        if (keyChar == (char)Keys::Enter)
        {
            if (ConfirmButton != nullptr && !ConfirmButton->GetIsDisposed())
            {
                // ConfirmButton->InvokeMouseClick();
                // Note: InvokeMouseClick needs implementation
            }
            e.Handled = true;
            return;
        }
    }

    void DXInputWindow::TextBox_TextChanged(void* sender, void* e)
    {
        if (ValueTextBox != nullptr)
        {
            // Value = ValueTextBox->TextBox->Text;
            // Note: Need to access inner TextBox text
            Value = ValueTextBox->GetText();
        }
    }

    void DXInputWindow::Dispose(bool disposing)
    {
        DXWindow::Dispose(disposing);

        if (disposing)
        {
            if (Label != nullptr)
            {
                if (!Label->GetIsDisposed())
                    Label->Dispose();
                delete Label;
                Label = nullptr;
            }

            if (ConfirmButton != nullptr)
            {
                if (!ConfirmButton->GetIsDisposed())
                    ConfirmButton->Dispose();
                delete ConfirmButton;
                ConfirmButton = nullptr;
            }

            if (CancelButton != nullptr)
            {
                if (!CancelButton->GetIsDisposed())
                    CancelButton->Dispose();
                delete CancelButton;
                CancelButton = nullptr;
            }

            if (ValueTextBox != nullptr)
            {
                if (!ValueTextBox->GetIsDisposed())
                    ValueTextBox->Dispose();
                delete ValueTextBox;
                ValueTextBox = nullptr;
            }
        }
    }

} // namespace Client::Controls
