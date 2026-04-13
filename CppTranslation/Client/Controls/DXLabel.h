#pragma once

#include "DXControl.h"
#include <string>

// Forward declare System.Drawing Font (will be implemented with native font)
namespace System::Drawing { class Font; }

namespace Client::Controls
{
    // TextFormatFlags equivalent for C++
    enum class TextFormatFlags : uint32
    {
        Default = 0,
        WordBreak = 1,
        // Add more flags as needed
    };
    
    class DXLabel : public DXControl
    {
    public:
        // Static Methods
        static Size GetSize(const std::string& text, void* font, bool outline, int32 paddingBottom = 0);
        static Size GetHeight(DXLabel* label, int32 width);
        
        // Properties
        
        // AutoSize
        bool GetAutoSize() const { return _AutoSize; }
        void SetAutoSize(bool value);
        EventPtr<EventArgs> AutoSizeChanged;
        virtual void OnAutoSizeChanged(bool oValue, bool nValue);
        
        // DrawFormat
        TextFormatFlags GetDrawFormat() const { return _DrawFormat; }
        void SetDrawFormat(TextFormatFlags value);
        EventPtr<EventArgs> DrawFormatChanged;
        virtual void OnDrawFormatChanged(TextFormatFlags oValue, TextFormatFlags nValue);
        
        // Font
        void* GetFont() const { return _Font; }  // Font*
        void SetFont(void* value);
        EventPtr<EventArgs> FontChanged;
        virtual void OnFontChanged(void* oValue, void* nValue);
        
        // Outline
        bool GetOutline() const { return _Outline; }
        void SetOutline(bool value);
        EventPtr<EventArgs> OutlineChanged;
        virtual void OnOutlineChanged(bool oValue, bool nValue);
        
        // DropShadow
        bool GetDropShadow() const { return _DropShadow; }
        void SetDropShadow(bool value);
        EventPtr<EventArgs> DropShadowChanged;
        virtual void OnDropShadowChanged(bool oValue, bool nValue);
        
        // OutlineColour
        Color GetOutlineColour() const { return _OutlineColour; }
        void SetOutlineColour(Color value);
        EventPtr<EventArgs> OutlineColourChanged;
        virtual void OnOutlineColourChanged(Color oValue, Color nValue);
        
        // PaddingBottom
        int32 GetPaddingBottom() const { return _PaddingBottom; }
        void SetPaddingBottom(int32 value);
        EventPtr<EventArgs> PaddingBottomChanged;
        virtual void OnPaddingBottomChanged(int32 oValue, int32 nValue);
        
        // Override methods
        void OnTextChanged(std::string oValue, std::string nValue) override;
        void OnForeColourChanged(Color oValue, Color nValue) override;
        
        // Constructor
        DXLabel();
        
        // Destructor
        ~DXLabel() override;
        
    protected:
        void CreateTexture() override;
        void DrawControl() override;
        void Dispose(bool disposing) override;
        
    private:
        void CreateSize();
        
        bool _AutoSize;
        TextFormatFlags _DrawFormat;
        void* _Font;  // Font*
        bool _Outline;
        bool _DropShadow;
        Color _OutlineColour;
        int32 _PaddingBottom;
    };
}
