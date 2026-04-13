#pragma once

#include "../../Common/CSharpCompat.h"
#include <string>
#include <map>

namespace Client::Envir
{
    enum class FontType : uint8_t;
    enum class FontStyle : uint8_t;
    
    class DXSoundManager;
    
    class DXManager
    {
    public:
        // Static Properties
        static void* Device;  // SlimDX Direct3D Device*
        static DXSoundManager* SoundManager;
        static int32 Width;
        static int32 Height;
        static bool FullScreen;
        static float DPIScale;
        
        // Methods
        static bool Initialize(void* hwnd);
        static void Shutdown();
        static void BeginRender();
        static void EndRender();
        static void Present();
        static void Clear(Color colour);
        
        static Size MeasureText(const string& text, FontType fontType, FontStyle fontStyle, 
                               int32 fontSize, int32 maxWidth);
        static void DrawText(const string& text, Rectangle rect, Color colour, 
                            FontType fontType, FontStyle fontStyle, int32 fontSize,
                            TextAlignment alignment = TextAlignment::Left,
                            bool outline = false, Color outlineColour = Color::Black);
        
        static void DrawLine(Point p1, Point p2, Color colour, float width = 1.0f);
        static void DrawRectangle(Rectangle rect, Color colour, float width = 1.0f);
        static void FillRectangle(Rectangle rect, Color colour);
        
        static void SetRenderTarget(void* texture);
        static void ResetRenderTarget();
        
        static bool CheckDeviceLost();
        static bool ResetDevice();
        
    private:
        static bool _Initialized;
        static std::map<int32, void*> _FontCache;  // Font handle cache
    };
}
