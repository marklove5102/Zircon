#pragma once

#include "DXControl.h"
#include <vector>
#include <memory>

namespace Client::Controls
{
    // Forward declarations
    class DXButton;
    class DXLabel;
    class WindowSetting;

    enum class WindowType
    {
        None = 0,
        // Add other window types as needed
    };

    class DXWindow : public DXControl
    {
    public:
        // Static properties
        static std::vector<DXWindow*>& GetWindows();

        // Properties
        bool GetHasTopBorder() const { return _HasTopBorder; }
        void SetHasTopBorder(bool value);

        bool GetHasTitle() const { return _HasTitle; }
        void SetHasTitle(bool value);

        bool GetHasFooter() const { return _HasFooter; }
        void SetHasFooter(bool value);

        RECT GetClientArea() const { return _ClientArea; }
        void SetClientArea(const RECT& value);

        // Abstract properties (to be implemented by derived classes)
        virtual WindowType GetType() const = 0;
        virtual bool GetCustomSize() const = 0;
        virtual bool GetAutomaticVisibility() const = 0;

        // Child controls
        DXButton* GetCloseButton() const { return CloseButton; }
        DXLabel* GetTitleLabel() const { return TitleLabel; }

        // Window texture
        void* GetWindowTexture() const { return WindowTexture; }
        void* GetWindowSurface() const { return WindowSurface; }
        bool GetWindowValid() const { return WindowValid; }
        void SetWindowValid(bool value) { WindowValid = value; }

        // Settings
        WindowSetting* Settings;

        // Override events
        void OnSizeChanged(const SIZE& oValue, const SIZE& nValue) override;
        void OnParentChanged(DXControl* oValue, DXControl* nValue) override;
        void OnLocationChanged(const POINT& oValue, const POINT& nValue) override;
        void OnVisibleChanged(bool oValue, bool nValue) override;
        void OnKeyDown(int keyCode, bool shift, bool alt, bool ctrl) override;

        // Constructor/Destructor
        DXWindow();
        virtual ~DXWindow();

        // Methods
        void ResolutionChanged() override;
        void DisposeTexture() override;
        void Draw() override;
        void UpdateClientArea();
        void SetClientSize(const SIZE& clientSize);
        SIZE GetSize(const SIZE& clientSize);
        RECT GetClientAreaRect(const SIZE& size);
        void LoadSettings();
        void UpdateSettings();
        virtual void ApplySettings();

        // Event handlers
        std::function<void()> HasTopBorderChanged;
        std::function<void()> HasTitleChanged;
        std::function<void()> HasFooterChanged;
        std::function<void()> ClientAreaChanged;

    protected:
        void CreateTexture() override;
        void DrawControl() override;
        void DrawWindow();
        void DrawEdges();
        void Dispose(bool disposing) override;

        void UpdateLocations();
        void UpdateDisplayArea() override;

        // Child controls
        DXButton* CloseButton;
        DXLabel* TitleLabel;

    private:
        static std::vector<DXWindow*> _Windows;

        bool _HasTopBorder = true;
        bool _HasTitle = true;
        bool _HasFooter = false;
        RECT _ClientArea = { 0, 0, 0, 0 };

        void* WindowTexture = nullptr;
        void* WindowSurface = nullptr;
        bool WindowValid = false;

        // Event handlers
        void OnHasTopBorderChanged(bool oValue, bool nValue);
        void OnHasTitleChanged(bool oValue, bool nValue);
        void OnHasFooterChanged(bool oValue, bool nValue);
        void OnClientAreaChanged(const RECT& oValue, const RECT& nValue);
    };
}
