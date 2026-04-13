#pragma once

#include "DXControl.h"
#include "../../Library/Enum.h"

namespace Client::Controls
{
    class DXImageControl : public DXControl
    {
    public:
        // Properties
        
        // Blend
        bool GetBlend() const { return _Blend; }
        void SetBlend(bool value);
        EventPtr<EventArgs> BlendChanged;
        virtual void OnBlendChanged(bool oValue, bool nValue);
        
        // BlendMode
        Library::BlendMode GetBlendMode() const { return _BlendMode; }
        void SetBlendMode(Library::BlendMode value);
        EventPtr<EventArgs> BlendModeChanged;
        virtual void OnBlendModeChanged(Library::BlendMode oValue, Library::BlendMode nValue);
        
        // DrawImage
        bool GetDrawImage() const { return _DrawImage; }
        void SetDrawImage(bool value);
        EventPtr<EventArgs> DrawImageChanged;
        virtual void OnDrawImageChanged(bool oValue, bool nValue);
        
        // FixedSize
        bool GetFixedSize() const { return _FixedSize; }
        void SetFixedSize(bool value);
        EventPtr<EventArgs> FixedSizeChanged;
        virtual void OnFixedSizeChanged(bool oValue, bool nValue);
        
        // Scale
        float GetScale() const { return _Scale; }
        void SetScale(float value);
        EventPtr<EventArgs> ScaleChanged;
        virtual void OnScaleChanged(float oValue, float nValue);
        
        // ImageOpacity
        float GetImageOpacity() const { return _ImageOpacity; }
        void SetImageOpacity(float value);
        EventPtr<EventArgs> ImageOpacityChanged;
        virtual void OnImageOpacityChanged(float oValue, float nValue);
        
        // Index
        int32 GetIndex() const { return _Index; }
        void SetIndex(int32 value);
        EventPtr<EventArgs> IndexChanged;
        virtual void OnIndexChanged(int32 oValue, int32 nValue);
        
        // Library
        void* Library;  // MirLibrary*
        
        // LibraryFile
        Library::LibraryFile GetLibraryFile() const { return _LibraryFile; }
        void SetLibraryFile(Library::LibraryFile value);
        EventPtr<EventArgs> LibraryFileChanged;
        virtual void OnLibraryFileChanged(Library::LibraryFile oValue, Library::LibraryFile nValue);
        
        // PixelDetect
        bool GetPixelDetect() const { return _PixelDetect; }
        void SetPixelDetect(bool value);
        EventPtr<EventArgs> PixelDetectChanged;
        virtual void OnPixelDetectChanged(bool oValue, bool nValue);
        
        // UseOffSet
        bool GetUseOffSet() const { return _UseOffSet; }
        void SetUseOffSet(bool value);
        EventPtr<EventArgs> UseOffSetChanged;
        virtual void OnUseOffSetChanged(bool oValue, bool nValue);
        
        // Size (override)
        Size GetSize() const override;
        void SetSize(Size value) override;
        
        // Constructor
        DXImageControl();
        
        // Methods
        void DrawMirTexture();
        void UpdateDisplayArea() override;
        
        // Destructor
        ~DXImageControl() override;
        
    protected:
        void DrawControl() override;
        void Dispose(bool disposing) override;
        
    private:
        bool _Blend;
        Library::BlendMode _BlendMode;
        bool _DrawImage;
        bool _FixedSize;
        float _Scale;
        float _ImageOpacity;
        int32 _Index;
        Library::LibraryFile _LibraryFile;
        bool _PixelDetect;
        bool _UseOffSet;
    };
}
