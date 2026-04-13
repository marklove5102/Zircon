#pragma once

#include "../../Common/CSharpCompat.h"
#include "../../Library/Enum.h"
#include <vector>
#include <memory>

using namespace CSharpCompat;

namespace Client::Controls
{
    class DXScene;
    
    // Forward declarations
    class DXControl;
    class DXTextBox;
    
    using DXControlPtr = std::shared_ptr<DXControl>;
    using DXControlList = std::vector<DXControlPtr>;
    
    enum class HintPosition : uint8_t
    {
        TopLeft,
        TopCenter,
        TopRight,
        MiddleLeft,
        MiddleRight,
        BottomLeft,
        BottomCenter,
        BottomRight
    };
    
    enum class SoundIndex : uint16;
    
    class DXControl : public IDisposable
    {
    public:
        // Static Properties
        static DXControlList MessageBoxList;
        static DXControl* GetMouseControl() { return _MouseControl; }
        static void SetMouseControl(DXControl* value);
        
        static DXControl* GetFocusControl() { return _FocusControl; }
        static void SetFocusControl(DXControl* value);
        
        static DXScene* GetActiveScene() { return _ActiveScene; }
        static void SetActiveScene(DXScene* value);
        
        static int32 DefaultHeight;
        static int32 TabHeight;
        static int32 HeaderBarSize;
        static int32 HeaderSize;
        static int32 FooterSize;
        static int32 NoFooterSize;
        static int32 SmallButtonHeight;
        
        // Static Methods
        static void InitializeStatics();
        
        // Properties
        DXControlList& GetControls() { return Controls; }
        
        // AllowDragOut
        bool GetAllowDragOut() const { return _AllowDragOut; }
        void SetAllowDragOut(bool value);
        EventPtr<EventArgs> AllowDragOutChanged;
        virtual void OnAllowDragOutChanged(bool oValue, bool nValue);
        
        // AllowResize
        bool GetAllowResize() const { return _AllowResize; }
        void SetAllowResize(bool value);
        EventPtr<EventArgs> AllowResizeChanged;
        virtual void OnAllowResizeChanged(bool oValue, bool nValue);
        
        // BackColour
        Color GetBackColour() const { return _BackColour; }
        void SetBackColour(Color value);
        EventPtr<EventArgs> BackColourChanged;
        virtual void OnBackColourChanged(Color oValue, Color nValue);
        
        // Border
        bool GetBorder() const { return _Border; }
        void SetBorder(bool value);
        EventPtr<EventArgs> BorderChanged;
        virtual void OnBorderChanged(bool oValue, bool nValue);
        
        // BorderColour
        Color GetBorderColour() const { return _BorderColour; }
        void SetBorderColour(Color value);
        EventPtr<EventArgs> BorderColourChanged;
        virtual void OnBorderColourChanged(Color oValue, Color nValue);
        
        // BorderInformation
        std::vector<Vector2> GetBorderInformation() const { return _BorderInformation; }
        void SetBorderInformation(const std::vector<Vector2>& value);
        EventPtr<EventArgs> BorderInformationChanged;
        virtual void OnBorderInformationChanged(const std::vector<Vector2>& oValue, const std::vector<Vector2>& nValue);
        
        // BorderSize
        float GetBorderSize() const { return _BorderSize; }
        void SetBorderSize(float value);
        EventPtr<EventArgs> BorderSizeChanged;
        virtual void OnBorderSizeChanged(float oValue, float nValue);
        
        // CanResizeHeight
        bool GetCanResizeHeight() const { return _CanResizeHeight; }
        void SetCanResizeHeight(bool value);
        EventPtr<EventArgs> CanResizeHeightChanged;
        virtual void OnCanResizeHeightChanged(bool oValue, bool nValue);
        
        // CanResizeWidth
        bool GetCanResizeWidth() const { return _CanResizeWidth; }
        void SetCanResizeWidth(bool value);
        EventPtr<EventArgs> CanResizeWidthChanged;
        virtual void OnCanResizeWidthChanged(bool oValue, bool nValue);
        
        // DrawTexture
        bool GetDrawTexture() const { return _DrawTexture; }
        void SetDrawTexture(bool value);
        EventPtr<EventArgs> DrawTextureChanged;
        virtual void OnDrawTextureChanged(bool oValue, bool nValue);
        
        // DisplayArea
        Rectangle GetDisplayArea() const { return _DisplayArea; }
        void SetDisplayArea(Rectangle value);
        EventPtr<EventArgs> DisplayAreaChanged;
        virtual void OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue);
        
        // Enabled
        bool GetEnabled() const { return _Enabled; }
        void SetEnabled(bool value);
        EventPtr<EventArgs> EnabledChanged;
        virtual void OnEnabledChanged(bool oValue, bool nValue);
        
        // ForeColour
        Color GetForeColour() const { return _ForeColour; }
        void SetForeColour(Color value);
        EventPtr<EventArgs> ForeColourChanged;
        virtual void OnForeColourChanged(Color oValue, Color nValue);
        
        // Hint
        string GetHint() const { return _Hint; }
        void SetHint(string value);
        EventPtr<EventArgs> HintChanged;
        virtual void OnHintChanged(string oValue, string nValue);
        
        // HintPosition
        HintPosition GetHintPosition() const { return _HintPosition; }
        void SetHintPosition(HintPosition value);
        EventPtr<EventArgs> HintPositionChanged;
        virtual void OnHintPositionChanged(HintPosition oValue, HintPosition nValue);
        
        // IsControl
        bool GetIsControl() const { return _IsControl; }
        void SetIsControl(bool value);
        EventPtr<EventArgs> IsControlChanged;
        virtual void OnIsControlChanged(bool oValue, bool nValue);
        
        // Location
        Point GetLocation() const { return _Location; }
        void SetLocation(Point value);
        EventPtr<EventArgs> LocationChanged;
        virtual void OnLocationChanged(Point oValue, Point nValue);
        
        // Modal
        bool GetModal() const { return _Modal; }
        void SetModal(bool value);
        EventPtr<EventArgs> ModalChanged;
        virtual void OnModalChanged(bool oValue, bool nValue);
        
        // Movable
        bool GetMovable() const { return _Movable; }
        void SetMovable(bool value);
        EventPtr<EventArgs> MovableChanged;
        virtual void OnMovableChanged(bool oValue, bool nValue);
        
        // IgnoreMoveBounds
        bool GetIgnoreMoveBounds() const { return _IgnoreMoveBounds; }
        void SetIgnoreMoveBounds(bool value);
        EventPtr<EventArgs> IgnoreMoveBoundsChanged;
        virtual void OnIgnoreMoveBoundsChanged(bool oValue, bool nValue);
        
        // Clip
        bool GetClip() const { return _Clip; }
        void SetClip(bool value);
        EventPtr<EventArgs> ClipChanged;
        virtual void OnClipChanged(bool oValue, bool nValue);
        
        // Opacity
        float GetOpacity() const { return _Opacity; }
        void SetOpacity(float value);
        EventPtr<EventArgs> OpacityChanged;
        virtual void OnOpacityChanged(float oValue, float nValue);
        
        // Parent
        DXControl* GetParent() const { return _Parent; }
        void SetParent(DXControl* value);
        EventPtr<EventArgs> ParentChanged;
        virtual void OnParentChanged(DXControl* oValue, DXControl* nValue);
        
        // PassThrough
        bool GetPassThrough() const { return _PassThrough; }
        void SetPassThrough(bool value);
        EventPtr<EventArgs> PassThroughChanged;
        virtual void OnPassThroughChanged(bool oValue, bool nValue);
        
        // Size
        virtual Size GetSize() const { return _Size; }
        virtual void SetSize(Size value);
        EventPtr<EventArgs> SizeChanged;
        virtual void OnSizeChanged(Size oValue, Size nValue);
        
        // Sort
        bool GetSort() const { return _Sort; }
        void SetSort(bool value);
        EventPtr<EventArgs> SortChanged;
        virtual void OnSortChanged(bool oValue, bool nValue);
        
        // Sound
        SoundIndex GetSound() const { return _Sound; }
        void SetSound(SoundIndex value);
        EventPtr<EventArgs> SoundChanged;
        virtual void OnSoundChanged(SoundIndex oValue, SoundIndex nValue);
        
        // Tag
        any GetTag() const { return _Tag; }
        void SetTag(any value);
        EventPtr<EventArgs> TagChanged;
        virtual void OnTagChanged(any oValue, any nValue);
        
        // Text
        string GetText() const { return _Text; }
        void SetText(string value);
        EventPtr<EventArgs> TextChanged;
        virtual void OnTextChanged(string oValue, string nValue);
        
        // Visible
        bool GetVisible() const { return _Visible; }
        void SetVisible(bool value);
        EventPtr<EventArgs> VisibleChanged;
        virtual void OnVisibleChanged(bool oValue, bool nValue);
        
        // IsEnabled (computed)
        bool GetIsEnabled() const { return _IsEnabled; }
        void SetIsEnabled(bool value);
        EventPtr<EventArgs> IsEnabledChanged;
        virtual void OnIsEnabledChanged(bool oValue, bool nValue);
        
        // IsVisible (computed)
        bool GetIsVisible() const { return _IsVisible; }
        void SetIsVisible(bool value);
        EventPtr<EventArgs> IsVisibleChanged;
        virtual void OnIsVisibleChanged(bool oValue, bool nValue);
        
        // IsMoving
        bool GetIsMoving() const { return _IsMoving; }
        void SetIsMoving(bool value);
        EventPtr<EventArgs> IsMovingChanged;
        virtual void OnIsMovingChanged(bool oValue, bool nValue);
        
        // IsResizing
        bool GetIsResizing() const { return _IsResizing; }
        void SetIsResizing(bool value);
        EventPtr<EventArgs> IsResizingChanged;
        virtual void OnIsResizingChanged(bool oValue, bool nValue);
        
        // Texture properties
        bool TextureValid;
        void* ControlTexture;  // SlimDX Texture*
        Size TextureSize;
        void* ControlSurface;  // SlimDX Surface*
        DateTime ExpireTime;
        
        // Events
        EventPtr<EventArgs> MouseEnter, MouseLeave, Focus, LostFocus;
        EventPtr<MouseEventArgs> MouseDown, MouseUp, MouseMove, Moving, MouseClick, MouseDoubleClick, MouseWheel;
        EventPtr<KeyEventArgs> KeyDown, KeyUp;
        EventPtr<KeyPressEventArgs> KeyPress;
        
        Action ProcessAction;
        
        EventPtr<EventArgs> BeforeDraw, AfterDraw, BeforeChildrenDraw;
        EventPtr<EventArgs> Disposing;
        
        // Constructor
        DXControl();
        
        // Methods
        virtual void Process();
        virtual void UpdateBorderInformation();
        virtual void CheckIsVisible();
        virtual void CheckIsEnabled();
        virtual void UpdateDisplayArea();
        virtual void ResolutionChanged();
        virtual void OnSorted();
        void BringToFront();
        void SendToBack();
        void InvokeMouseClick();
        virtual bool IsMouseOver(Point p);
        virtual void OnMouseEnter();
        virtual void OnMouseLeave();
        virtual void OnMouseMove(MouseEventArgs e);
        virtual Size GetAcceptableResize(Size size);
        virtual void OnMouseDown(MouseEventArgs e);
        virtual void OnMouseUp(MouseEventArgs e);
        virtual void OnMouseClick(MouseEventArgs e);
        virtual void OnMouseDoubleClick(MouseEventArgs e);
        virtual void OnMouseWheel(MouseEventArgs e);
        virtual void OnFocus();
        virtual void OnLostFocus();
        virtual void OnKeyPress(KeyPressEventArgs e);
        virtual void OnKeyDown(KeyEventArgs e);
        virtual void OnKeyUp(KeyEventArgs e);
        
        // Drawing
        virtual void Draw();
        virtual void CreateTexture();
        virtual void OnClearTexture();
        virtual void DisposeTexture();
        virtual void DrawBorder();
        virtual void DrawChildControls();
        virtual void DrawControl();
        
        static void PresentTexture(void* texture, DXControl* parent, Rectangle displayArea, 
                                   Color colour, DXControl* control, int offX = 0, int offY = 0, float scale = 1.0f);
        
        // Destructor
        ~DXControl() override;
        
        // IDisposable
        bool IsDisposed;
        void Dispose() override;
        
    protected:
        virtual void OnBeforeDraw();
        virtual void OnBeforeChildrenDraw();
        virtual void OnAfterDraw();
        virtual void Dispose(bool disposing);
        
        void HandleMouseWheel(MouseEventArgs e);
        
        // Protected members
        DXControlList Controls;
        static DXControl* _MouseControl;
        static DXControl* _FocusControl;
        static DXScene* _ActiveScene;
        
        DXControl* _Parent;
        
        bool _AllowDragOut;
        bool _AllowResize;
        Color _BackColour;
        bool _Border;
        Color _BorderColour;
        std::vector<Vector2> _BorderInformation;
        float _BorderSize;
        bool _CanResizeHeight;
        bool _CanResizeWidth;
        bool _DrawTexture;
        Rectangle _DisplayArea;
        bool _Enabled;
        Color _ForeColour;
        string _Hint;
        HintPosition _HintPosition;
        bool _IsControl;
        Point _Location;
        bool _Modal;
        bool _Movable;
        bool _IgnoreMoveBounds;
        bool _Clip;
        float _Opacity;
        bool _PassThrough;
        Size _Size;
        bool _Sort;
        SoundIndex _Sound;
        any _Tag;
        string _Text;
        bool _Visible;
        
        bool _IsEnabled;
        bool _IsVisible;
        bool _IsMoving;
        bool _IsResizing;
        
        Point MovePoint;
        Point ResizePoint;
        bool ResizeLeft, ResizeRight, ResizeUp, ResizeDown;
        
    public:
        static const int ResizeBuffer = 9;
    };
}
