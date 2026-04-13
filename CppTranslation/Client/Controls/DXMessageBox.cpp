#include "DXMessageBox.h"
#include "CEnvir.h"

namespace Client::Controls
{
    // DXMessageBox Implementation

    void DXMessageBox::OnSizeChanged(const Size& oValue, const Size& nValue)
    {
        DXWindow::OnSizeChanged(oValue, nValue);

        if (Parent != nullptr)
            SetLocation(Point((Parent->DisplayArea.Width - DisplayArea.Width) / 2, 
                              (Parent->DisplayArea.Height - DisplayArea.Height) / 2));

        if (Label != nullptr)
            Label->SetLocation(ClientArea.Location);

        if (OKButton != nullptr)
            OKButton->SetLocation(Point(OKButton->GetLocation().X, nValue.Height - 44));
        
        if (CancelButton != nullptr)
            CancelButton->SetLocation(Point(CancelButton->GetLocation().X, nValue.Height - 44));
        
        if (NoButton != nullptr)
            NoButton->SetLocation(Point(NoButton->GetLocation().X, nValue.Height - 44));
        
        if (YesButton != nullptr)
            YesButton->SetLocation(Point(YesButton->GetLocation().X, nValue.Height - 44));
    }

    void DXMessageBox::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        DXWindow::OnParentChanged(oValue, nValue);

        if (Parent == nullptr)
            return;

        SetLocation(Point((Parent->DisplayArea.Width - DisplayArea.Width) / 2, 
                          (Parent->DisplayArea.Height - DisplayArea.Height) / 2));
    }

    void DXMessageBox::OnIsVisibleChanged(bool oValue, bool nValue)
    {
        DXWindow::OnIsVisibleChanged(oValue, nValue);

        if (IsVisible)
        {
            HiddenBox = DXTextBox::ActiveTextBox;
            DXTextBox::ActiveTextBox = nullptr;
        }
        else if (HiddenBox != nullptr)
        {
            DXTextBox::ActiveTextBox = HiddenBox;
        }
    }

    WindowType DXMessageBox::GetType() const
    {
        return WindowType::MessageBox;
    }

    bool DXMessageBox::GetCustomSize() const
    {
        return false;
    }

    bool DXMessageBox::GetAutomaticVisibility() const
    {
        return false;
    }

    DXMessageBox::DXMessageBox(const std::string& message, const std::string& caption, DXMessageBoxButtons buttons)
    {
        Buttons = buttons;
        Modal = true;
        HasFooter = true;

        TitleLabel->SetText(caption);

        Parent = ActiveScene;
        MessageBoxList.push_back(this);

        Label = new DXLabel();
        Label->AutoSize = false;
        Label->SetLocation(Point(10, 35));
        Label->Parent = this;
        Label->SetText(message);
        Label->DrawFormat = TextFormatFlags::VerticalCenter | TextFormatFlags::HorizontalCenter;
        
        Size labelSize = DXLabel::GetSize(message, Label->GetFont(), Label->Outline);
        Label->SetSize(Size(380, labelSize.Height));
        SetClientSize(Label->GetSize());
        Label->SetLocation(ClientArea.Location);

        SetLocation(Point((ActiveScene->DisplayArea.Width - DisplayArea.Width) / 2, 
                          (ActiveScene->DisplayArea.Height - DisplayArea.Height) / 2));

        switch (Buttons)
        {
            case DXMessageBoxButtons::OK:
                OKButton = new DXButton();
                OKButton->SetLocation(Point((GetSize().Width - 80) / 2, GetSize().Height - 43));
                OKButton->SetSize(Size(80, DefaultHeight));
                OKButton->Parent = this;
                OKButton->Label->SetText(CEnvir::Language.CommonControlOk);
                OKButton->MouseClick += [this](void* sender, MouseEventArgs* e) { Dispose(); };
                break;

            case DXMessageBoxButtons::YesNo:
                YesButton = new DXButton();
                YesButton->SetLocation(Point((GetSize().Width) / 2 - 80 - 10, GetSize().Height - 43));
                YesButton->SetSize(Size(80, DefaultHeight));
                YesButton->Parent = this;
                YesButton->Label->SetText(CEnvir::Language.CommonControlYes);
                YesButton->MouseClick += [this](void* sender, MouseEventArgs* e) { Dispose(); };
                
                NoButton = new DXButton();
                NoButton->SetLocation(Point(GetSize().Width / 2 + 10, GetSize().Height - 43));
                NoButton->SetSize(Size(80, DefaultHeight));
                NoButton->Parent = this;
                NoButton->Label->SetText(CEnvir::Language.CommonControlNo);
                NoButton->MouseClick += [this](void* sender, MouseEventArgs* e) { Dispose(); };
                break;

            case DXMessageBoxButtons::Cancel:
                CancelButton = new DXButton();
                CancelButton->SetLocation(Point((GetSize().Width - 80) / 2, GetSize().Height - 43));
                CancelButton->SetSize(Size(80, DefaultHeight));
                CancelButton->Parent = this;
                CancelButton->Label->SetText(CEnvir::Language.CommonControlCancel);
                CancelButton->MouseClick += [this](void* sender, MouseEventArgs* e) { Dispose(); };
                break;

            default:
                break;
        }

        BringToFront();
    }

    DXMessageBox* DXMessageBox::Show(const std::string& message, const std::string& caption, DialogAction action)
    {
        DXMessageBox* box = new DXMessageBox(message, caption);

        switch (action)
        {
            case DialogAction::None:
                break;

            case DialogAction::Close:
                box->OKButton->MouseClick += [](void* sender, MouseEventArgs* e) { CEnvir::Target->Close(); };
                box->CloseButton->MouseClick += [](void* sender, MouseEventArgs* e) { CEnvir::Target->Close(); };
                break;

            case DialogAction::ReturnToLogin:
                box->OKButton->MouseClick += [](void* sender, MouseEventArgs* e) { CEnvir::ReturnToLogin(); };
                box->CloseButton->MouseClick += [](void* sender, MouseEventArgs* e) { CEnvir::ReturnToLogin(); };
                break;
        }

        return box;
    }

    void DXMessageBox::OnKeyPress(KeyPressEventArgs* e)
    {
        DXWindow::OnKeyPress(e);

        if (e->KeyChar == static_cast<char>(Keys::Escape))
        {
            switch (Buttons)
            {
                case DXMessageBoxButtons::OK:
                    if (OKButton != nullptr && !OKButton->IsDisposed)
                        OKButton->InvokeMouseClick();
                    break;

                case DXMessageBoxButtons::YesNo:
                    if (NoButton != nullptr && !NoButton->IsDisposed)
                        NoButton->InvokeMouseClick();
                    break;
            }
            e->Handled = true;
        }
        else if (e->KeyChar == static_cast<char>(Keys::Enter))
        {
            switch (Buttons)
            {
                case DXMessageBoxButtons::OK:
                    if (OKButton != nullptr && !OKButton->IsDisposed)
                        OKButton->InvokeMouseClick();
                    break;

                case DXMessageBoxButtons::YesNo:
                    if (YesButton != nullptr && !YesButton->IsDisposed)
                        YesButton->InvokeMouseClick();
                    break;
            }
            e->Handled = true;
        }
    }

    void DXMessageBox::ResolutionChanged()
    {
        DXWindow::ResolutionChanged();

        if (Parent != nullptr)
            SetLocation(Point((Parent->DisplayArea.Width - DisplayArea.Width) / 2, 
                              (Parent->DisplayArea.Height - DisplayArea.Height) / 2));
    }

    void DXMessageBox::Dispose(bool disposing)
    {
        DXWindow::Dispose(disposing);

        if (disposing)
        {
            if (Label != nullptr)
            {
                if (!Label->IsDisposed)
                    Label->Dispose();
                Label = nullptr;
            }

            if (OKButton != nullptr)
            {
                if (!OKButton->IsDisposed)
                    OKButton->Dispose();
                OKButton = nullptr;
            }

            if (CancelButton != nullptr)
            {
                if (!CancelButton->IsDisposed)
                    CancelButton->Dispose();
                CancelButton = nullptr;
            }

            if (NoButton != nullptr)
            {
                if (!NoButton->IsDisposed)
                    NoButton->Dispose();
                NoButton = nullptr;
            }

            if (YesButton != nullptr)
            {
                if (!YesButton->IsDisposed)
                    YesButton->Dispose();
                YesButton = nullptr;
            }

            if (HiddenBox != nullptr)
            {
                DXTextBox::ActiveTextBox = HiddenBox;
                HiddenBox = nullptr;
            }

            Buttons = DXMessageBoxButtons::None;
            
            auto it = std::find(MessageBoxList.begin(), MessageBoxList.end(), this);
            if (it != MessageBoxList.end())
                MessageBoxList.erase(it);
        }
    }
}
