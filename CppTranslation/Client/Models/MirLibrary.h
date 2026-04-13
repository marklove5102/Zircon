#pragma once

#include "LibraryCore/Enums.h"
#include <drawing.h>
#include <vector>
#include <string>
#include <mutex>
#include <chrono>
#include <functional>

namespace SlimDX::Direct3D9 { class Texture; }

namespace Client::Envir
{

    enum class ImageType
    {
        Image,
        Shadow,
        Overlay
    };

    class MirImage;

    class MirLibrary
    {
    public:
        std::mutex LoadLocker;

        int Version = 0;
        std::string FileName;

        bool Loaded = false;
        bool Loading = false;

        std::vector<MirImage*> Images;

        MirLibrary(const std::string& fileName);
        ~MirLibrary();

        void ReadLibrary();
        Size GetSize(int index);
        Point GetOffSet(int index);
        MirImage* GetImage(int index);
        MirImage* CreateImage(int index, ImageType type);
        bool VisiblePixel(int index, Point location, bool accurate = true, bool offSet = false);
        
        void Draw(int index, float x, float y, Color4 colour, Rectangle area, float opacity, ImageType type, byte shadow = 0);
        void Draw(int index, float x, float y, Color4 colour, bool useOffSet, float opacity, ImageType type, float scale = 1.0f);
        void DrawBlend(int index, float size, Color4 colour, float x, float y, float angle, float opacity, ImageType type, bool useOffSet = false, byte shadow = 0);
        void DrawBlend(int index, float x, float y, Color4 colour, bool useOffSet, float rate, ImageType type, byte shadow = 0);

        bool IsDisposed = false;
        void Dispose();

    private:
        bool CheckImage(int index);
        void Dispose(bool disposing);
    };

    class MirImage
    {
    public:
        int Version = 0;
        int Position = 0;

        short Width = 0;
        short Height = 0;
        short OffSetX = 0;
        short OffSetY = 0;
        byte ShadowType = 0;

        SlimDX::Direct3D9::Texture* Image = nullptr;
        bool ImageValid = false;
        byte* ImageData = nullptr;
        int ImageDataSize();

        short ShadowWidth = 0;
        short ShadowHeight = 0;
        short ShadowOffSetX = 0;
        short ShadowOffSetY = 0;
        SlimDX::Direct3D9::Texture* Shadow = nullptr;
        bool ShadowValid = false;
        byte* ShadowData = nullptr;
        int ShadowDataSize();

        short OverlayWidth = 0;
        short OverlayHeight = 0;
        SlimDX::Direct3D9::Texture* Overlay = nullptr;
        bool OverlayValid = false;
        byte* OverlayData = nullptr;
        int OverlayDataSize();

        std::chrono::system_clock::time_point ExpireTime;

        MirImage(void* reader, int version); // BinaryReader*
        ~MirImage();

        bool VisiblePixel(Point p, bool accurate);
        void DisposeTexture();
        void CreateImage(void* reader); // BinaryReader*
        void CreateShadow(void* reader); // BinaryReader*
        void CreateOverlay(void* reader); // BinaryReader*

        bool IsDisposed = false;
        void Dispose();
        void Dispose(bool disposing);

    private:
        Format DrawFormat() const;
    };

} // namespace Client::Envir
