#include "DXWindow.h"
#include "DXButton.h"
#include "DXLabel.h"
#include "../Envir/CEnvir.h"
#include "../Envir/DXManager.h"
#include "../Envir/Config.h"

namespace Client::Controls
{
    // Static member initialization
    std::vector<DXWindow*> DXWindow::_Windows;

    // Static methods
    std::vector<DXWindow*>& DXWindow::GetWindows()
    {
        return _Windows;
    }

    DXWindow::DXWindow()
    {
        _Windows.push_back(this);

        DrawTexture = true;
        SetBackColour({ 16.0f/255.0f, 8.0f/255.0f, 8.0f/255.0f, 1.0f });
        SetHasTitle(true);
        SetMovable(true);
        SetHasTopBorder(true);
        SetSort(true);

        CloseButton = new DXButton();
        CloseButton->SetParent(this);
        CloseButton->SetIndex(15);
        // CloseButton->SetLibraryFile(LibraryFile::Interface);
        CloseButton->MouseClick = [this]() { SetIsVisible(false); };

        TitleLabel = new DXLabel();
        TitleLabel->SetParent(this);
        TitleLabel->SetText(L"Window");
        TitleLabel->SetFontColor({ 198.0f/255.0f, 166.0f/255.0f, 99.0f/255.0f, 1.0f });
        TitleLabel->SetOutline(true);
        TitleLabel->SetOutlineColour({ 0.0f, 0.0f, 0.0f, 1.0f });
        TitleLabel->SetIsVisible(GetHasTitle());
        TitleLabel->SetIsControl(false);
        
        TitleLabel->SizeChanged = [this]() {
            if (TitleLabel != nullptr)
            {
                SIZE labelSize = TitleLabel->GetSize();
                int windowWidth = GetSize().cx;
                TitleLabel->SetLocation({ (windowWidth - labelSize.cx) / 2, 8 });
            }
        };
    }

    DXWindow::~DXWindow()
    {
        Dispose(true);
    }

    void DXWindow::SetHasTopBorder(bool value)
    {
        if (_HasTopBorder == value) return;

        bool oldValue = _HasTopBorder;
        _HasTopBorder = value;

        OnHasTopBorderChanged(oldValue, value);
    }

    void DXWindow::SetHasTitle(bool value)
    {
        if (_HasTitle == value) return;

        bool oldValue = _HasTitle;
        _HasTitle = value;

        OnHasTitleChanged(oldValue, value);
    }

    void DXWindow::SetHasFooter(bool value)
    {
        if (_HasFooter == value) return;

        bool oldValue = _HasFooter;
        _HasFooter = value;

        OnHasFooterChanged(oldValue, value);
    }

    void DXWindow::SetClientArea(const RECT& value)
    {
        if (_ClientArea.left == value.left && _ClientArea.top == value.top &&
            _ClientArea.right == value.right && _ClientArea.bottom == value.bottom) return;

        RECT oldValue = _ClientArea;
        _ClientArea = value;

        OnClientAreaChanged(oldValue, value);
    }

    void DXWindow::OnHasTopBorderChanged(bool oValue, bool nValue)
    {
        if (HasTopBorderChanged)
            HasTopBorderChanged();

        UpdateClientArea();
    }

    void DXWindow::OnHasTitleChanged(bool oValue, bool nValue)
    {
        if (HasTitleChanged)
            HasTitleChanged();

        UpdateClientArea();
        
        if (TitleLabel != nullptr)
            TitleLabel->SetIsVisible(_HasTitle);
    }

    void DXWindow::OnHasFooterChanged(bool oValue, bool nValue)
    {
        if (HasFooterChanged)
            HasFooterChanged();

        UpdateClientArea();
    }

    void DXWindow::OnClientAreaChanged(const RECT& oValue, const RECT& nValue)
    {
        if (ClientAreaChanged)
            ClientAreaChanged();
    }

    void DXWindow::OnSizeChanged(const SIZE& oValue, const SIZE& nValue)
    {
        DXControl::OnSizeChanged(oValue, nValue);

        UpdateClientArea();
        UpdateLocations();

        if (Settings != nullptr && GetIsResizing())
        {
            Settings->Size = nValue;
            Settings->Location = GetLocation();
        }
    }

    void DXWindow::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        DXControl::OnParentChanged(oValue, nValue);

        if (nValue == nullptr) return;

        UpdateClientArea();
        UpdateLocations();
    }

    void DXWindow::OnLocationChanged(const POINT& oValue, const POINT& nValue)
    {
        DXControl::OnLocationChanged(oValue, nValue);

        if (Settings != nullptr && GetIsMoving())
            Settings->Location = nValue;
    }

    void DXWindow::OnVisibleChanged(bool oValue, bool nValue)
    {
        DXControl::OnVisibleChanged(oValue, nValue);
        
        if (nValue)
            BringToFront();

        if (Settings != nullptr && GetAutomaticVisibility())
            Settings->Visible = nValue;
    }

    void DXWindow::OnKeyDown(int keyCode, bool shift, bool alt, bool ctrl)
    {
        DXControl::OnKeyDown(keyCode, shift, alt, ctrl);

        // Handle Escape key
        if (keyCode == 27) // VK_ESCAPE
        {
            if (CloseButton != nullptr && CloseButton->GetIsVisible())
            {
                CloseButton->InvokeMouseClick();
                if (!Config::EscapeCloseAll)
                {
                    // Mark event as handled
                }
            }
        }
    }

    void DXWindow::ResolutionChanged()
    {
        Settings = nullptr;

        DXControl::ResolutionChanged();

        DisposeTexture();
    }

    void DXWindow::CreateTexture()
    {
        DXControl::CreateTexture();

        if (WindowTexture == nullptr || 
            (GetSize().cx != TextureSize.cx || GetSize().cy != TextureSize.cy))
        {
            // Create window texture using DXManager
            WindowTexture = DXManager::CreateTexture(
                DXManager::GetBackBufferWidth(), 
                DXManager::GetBackBufferHeight());
            
            // Get surface from texture
            WindowSurface = DXManager::GetSurfaceFromTexture(WindowTexture);
            WindowValid = false;
        }
    }

    void DXWindow::DisposeTexture()
    {
        DXControl::DisposeTexture();

        if (WindowTexture != nullptr)
        {
            DXManager::ReleaseTexture(WindowTexture);
            WindowTexture = nullptr;
        }

        if (WindowSurface != nullptr)
        {
            DXManager::ReleaseSurface(WindowSurface);
            WindowSurface = nullptr;
        }

        WindowValid = false;
    }

    void DXWindow::UpdateLocations()
    {
        if (CloseButton != nullptr)
        {
            SIZE closeSize = CloseButton->GetSize();
            int windowWidth = GetDisplayArea().right - GetDisplayArea().left;
            CloseButton->SetLocation({ windowWidth - closeSize.cx - 3, 3 });
        }

        if (TitleLabel != nullptr)
        {
            SIZE labelSize = TitleLabel->GetSize();
            int windowWidth = GetDisplayArea().right - GetDisplayArea().left;
            TitleLabel->SetLocation({ (windowWidth - labelSize.cx) / 2, 8 });
        }
    }

    void DXWindow::UpdateDisplayArea()
    {
        DXControl::UpdateDisplayArea();

        WindowValid = false;
    }

    void DXWindow::UpdateClientArea()
    {
        SetClientArea(GetClientAreaRect(GetSize()));
    }

    void DXWindow::SetClientSize(const SIZE& clientSize)
    {
        SetSize(GetSize(clientSize));
    }

    SIZE DXWindow::GetSize(const SIZE& clientSize)
    {
        int w = 3 + 6 + 6 + 3; // Border Padding Padding Border
        int h = 6 + 6; // Padding Padding

        int headerBarSize = 30; // Approximate header bar size

        if (!_HasTopBorder)
            h += 30; // NoFooterSize
        else if (_HasTitle)
            h += headerBarSize + 20; // HeaderSize
        else
            h += headerBarSize; // HeaderBarSize

        if (!_HasFooter)
            h += 30; // NoFooterSize
        else
            h += 30; // FooterSize

        return { clientSize.cx + w, clientSize.cy + h };
    }

    RECT DXWindow::GetClientAreaRect(const SIZE& size)
    {
        int x = 6 + 3;
        int y = 6;

        int headerBarSize = 30;

        if (!_HasTopBorder)
            y += 30; // NoFooterSize
        else if (_HasTitle)
            y += headerBarSize + 20; // HeaderSize
        else
            y += headerBarSize; // HeaderBarSize

        int w = size.cx - x * 2;
        int h = size.cy - y - 6;

        if (!_HasFooter)
            h -= 30; // NoFooterSize
        else
            h -= 30; // FooterSize

        return { x, y, x + w, y + h };
    }

    void DXWindow::Draw()
    {
        if (!GetIsVisible() || GetSize().cx == 0 || GetSize().cy == 0) return;

        // OnBeforeDraw();
        DrawControl();
        DrawWindow();
        // OnBeforeChildrenDraw();
        DrawChildControls();
        DrawBorder();
        // OnAfterDraw();
    }

    void DXWindow::DrawWindow()
    {
        // Interface library drawing would go here
        if (!WindowValid)
        {
            void* oldSurface = DXManager::GetCurrentSurface();
            DXManager::SetCurrentSurface(WindowSurface);
            
            // Clear surface
            DXManager::ClearSurface(WindowSurface, 0, 0, 0, 0);

            DrawEdges();

            DXManager::SetCurrentSurface(oldSurface);
            WindowValid = true;
        }

        float oldOpacity = DXManager::GetOpacity();
        DXManager::SetOpacity(GetOpacity());
        
        // Present window texture
        DXManager::PresentTexture(WindowTexture, GetParent(), GetDisplayArea(), 
                                  GetIsEnabled() ? D2D1::ColorF(1, 1, 1, 1) : D2D1::ColorF(0.75f, 0.75f, 0.75f, 1), 
                                  this);

        DXManager::SetOpacity(oldOpacity);
    }

    void DXWindow::DrawEdges()
    {
        // Edge drawing implementation would use InterfaceLibrary
        // This is a placeholder for the actual drawing logic
        SIZE s;

        if (_HasTopBorder)
        {
            // Draw top border with title
            s = { 100, 30 }; // Placeholder size
            // InterfaceLibrary.Draw(0, 0, 0, Color.White, Rectangle(0, 0, Size.Width, s.Height), 1f, ImageType.Image);
        }
        else
        {
            // Draw top border without title
            s = { 100, 20 }; // Placeholder size
            // InterfaceLibrary.Draw(2, 0, 0, Color.White, Rectangle(0, 0, Size.Width, s.Height), 1f, ImageType.Image);
        }

        int y = s.cy;

        s = { 6, 100 }; // Side border size
        // Draw left and right borders
        // InterfaceLibrary.Draw(1, 0, y, Color.White, Rectangle(0, 0, s.Width, Size.Height - y), 1f, ImageType.Image);
        // InterfaceLibrary.Draw(1, Size.Width - s.Width, y, Color.White, Rectangle(0, 0, s.Width, Size.Height - y), 1F, ImageType.Image);

        // Additional edge drawing logic...
    }

    void DXWindow::LoadSettings()
    {
        // Window type check
        if (GetType() == WindowType::None || !CEnvir::GetLoaded()) return;

        // Load settings from CEnvir
        // Settings = CEnvir.WindowSettings.Binding.FirstOrDefault(x => x.Resolution == Config.GameSize && x.Window == Type);

        if (Settings != nullptr)
        {
            ApplySettings();
            return;
        }

        UpdateSettings();
    }

    void DXWindow::UpdateSettings()
    {
        if (Settings == nullptr)
        {
            // Create new settings object
            // Settings = CEnvir.WindowSettings.CreateNewObject();
        }

        // Settings->Resolution = Config.GameSize;
        // Settings->Window = GetType();
        Settings->Size = GetSize();
        Settings->Visible = GetIsVisible();
        Settings->Location = GetLocation();
    }

    void DXWindow::ApplySettings()
    {
        if (Settings == nullptr) return;

        SetLocation(Settings->Location);

        if (GetAutomaticVisibility())
            SetIsVisible(Settings->Visible);

        if (GetCustomSize())
            SetSize(Settings->Size);
    }

    void DXWindow::DrawControl()
    {
        // Call base class implementation
        DXControl::DrawControl();
    }

    void DXWindow::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            _HasTopBorder = false;
            _HasTitle = false;
            _HasFooter = false;
            _ClientArea = { 0, 0, 0, 0 };

            if (CloseButton != nullptr)
            {
                delete CloseButton;
                CloseButton = nullptr;
            }

            if (TitleLabel != nullptr)
            {
                delete TitleLabel;
                TitleLabel = nullptr;
            }

            HasTopBorderChanged = nullptr;
            HasTitleChanged = nullptr;
            HasFooterChanged = nullptr;
            ClientAreaChanged = nullptr;

            if (WindowTexture != nullptr)
            {
                DXManager::ReleaseTexture(WindowTexture);
                WindowTexture = nullptr;
            }

            if (WindowSurface != nullptr)
            {
                DXManager::ReleaseSurface(WindowSurface);
                WindowSurface = nullptr;
            }

            WindowValid = false;
            Settings = nullptr;
            
            // Remove from windows list
            auto it = std::find(_Windows.begin(), _Windows.end(), this);
            if (it != _Windows.end())
                _Windows.erase(it);
        }
    }
}
