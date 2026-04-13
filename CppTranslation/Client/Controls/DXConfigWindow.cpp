#include "DXConfigWindow.h"

namespace Client::Controls
{
    // Static member initialization
    DXConfigWindow* DXConfigWindow::ActiveConfig = nullptr;

    void DXConfigWindow::OnVisibleChanged(bool oValue, bool nValue)
    {
        DXWindow::OnVisibleChanged(oValue, nValue);

        if (!GetIsVisible()) return;

        // Graphics settings would be applied here when visible
        // FullScreenCheckBox->SetChecked(Config.FullScreen);
        // etc.
    }

    void DXConfigWindow::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        DXWindow::OnParentChanged(oValue, nValue);

        if (KeyBindWindow != nullptr)
            KeyBindWindow->SetParent(nValue);
    }

    DXConfigWindow::DXConfigWindow()
    {
        ActiveConfig = this;

        SetSize(Size(300, 355));
        // TitleLabel->SetText(CEnvir::Language.CommonControlConfigWindowTitle);
        SetHasFooter(true);

        TabControl = new DXTabControl();
        TabControl->SetParent(this);
        TabControl->SetLocation(GetClientArea().Location);
        TabControl->SetSize(GetClientArea().Size);

        // Graphics Tab
        GraphicsTab = new DXTab();
        GraphicsTab->SetParent(TabControl);
        GraphicsTab->SetBorder(true);
        // GraphicsTab->GetTabButton()->GetLabel()->SetText(CEnvir::Language.CommonControlConfigWindowGraphicsTabLabel);

        // Sound Tab
        SoundTab = new DXTab();
        SoundTab->SetParent(TabControl);
        SoundTab->SetBorder(true);
        // SoundTab->GetTabButton()->GetLabel()->SetText(CEnvir::Language.CommonControlConfigWindowSoundTabLabel);

        // Game Tab
        GameTab = new DXTab();
        GameTab->SetParent(TabControl);
        GameTab->SetBorder(true);
        // GameTab->GetTabButton()->GetLabel()->SetText(CEnvir::Language.CommonControlConfigWindowGameTabLabel);

        // Network Tab
        NetworkTab = new DXTab();
        NetworkTab->SetParent(TabControl);
        NetworkTab->SetBorder(true);
        // NetworkTab->GetTabButton()->GetLabel()->SetText(CEnvir::Language.CommonControlConfigWindowNetworkTabLabel);

        // Colour Tab
        ColourTab = new DXTab();
        ColourTab->SetParent(TabControl);
        ColourTab->SetBorder(true);
        // ColourTab->GetTabButton()->GetLabel()->SetText(CEnvir::Language.CommonControlConfigWindowColoursTabLabel);
        ColourTab->GetTabButton()->GetLabel()->SetVisible(false);

        KeyBindWindow = new DXKeyBindWindow();
        KeyBindWindow->SetVisible(false);

        // Initialize buttons
        SaveButton = new DXButton();
        CancelButton = new DXButton();
        ResetColoursButton = new DXButton();
        KeyBindButton = new DXButton();

        // Note: Full UI initialization would continue here with all controls
        // This is a skeleton translation - full implementation requires Config and CEnvir classes
    }

    DXConfigWindow::~DXConfigWindow()
    {
        Dispose(true);
    }

    void DXConfigWindow::Dispose(bool disposing)
    {
        DXWindow::Dispose(disposing);

        if (disposing)
        {
            if (TabControl != nullptr && !TabControl->GetIsDisposed())
                delete TabControl;
            
            if (KeyBindWindow != nullptr && !KeyBindWindow->GetIsDisposed())
                delete KeyBindWindow;
            
            if (SaveButton != nullptr && !SaveButton->GetIsDisposed())
                delete SaveButton;
            
            if (CancelButton != nullptr && !CancelButton->GetIsDisposed())
                delete CancelButton;
            
            if (ResetColoursButton != nullptr && !ResetColoursButton->GetIsDisposed())
                delete ResetColoursButton;
            
            if (KeyBindButton != nullptr && !KeyBindButton->GetIsDisposed())
                delete KeyBindButton;

            ActiveConfig = nullptr;
        }
    }
}
