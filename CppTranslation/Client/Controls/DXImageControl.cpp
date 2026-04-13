#include "DXImageControl.h"
#include "../../Library/MirLibrary.h"
#include "../Envir/CEnvir.h"

namespace Client::Controls
{
    DXImageControl::DXImageControl()
        : _Library(nullptr)
        , _Index(0)
        , _Centre(false)
        , _PartialRect(Rectangle::Empty)
        , _Scale(1.0f)
    {
    }
    
    DXImageControl::~DXImageControl()
    {
        Dispose();
    }
    
    void DXImageControl::DrawControl()
    {
        if (_Library == nullptr || !TextureValid) return;
        
        Size size = _Library->GetSize(_Index);
        
        if (size.Width <= 0 || size.Height <= 0) return;
        
        int drawWidth = static_cast<int>(size.Width * _Scale);
        int drawHeight = static_cast<int>(size.Height * _Scale);
        
        int drawX = _DisplayArea.X;
        int drawY = _DisplayArea.Y;
        
        if (_Centre)
        {
            drawX += (_Size.Width - drawWidth) / 2;
            drawY += (_Size.Height - drawHeight) / 2;
        }
        
        Rectangle displayArea = Rectangle(drawX, drawY, drawWidth, drawHeight);
        
        if (_PartialRect != Rectangle::Empty)
        {
            // Draw partial image
            PresentTexture(_Library->GetTexture(), GetParent(), displayArea, 
                          GetForeColour(), this, 0, 0, _Scale);
        }
        else
        {
            PresentTexture(_Library->GetTexture(), GetParent(), displayArea,
                          GetForeColour(), this, 0, 0, _Scale);
        }
    }
    
    void DXImageControl::CreateTexture()
    {
        if (_Library == nullptr) return;
        
        TextureValid = true;
    }
    
    void DXImageControl::SetLibrary(MirLibrary* value)
    {
        if (_Library == value) return;
        MirLibrary* oldValue = _Library;
        _Library = value;
        OnLibraryChanged(oldValue, value);
    }
    
    void DXImageControl::SetIndex(int32 value)
    {
        if (_Index == value) return;
        int32 oldValue = _Index;
        _Index = value;
        OnIndexChanged(oldValue, value);
    }
    
    void DXImageControl::SetCentre(bool value)
    {
        if (_Centre == value) return;
        bool oldValue = _Centre;
        _Centre = value;
        OnCentreChanged(oldValue, value);
    }
    
    void DXImageControl::SetPartialRect(Rectangle value)
    {
        if (_PartialRect == value) return;
        Rectangle oldValue = _PartialRect;
        _PartialRect = value;
        OnPartialRectChanged(oldValue, value);
    }
    
    void DXImageControl::SetScale(float value)
    {
        if (_Scale == value) return;
        float oldValue = _Scale;
        _Scale = value;
        OnScaleChanged(oldValue, value);
    }
    
    void DXImageControl::OnLibraryChanged(MirLibrary* oValue, MirLibrary* nValue)
    {
        TextureValid = false;
        LibraryChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXImageControl::OnIndexChanged(int32 oValue, int32 nValue)
    {
        TextureValid = false;
        
        if (_Library != nullptr && !_Centre)
        {
            Size size = _Library->GetSize(_Index);
            SetSize(size);
        }
        
        IndexChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXImageControl::OnCentreChanged(bool oValue, bool nValue)
    {
        CentreChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXImageControl::OnPartialRectChanged(Rectangle oValue, Rectangle nValue)
    {
        TextureValid = false;
        PartialRectChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXImageControl::OnScaleChanged(float oValue, float nValue)
    {
        if (!_Centre)
        {
            if (_Library != nullptr)
            {
                Size size = _Library->GetSize(_Index);
                SetSize(Size(static_cast<int>(size.Width * _Scale), 
                            static_cast<int>(size.Height * _Scale)));
            }
        }
        
        ScaleChanged?.Invoke(this, EventArgs::Empty);
    }
}
