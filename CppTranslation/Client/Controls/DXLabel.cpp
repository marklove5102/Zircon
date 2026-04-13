#include "DXLabel.h"
#include "../../Library/MirLibrary.h"
#include "../Envir/CEnvir.h"
#include "../Envir/DXManager.h"

namespace Client::Controls
{
    DXLabel::DXLabel()
        : _FontType(FontType::Default)
        , _FontStyle(FontStyle::Normal)
        , _FontSize(10)
        , _MaxWidth(0)
        , _PaddingTop(0)
        , _PaddingBottom(0)
        , _Outline(false)
        , _OutlineColour(Color::Black)
        , _Alignment(TextAlignment::Left)
    {
    }
    
    DXLabel::~DXLabel()
    {
        Dispose();
    }
    
    void DXLabel::DrawControl()
    {
        if (GetText().empty()) return;
        
        // Draw text using DXManager's font rendering
        if (DXManager::Device != nullptr)
        {
            Rectangle rect = GetDisplayArea();
            rect.X += 2; // Small padding
            rect.Y += _PaddingTop;
            rect.Width -= 4;
            rect.Height -= (_PaddingTop + _PaddingBottom);
            
            // Draw outline if enabled
            if (_Outline)
            {
                // Draw outlined text
            }
            
            // Draw main text
            // DXManager::DrawText would be called here
        }
    }
    
    void DXLabel::CreateTexture()
    {
        TextureValid = true;
    }
    
    void DXLabel::SetFontType(FontType value)
    {
        if (_FontType == value) return;
        FontType oldValue = _FontType;
        _FontType = value;
        OnFontTypeChanged(oldValue, value);
    }
    
    void DXLabel::SetFontStyle(FontStyle value)
    {
        if (_FontStyle == value) return;
        FontStyle oldValue = _FontStyle;
        _FontStyle = value;
        OnFontStyleChanged(oldValue, value);
    }
    
    void DXLabel::SetFontSize(int32 value)
    {
        if (_FontSize == value) return;
        int32 oldValue = _FontSize;
        _FontSize = value;
        OnFontSizeChanged(oldValue, value);
    }
    
    void DXLabel::SetMaxWidth(int32 value)
    {
        if (_MaxWidth == value) return;
        int32 oldValue = _MaxWidth;
        _MaxWidth = value;
        OnMaxWidthChanged(oldValue, value);
    }
    
    void DXLabel::SetPaddingTop(int32 value)
    {
        if (_PaddingTop == value) return;
        int32 oldValue = _PaddingTop;
        _PaddingTop = value;
        OnPaddingTopChanged(oldValue, value);
    }
    
    void DXLabel::SetPaddingBottom(int32 value)
    {
        if (_PaddingBottom == value) return;
        int32 oldValue = _PaddingBottom;
        _PaddingBottom = value;
        OnPaddingBottomChanged(oldValue, value);
    }
    
    void DXLabel::SetOutline(bool value)
    {
        if (_Outline == value) return;
        bool oldValue = _Outline;
        _Outline = value;
        OnOutlineChanged(oldValue, value);
    }
    
    void DXLabel::SetOutlineColour(Color value)
    {
        if (_OutlineColour == value) return;
        Color oldValue = _OutlineColour;
        _OutlineColour = value;
        OnOutlineColourChanged(oldValue, value);
    }
    
    void DXLabel::SetAlignment(TextAlignment value)
    {
        if (_Alignment == value) return;
        TextAlignment oldValue = _Alignment;
        _Alignment = value;
        OnAlignmentChanged(oldValue, value);
    }
    
    void DXLabel::OnFontTypeChanged(FontType oValue, FontType nValue)
    {
        TextureValid = false;
        UpdateSize();
        FontTypeChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnFontStyleChanged(FontStyle oValue, FontStyle nValue)
    {
        TextureValid = false;
        UpdateSize();
        FontStyleChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnFontSizeChanged(int32 oValue, int32 nValue)
    {
        TextureValid = false;
        UpdateSize();
        FontSizeChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnMaxWidthChanged(int32 oValue, int32 nValue)
    {
        TextureValid = false;
        UpdateSize();
        MaxWidthChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnPaddingTopChanged(int32 oValue, int32 nValue)
    {
        TextureValid = false;
        UpdateSize();
        PaddingTopChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnPaddingBottomChanged(int32 oValue, int32 nValue)
    {
        TextureValid = false;
        UpdateSize();
        PaddingBottomChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnOutlineChanged(bool oValue, bool nValue)
    {
        TextureValid = false;
        OutlineChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnOutlineColourChanged(Color oValue, Color nValue)
    {
        TextureValid = false;
        OutlineColourChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnAlignmentChanged(TextAlignment oValue, TextAlignment nValue)
    {
        TextureValid = false;
        AlignmentChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXLabel::OnTextChanged(string oValue, string nValue)
    {
        TextureValid = false;
        UpdateSize();
        DXControl::OnTextChanged(oValue, nValue);
    }
    
    void DXLabel::UpdateSize()
    {
        if (GetText().empty())
        {
            SetSize(Size(0, _FontSize + _PaddingTop + _PaddingBottom));
            return;
        }
        
        // Calculate text size using DXManager
        Size textSize = DXManager::MeasureText(GetText(), _FontType, _FontStyle, _FontSize, _MaxWidth);
        
        textSize.Width += 4; // Padding
        textSize.Height += (_PaddingTop + _PaddingBottom);
        
        if (!_Centre)
            SetSize(textSize);
    }
}
