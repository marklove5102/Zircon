#include "DXButton.h"

namespace Client::Controls
{
    DXButton::DXButton()
    {
        _HasFocus = false;
        _Pressed = false;
        _CanBePressed = false;
        _RightAligned = false;
        _ButtonType = ButtonType::Default;
        _HoverIndex = 0;
        _PressedIndex = 0;
        
        SetForeColour(Color::White());
        // Sound = SoundIndex.ButtonA; // Requires SoundIndex enum
        SetCanBePressed(true);
        SetForeColour(Color4(0.85f, 0.85f, 0.85f).ToColor());

        Label = new DXLabel();
        Label->SetLocation(Point(0, -1));
        Label->SetAutoSize(false);
        Label->SetDrawFormat(TextFormatFlags::HorizontalCenter | TextFormatFlags::VerticalCenter);
        Label->SetIsControl(false);
        Label->SetParent(this);
    }

    DXButton::~DXButton()
    {
        Dispose(true);
    }

    void DXButton::SetHasFocus(bool value)
    {
        if (_HasFocus == value) return;

        bool oldValue = _HasFocus;
        _HasFocus = value;

        OnHasFocusChanged(oldValue, value);
    }

    void DXButton::OnHasFocusChanged(bool oValue, bool nValue)
    {
        UpdateDisplayArea();
        if (HasFocusChanged) HasFocusChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetPressed(bool value)
    {
        if (_Pressed == value) return;

        bool oldValue = _Pressed;
        _Pressed = value;

        OnPressedChanged(oldValue, value);
    }

    void DXButton::OnPressedChanged(bool oValue, bool nValue)
    {
        UpdateForeColour();
        if (PressedChanged) PressedChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetCanBePressed(bool value)
    {
        if (_CanBePressed == value) return;

        bool oldValue = _CanBePressed;
        _CanBePressed = value;

        OnCanBePressedChanged(oldValue, value);
    }

    void DXButton::OnCanBePressedChanged(bool oValue, bool nValue)
    {
        if (CanBePressedChanged) CanBePressedChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetRightAligned(bool value)
    {
        if (_RightAligned == value) return;

        bool oldValue = _RightAligned;
        _RightAligned = value;

        OnRightAlignedChanged(oldValue, value);
    }

    void DXButton::OnRightAlignedChanged(bool oValue, bool nValue)
    {
        if (RightAlignedChanged) RightAlignedChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetButtonType(ButtonType value)
    {
        if (_ButtonType == value) return;

        ButtonType oldValue = _ButtonType;
        _ButtonType = value;

        OnButtonTypeChanged(oldValue, value);
    }

    void DXButton::OnButtonTypeChanged(ButtonType oValue, ButtonType nValue)
    {
        if (Label == nullptr) return;
        
        switch (nValue)
        {
            case ButtonType::SmallButton:
                Label->SetLocation(Point(0, -1));
                break;
            default:
                Label->SetLocation(Point(0, 0));
                break;
        }

        if (ButtonTypeChanged) ButtonTypeChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetHoverIndex(int value)
    {
        if (_HoverIndex == value) return;

        int oldValue = _HoverIndex;
        _HoverIndex = value;

        OnHoverIndexChanged(oldValue, value);
    }

    void DXButton::OnHoverIndexChanged(int oValue, int nValue)
    {
        SetTextureValid(false);
        UpdateDisplayArea();
        if (HoverIndexChanged) HoverIndexChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::SetPressedIndex(int value)
    {
        if (_PressedIndex == value) return;

        int oldValue = _PressedIndex;
        _PressedIndex = value;

        OnPressedIndexChanged(oldValue, value);
    }

    void DXButton::OnPressedIndexChanged(int oValue, int nValue)
    {
        SetTextureValid(false);
        UpdateDisplayArea();
        if (PressedIndexChanged) PressedIndexChanged->Invoke(this, EventArgs::Empty());
    }

    void DXButton::OnIsEnabledChanged(bool oValue, bool nValue)
    {
        DXImageControl::OnIsEnabledChanged(oValue, nValue);

        UpdateForeColour();
        UpdateDisplayArea();
    }

    void DXButton::OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue)
    {
        DXImageControl::OnDisplayAreaChanged(oValue, nValue);

        if (Label == nullptr) return;

        Label->SetSize(GetDisplayArea().Size);
    }

    void DXButton::OnOpacityChanged(float oValue, float nValue)
    {
        DXImageControl::OnOpacityChanged(oValue, nValue);

        if (Label == nullptr) return;

        Label->SetOpacity(GetOpacity());
    }

    void DXButton::UpdateDisplayArea()
    {
        Rectangle area(GetLocation(), GetSize());

        if (GetParent() != nullptr)
            area.Offset(GetParent()->GetDisplayArea().Location);

        if (GetHasFocus() && MouseControl == this && !GetPressed() && GetIsEnabled() && GetCanBePressed())
            area.Y++;

        SetDisplayArea(area);
    }

    void DXButton::DrawMirTexture()
    {
        Texture* texture = nullptr;

        if (GetLibrary() == nullptr)
        {
            DXManager::SetOpacity(GetOpacity());
            
            Surface* oldSurface = DXManager::GetCurrentSurface();
            DXManager::SetSurface(DXManager::GetScratchSurface());
            DXManager::GetDevice()->Clear(ClearFlags::Target, 0, 0, 0);

            switch (GetButtonType())
            {
                case ButtonType::Default:
                    DrawDefault();
                    break;
                case ButtonType::SelectedTab:
                    DrawSelectedTab();
                    break;
                case ButtonType::DeselectedTab:
                    DrawDeselectedTab();
                    break;
                case ButtonType::SmallButton:
                    DrawSmallButton();
                    break;
                case ButtonType::AddButton:
                    // InterfaceLibrary.Draw(241, 0, 0, Color.White, false, 1F, ImageType.Image);
                    break;
                case ButtonType::RemoveButton:
                    // InterfaceLibrary.Draw(242, 0, 0, Color.White, false, 1F, ImageType.Image);
                    break;
                case ButtonType::LFGButton:
                    // InterfaceLibrary.Draw(243, 0, 0, Color.White, false, 1F, ImageType.Image);
                    break;
                case ButtonType::SearchButton:
                    // InterfaceLibrary.Draw(244, 0, 0, Color.White, false, 1F, ImageType.Image);
                    break;
                case ButtonType::OptionsButton:
                    // InterfaceLibrary.Draw(245, 0, 0, Color.White, false, 1F, ImageType.Image);
                    break;
            }

            DXManager::SetSurface(oldSurface);

            texture = DXManager::GetScratchTexture();
        }
        else
        {
            int index = GetIndex();

            if (GetHoverIndex() > 0 && MouseControl == this && GetIsEnabled() && GetCanBePressed())
                index = GetHoverIndex();

            if (GetPressedIndex() > 0 && GetPressed() && GetIsEnabled())
                index = GetPressedIndex();

            if (index > 0)
            {
                // MirImage image = Library.CreateImage(index, ImageType.Image);
                // texture = image.Image;
                // image.ExpireTime = CEnvir.Now + Config.CacheDuration;
            }
        }

        if (texture == nullptr) return;

        bool oldBlend = DXManager::GetBlending();
        float oldRate = DXManager::GetBlendRate();

        if (GetBlend())
            DXManager::SetBlend(true, GetImageOpacity(), GetBlendMode());
        else
            DXManager::SetOpacity(GetOpacity());

        PresentTexture(texture, GetParent(), GetDisplayArea(), GetForeColour(), this, 0, GetPressed() ? 1 : 0);
        
        if (GetBlend())
            DXManager::SetBlend(oldBlend, oldRate, GetBlendMode());
        else
            DXManager::SetOpacity(1.0f);
    }

    void DXButton::OnFocus()
    {
        DXImageControl::OnFocus();
        SetHasFocus(true);
    }

    void DXButton::OnLostFocus()
    {
        DXImageControl::OnFocus(); // Note: C# code calls OnFocus() here, might be a bug
        SetHasFocus(false);
    }

    void DXButton::OnMouseEnter()
    {
        DXImageControl::OnMouseEnter();
        UpdateForeColour();
        UpdateDisplayArea();
    }

    void DXButton::OnMouseLeave()
    {
        DXImageControl::OnMouseLeave();
        UpdateForeColour();
        UpdateDisplayArea();
    }

    void DXButton::UpdateForeColour()
    {
        if (!GetIsEnabled())
            SetForeColour(Color4(0.2f, 0.2f, 0.2f).ToColor());
        else
            SetForeColour(MouseControl == this || GetPressed() ? 
                Color4(1.0f, 1.0f, 1.0f).ToColor() : 
                Color4(0.85f, 0.85f, 0.85f).ToColor());
    }

    void DXButton::DrawDefault()
    {
        // Size s = InterfaceLibrary.GetSize(16);
        // int x = s.Width;
        // s = InterfaceLibrary.GetSize(18);
        // InterfaceLibrary.Draw(18, x, 0, Color.White, new Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1f, ImageType.Image);
        // InterfaceLibrary.Draw(16, 0, 0, Color.White, false, 1F, ImageType.Image);
        // s = InterfaceLibrary.GetSize(17);
        // InterfaceLibrary.Draw(17, GetSize().Width - s.Width, 0, Color.White, false, 1F, ImageType.Image);
    }

    void DXButton::DrawSelectedTab()
    {
        // Size s = InterfaceLibrary.GetSize(56);
        // InterfaceLibrary.Draw(56, 0, 0, Color.White, false, 1F, ImageType.Image);
        // int x = s.Width;
        // s = InterfaceLibrary.GetSize(58);
        // InterfaceLibrary.Draw(58, x, 0, Color.White, new Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1f, ImageType.Image);
        // s = InterfaceLibrary.GetSize(57);
        // InterfaceLibrary.Draw(57, GetSize().Width - s.Width, 0, Color.White, false, 1F, ImageType.Image);
    }

    void DXButton::DrawDeselectedTab()
    {
        // Size s = InterfaceLibrary.GetSize(53);
        // InterfaceLibrary.Draw(53, 0, 0, Color.White, false, 1F, ImageType.Image);
        // int x = s.Width;
        // s = InterfaceLibrary.GetSize(55);
        // InterfaceLibrary.Draw(55, x, 0, Color.White, new Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1f, ImageType.Image);
        // s = InterfaceLibrary.GetSize(54);
        // InterfaceLibrary.Draw(54, GetSize().Width - s.Width, 0, Color.White, false, 1F, ImageType.Image);
    }

    void DXButton::DrawSmallButton()
    {
        // Size s = InterfaceLibrary.GetSize(41);
        // InterfaceLibrary.Draw(41, 0, 0, Color.White, false, 1F, ImageType.Image);
        // int x = s.Width;
        // s = InterfaceLibrary.GetSize(43);
        // InterfaceLibrary.Draw(43, x, 0, Color.White, new Rectangle(0, 0, GetSize().Width - x * 2, s.Height), 1f, ImageType.Image);
        // s = InterfaceLibrary.GetSize(42);
        // InterfaceLibrary.Draw(42, GetSize().Width - s.Width, 0, Color.White, false, 1F, ImageType.Image);
    }

    void DXButton::Dispose(bool disposing)
    {
        DXImageControl::Dispose(disposing);

        if (disposing)
        {
            _HasFocus = false;
            _Pressed = false;
            _CanBePressed = false;
            _RightAligned = false;
            _ButtonType = ButtonType::Default;
            _HoverIndex = 0;
            _PressedIndex = 0;

            if (Label != nullptr)
            {
                if (!Label->GetIsDisposed())
                    Label->Dispose();

                delete Label;
                Label = nullptr;
            }

            HasFocusChanged.reset();
            CanBePressedChanged.reset();
            PressedChanged.reset();
            RightAlignedChanged.reset();
            ButtonTypeChanged.reset();
            HoverIndexChanged.reset();
            PressedIndexChanged.reset();
        }
    }
}
