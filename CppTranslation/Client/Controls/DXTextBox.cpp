#include "DXTextBox.h"
#include "../Envir/CEnvir.h"
#include "../Envir/DXManager.h"
#include "../Envir/Config.h"
#include <algorithm>

namespace Client::Controls
{
    // Static member initialization
    DXTextBox* DXTextBox::_ActiveTextBox = nullptr;

    // Static methods
    DXTextBox* DXTextBox::GetActiveTextBox()
    {
        return _ActiveTextBox;
    }

    void DXTextBox::SetActiveTextBox(DXTextBox* value)
    {
        if (_ActiveTextBox == value) return;

        DXTextBox* oldValue = _ActiveTextBox;
        _ActiveTextBox = value;

        if (oldValue != nullptr)
            oldValue->OnDeactivated();
        
        if (_ActiveTextBox != nullptr)
            _ActiveTextBox->OnActivated();
    }

    DXTextBox::DXTextBox()
    {
        DrawTexture = true;

        _TextBox = new MirTextBox(this);

        Border = true;
        BorderColour = { 198.0f/255.0f, 166.0f/255.0f, 99.0f/255.0f, 1.0f };

        // Font will be initialized by system
        SetEditable(true);
    }

    DXTextBox::~DXTextBox()
    {
        Dispose(true);
    }

    void DXTextBox::SetEditable(bool value)
    {
        if (_Editable == value) return;

        bool oldValue = _Editable;
        _Editable = value;

        OnEditableChanged(oldValue, value);
    }

    void DXTextBox::SetFont(void* value)
    {
        if (_Font == value) return;

        void* oldValue = _Font;
        _Font = value;

        OnFontChanged(oldValue, value);
    }

    void DXTextBox::SetKeepFocus(bool value)
    {
        if (_KeepFocus == value) return;

        bool oldValue = _KeepFocus;
        _KeepFocus = value;

        OnKeepFocusChanged(oldValue, value);
    }

    void DXTextBox::SetMaxLength(int value)
    {
        if (_MaxLength == value) return;

        int oldValue = _MaxLength;
        _MaxLength = value;

        OnMaxLengthChanged(oldValue, value);
    }

    void DXTextBox::SetPassword(bool value)
    {
        if (_Password == value) return;

        bool oldValue = _Password;
        _Password = value;

        OnPasswordChanged(oldValue, value);
    }

    void DXTextBox::SetReadOnly(bool value)
    {
        if (_ReadOnly == value) return;

        bool oldValue = _ReadOnly;
        _ReadOnly = value;

        OnReadOnlyChanged(oldValue, value);
    }

    void DXTextBox::OnEditableChanged(bool oValue, bool nValue)
    {
        if (EditableChanged)
            EditableChanged();

        CheckFocus();
    }

    void DXTextBox::OnFontChanged(void* oValue, void* nValue)
    {
        if (FontChanged)
            FontChanged();

        // Apply font to TextBox if needed
    }

    void DXTextBox::OnKeepFocusChanged(bool oValue, bool nValue)
    {
        if (KeepFocusChanged)
            KeepFocusChanged();
    }

    void DXTextBox::OnMaxLengthChanged(int oValue, int nValue)
    {
        if (MaxLengthChanged)
            MaxLengthChanged();

        // Apply max length to TextBox
    }

    void DXTextBox::OnPasswordChanged(bool oValue, bool nValue)
    {
        if (PasswordChanged)
            PasswordChanged();

        // Apply password mode to TextBox
    }

    void DXTextBox::OnReadOnlyChanged(bool oValue, bool nValue)
    {
        if (ReadOnlyChanged)
            ReadOnlyChanged();

        // Apply read-only to TextBox
    }

    void DXTextBox::OnTextBoxChanged(MirTextBox* oValue, MirTextBox* nValue)
    {
        if (TextBoxChanged)
            TextBoxChanged();
    }

    void DXTextBox::OnBackColourChanged(const D2D1_COLOR_F& oValue, const D2D1_COLOR_F& nValue)
    {
        DXControl::OnBackColourChanged(oValue, nValue);

        // Apply back colour to TextBox
    }

    void DXTextBox::OnForeColourChanged(const D2D1_COLOR_F& oValue, const D2D1_COLOR_F& nValue)
    {
        DXControl::OnForeColourChanged(oValue, nValue);

        if (_TextBox == nullptr) return;

        // Apply fore colour to TextBox
    }

    void DXTextBox::OnDisplayAreaChanged(const RECT& oValue, const RECT& nValue)
    {
        DXControl::OnDisplayAreaChanged(oValue, nValue);

        if (_TextBox == nullptr || !_TextBox->GetVisible()) return;

        // Update TextBox location
    }

    void DXTextBox::OnSizeChanged(const SIZE& oValue, const SIZE& nValue)
    {
        DXControl::OnSizeChanged(oValue, nValue);

        if (_TextBox == nullptr) return;

        // Update TextBox size
    }

    void DXTextBox::OnIsVisibleChanged(bool oValue, bool nValue)
    {
        DXControl::OnIsVisibleChanged(oValue, nValue);

        CheckFocus();
    }

    void DXTextBox::OnIsEnabledChanged(bool oValue, bool nValue)
    {
        DXControl::OnIsEnabledChanged(oValue, nValue);

        CheckFocus();
    }

    void DXTextBox::CreateTexture()
    {
        if (ControlTexture == nullptr || 
            (DisplayArea.right - DisplayArea.left) != TextureSize.cx || 
            (DisplayArea.bottom - DisplayArea.top) != TextureSize.cy)
        {
            DisposeTexture();
            TextureSize.cx = DisplayArea.right - DisplayArea.left;
            TextureSize.cy = DisplayArea.bottom - DisplayArea.top;
            
            // Create texture using DXManager
            ControlTexture = DXManager::CreateTexture(TextureSize.cx, TextureSize.cy);
            DXManager::AddControl(this);
        }

        // Lock texture and draw TextBox content
        // This would need DirectX implementation
        
        TextureValid = true;
        ExpireTime = CEnvir::GetNow() + Config::CacheDuration;
    }

    void DXTextBox::OnActivated()
    {
        if (_TextBox != nullptr)
        {
            bool shouldBeVisible = GetEditable();
            if (_TextBox->GetVisible() != shouldBeVisible)
                _TextBox->SetVisible(shouldBeVisible);

            // Update location if needed
        }

        if (_TextBox != nullptr && _TextBox->GetVisible())
        {
            // Set as active control
            CEnvir::SetActiveControl(_TextBox);
        }
    }

    void DXTextBox::OnDeactivated()
    {
        if (_TextBox != nullptr)
        {
            if (_TextBox->GetVisible())
                TextureValid = false;

            _TextBox->SetVisible(false);
        }

        CEnvir::SetActiveControl(nullptr);
    }

    void DXTextBox::OnMouseEnter()
    {
        DXControl::OnMouseEnter();

        if (GetIsEnabled() && GetEditable())
        {
            // Set cursor to IBeam
            CEnvir::SetCursor(1); // IBeam cursor
        }
    }

    void DXTextBox::OnMouseLeave()
    {
        DXControl::OnMouseLeave();

        // Reset cursor to default
        CEnvir::SetCursor(0); // Default cursor
    }

    void DXTextBox::UpdateDisplayArea()
    {
        RECT area = { Location.x, Location.y, 
                      Location.x + (_TextBox != nullptr ? _TextBox->GetWidth() : 0),
                      Location.y + (_TextBox != nullptr ? _TextBox->GetHeight() : 0) };

        if (GetParent() != nullptr)
        {
            RECT parentArea = GetParent()->GetDisplayArea();
            area.left += parentArea.left;
            area.right += parentArea.left;
            area.top += parentArea.top;
            area.bottom += parentArea.top;
        }

        DisplayArea = area;
    }

    void DXTextBox::OnMouseDown(int x, int y, int button, int clicks)
    {
        DXControl::OnMouseDown(x, y, button, clicks);

        if (_TextBox == nullptr || !_TextBox->GetVisible()) return;

        int location = x - DisplayArea.left | (y - DisplayArea.top) << 16;

        switch (button)
        {
            case 0: // Left button
                // SendMessage to TextBox
                break;
            case 2: // Right button
                // SendMessage to TextBox
                break;
        }
    }

    void DXTextBox::OnMouseMove(int x, int y, int clicks)
    {
        DXControl::OnMouseMove(x, y, clicks);

        // Handle mouse move for TextBox
    }

    void DXTextBox::OnMouseUp(int x, int y, int button, int clicks)
    {
        DXControl::OnMouseUp(x, y, button, clicks);

        if (_TextBox == nullptr || !_TextBox->GetVisible()) return;

        int location = x - DisplayArea.left | (y - DisplayArea.top) << 16;

        switch (button)
        {
            case 0: // Left button
                // SendMessage to TextBox
                break;
            case 2: // Right button
                // SendMessage to TextBox
                break;
        }
    }

    bool DXTextBox::CanFocus()
    {
        return GetIsVisible() && GetEditable() && GetIsEnabled();
    }

    void DXTextBox::SetFocus()
    {
        if (!CanFocus())
        {
            NeedFocus = true;
        }
        else
        {
            SetActiveTextBox(this);
            if (_TextBox != nullptr)
                _TextBox->SelectAll();
        }
    }

    void DXTextBox::CheckFocus()
    {
        if (_TextBox == nullptr) return;

        if (CanFocus())
        {
            if (!NeedFocus) return;

            NeedFocus = false;
            SetFocus();
        }
        else if (_ActiveTextBox == this)
        {
            SetActiveTextBox(nullptr);
        }
    }

    void DXTextBox::DrawControl()
    {
        if (!DrawTexture) return;

        if (!TextureValid) 
            CreateTexture();

        float oldOpacity = DXManager::GetOpacity();
        DXManager::SetOpacity(GetOpacity());

        // Present texture
        DXManager::PresentTexture(ControlTexture, GetParent(), DisplayArea, 
                                  GetIsEnabled() ? D2D1::ColorF(1, 1, 1, 1) : D2D1::ColorF(75.0f/255.0f, 75.0f/255.0f, 75.0f/255.0f, 1), 
                                  this);

        DXManager::SetOpacity(oldOpacity);

        ExpireTime = CEnvir::GetNow() + Config::CacheDuration;
    }

    void DXTextBox::Dispose(bool disposing)
    {
        DXControl::Dispose(disposing);

        if (disposing)
        {
            _Editable = false;
            _Font = nullptr;
            _KeepFocus = false;
            _MaxLength = 0;
            _Password = false;
            _ReadOnly = false;

            if (_TextBox != nullptr)
            {
                delete _TextBox;
                _TextBox = nullptr;
            }

            Button = 0;
            ClickTime = 0;
            NeedFocus = false;

            // Clear event handlers
            EditableChanged = nullptr;
            FontChanged = nullptr;
            KeepFocusChanged = nullptr;
            MaxLengthChanged = nullptr;
            PasswordChanged = nullptr;
            ReadOnlyChanged = nullptr;
            TextBoxChanged = nullptr;
        }

        if (_ActiveTextBox == this) 
            _ActiveTextBox = nullptr;
    }

    // MirTextBox implementation
    MirTextBox::MirTextBox(DXTextBox* owner)
    {
        Owner = owner;
    }

    MirTextBox::~MirTextBox()
    {
        Owner = nullptr;
    }

    void MirTextBox::NextTextBox()
    {
        if (Owner == nullptr || Owner->GetParent() == nullptr) return;

        MirTextBox* next = nullptr;
        bool found = false;

        auto& controls = Owner->GetParent()->GetControls();
        for (auto* control : controls)
        {
            auto* textBox = dynamic_cast<DXTextBox*>(control);
            if (textBox == nullptr) continue;

            if (!found)
            {
                if (control == Owner)
                    found = true;
                else if (next == nullptr)
                {
                    next = textBox;
                    if (!next->CanFocus())
                        next = nullptr;
                }
                continue;
            }

            next = textBox;
            break;
        }

        if (next != nullptr)
            next->SetFocus();
    }

    void MirTextBox::PreviousTextBox()
    {
        if (Owner == nullptr || Owner->GetParent() == nullptr) return;

        MirTextBox* previous = nullptr;
        bool found = false;

        auto& controls = Owner->GetParent()->GetControls();
        for (int i = static_cast<int>(controls.size()) - 1; i >= 0; i--)
        {
            auto* control = controls[i];
            auto* textBox = dynamic_cast<DXTextBox*>(control);
            if (textBox == nullptr) continue;

            if (!found)
            {
                if (control == Owner)
                    found = true;
                else if (previous == nullptr)
                {
                    previous = textBox;
                    if (!previous->CanFocus())
                        previous = nullptr;
                }
                continue;
            }

            previous = textBox;
            break;
        }

        if (previous != nullptr)
            previous->SetFocus();
    }

    void MirTextBox::SelectAll()
    {
        _selectedAll = true;
    }

    void MirTextBox::SetText(const std::wstring& text)
    {
        _text = text;
        OnTextChanged();
    }

    std::wstring MirTextBox::GetText() const
    {
        return _text;
    }

    void MirTextBox::OnMouseClick(int x, int y, int button, int clicks)
    {
        if (Owner == nullptr) return;

        long long now = CEnvir::GetNow();
        if (button == Owner->Button && Owner->ClickTime + 500 >= now) // Double click time
        {
            SelectAll();
        }
        else
        {
            Owner->Button = button;
            Owner->ClickTime = now;
        }
    }

    void MirTextBox::OnKeyDown(int keyCode, bool shift, bool alt, bool ctrl)
    {
        CEnvir::Shift = shift;
        CEnvir::Alt = alt;
        CEnvir::Ctrl = ctrl;

        if (alt && keyCode == 13) // Alt+Enter
        {
            DXManager::ToggleFullScreen();
            return;
        }

        // Handle special keys
        switch (keyCode)
        {
            case 112: // F1
            case 113: // F2
            case 114: // F3
            case 115: // F4
            case 116: // F5
            case 117: // F6
            case 118: // F7
            case 119: // F8
            case 120: // F9
            case 121: // F10
            case 122: // F11
            case 123: // F12
            case 9:   // Tab
            case 27:  // Escape
                // Forward to active scene
                // ActiveScene->OnKeyDown(keyCode, shift, alt, ctrl);
                break;
        }
    }

    void MirTextBox::OnKeyUp(int keyCode, bool shift, bool alt, bool ctrl)
    {
        CEnvir::Shift = shift;
        CEnvir::Alt = alt;
        CEnvir::Ctrl = ctrl;

        // Handle special keys
        switch (keyCode)
        {
            case 112: // F1
            case 113: // F2
            case 114: // F3
            case 115: // F4
            case 116: // F5
            case 117: // F6
            case 118: // F7
            case 119: // F8
            case 120: // F9
            case 121: // F10
            case 122: // F11
            case 123: // F12
            case 9:   // Tab
            case 27:  // Escape
                // Forward to active scene
                // ActiveScene->OnKeyUp(keyCode, shift, alt, ctrl);
                break;
        }
    }

    void MirTextBox::OnTextChanged()
    {
        if (Owner == nullptr) return;

        Owner->TextureValid = false;
    }

    void MirTextBox::OnSizeChanged(int width, int height)
    {
        if (Owner == nullptr) return;

        Owner->SetSize({ width, height });
        Owner->TextureValid = false;
    }
}
