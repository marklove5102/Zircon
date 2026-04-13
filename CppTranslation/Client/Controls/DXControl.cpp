#include "DXControl.h"
#include "../Envir/CEnvir.h"
#include "../Envir/DXManager.h"
#include "../../Library/MirLibrary.h"
#include <algorithm>

namespace Client::Controls
{
    // Static member initialization
    DXControlList DXControl::MessageBoxList;
    DXControl* DXControl::_MouseControl = nullptr;
    DXControl* DXControl::_FocusControl = nullptr;
    DXScene* DXControl::_ActiveScene = nullptr;
    
    int32 DXControl::DefaultHeight = 0;
    int32 DXControl::TabHeight = 0;
    int32 DXControl::HeaderBarSize = 0;
    int32 DXControl::HeaderSize = 0;
    int32 DXControl::FooterSize = 0;
    int32 DXControl::NoFooterSize = 0;
    int32 DXControl::SmallButtonHeight = 0;
    
    void DXControl::InitializeStatics()
    {
        // DebugLabel and HintLabel would be initialized here
        // For now, we'll skip the static label initialization
        
        MirLibrary* interfaceLibrary = nullptr;
        CEnvir::GetLibrary(LibraryFile::Interface, &interfaceLibrary);
        
        if (interfaceLibrary == nullptr) return;
        
        Size size = interfaceLibrary->GetSize(16);
        DefaultHeight = size.Height;
        TabHeight = interfaceLibrary->GetSize(19).Height;
        SmallButtonHeight = interfaceLibrary->GetSize(41).Height;
        
        HeaderBarSize = interfaceLibrary->GetSize(0).Height;
        
        HeaderSize = HeaderBarSize;
        HeaderSize += interfaceLibrary->GetSize(3).Height;
        
        NoFooterSize = interfaceLibrary->GetSize(2).Height;
        
        FooterSize = HeaderBarSize;
        FooterSize += interfaceLibrary->GetSize(2).Height;
        FooterSize += interfaceLibrary->GetSize(10).Height;
    }
    
    DXControl::DXControl()
        : _AllowDragOut(false)
        , _AllowResize(false)
        , _BackColour(Color::White)
        , _Border(false)
        , _BorderColour(Color::Black)
        , _BorderSize(1.0f)
        , _CanResizeHeight(true)
        , _CanResizeWidth(true)
        , _DrawTexture(true)
        , _Enabled(true)
        , _ForeColour(Color::White)
        , _Hint("")
        , _HintPosition(HintPosition::TopLeft)
        , _IsControl(true)
        , _Location(Point::Empty)
        , _Modal(false)
        , _Movable(false)
        , _IgnoreMoveBounds(false)
        , _Clip(true)
        , _Opacity(1.0f)
        , _PassThrough(false)
        , _Size(Size::Empty)
        , _Sort(false)
        , _Sound(SoundIndex::None)
        , _Text("")
        , _Visible(true)
        , _IsEnabled(true)
        , _IsVisible(true)
        , _IsMoving(false)
        , _IsResizing(false)
        , TextureValid(false)
        , ControlTexture(nullptr)
        , TextureSize(Size::Empty)
        , ControlSurface(nullptr)
        , IsDisposed(false)
        , _Parent(nullptr)
        , MovePoint(Point::Empty)
        , ResizePoint(Point::Empty)
        , ResizeLeft(false)
        , ResizeRight(false)
        , ResizeUp(false)
        , ResizeDown(false)
    {
        AllowDragOutChanged = nullptr;
        AllowResizeChanged = nullptr;
        BackColourChanged = nullptr;
        BorderChanged = nullptr;
        BorderColourChanged = nullptr;
        BorderInformationChanged = nullptr;
        BorderSizeChanged = nullptr;
        CanResizeHeightChanged = nullptr;
        CanResizeWidthChanged = nullptr;
        DrawTextureChanged = nullptr;
        DisplayAreaChanged = nullptr;
        EnabledChanged = nullptr;
        ForeColourChanged = nullptr;
        HintChanged = nullptr;
        HintPositionChanged = nullptr;
        IsControlChanged = nullptr;
        LocationChanged = nullptr;
        ModalChanged = nullptr;
        MovableChanged = nullptr;
        IgnoreMoveBoundsChanged = nullptr;
        ClipChanged = nullptr;
        OpacityChanged = nullptr;
        ParentChanged = nullptr;
        PassThroughChanged = nullptr;
        SizeChanged = nullptr;
        SortChanged = nullptr;
        SoundChanged = nullptr;
        TagChanged = nullptr;
        TextChanged = nullptr;
        VisibleChanged = nullptr;
        IsEnabledChanged = nullptr;
        IsVisibleChanged = nullptr;
        IsMovingChanged = nullptr;
        IsResizingChanged = nullptr;
        
        MouseEnter = nullptr;
        MouseLeave = nullptr;
        Focus = nullptr;
        LostFocus = nullptr;
        MouseDown = nullptr;
        MouseUp = nullptr;
        MouseMove = nullptr;
        Moving = nullptr;
        MouseClick = nullptr;
        MouseDoubleClick = nullptr;
        MouseWheel = nullptr;
        KeyDown = nullptr;
        KeyUp = nullptr;
        KeyPress = nullptr;
        
        BeforeDraw = nullptr;
        AfterDraw = nullptr;
        BeforeChildrenDraw = nullptr;
        Disposing = nullptr;
        
        ProcessAction = nullptr;
    }
    
    DXControl::~DXControl()
    {
        Dispose();
    }
    
    void DXControl::Dispose()
    {
        if (IsDisposed) return;
        
        Disposing?.Invoke(this, EventArgs::Empty);
        
        IsDisposed = true;
        
        // Dispose all child controls
        for (auto& control : Controls)
        {
            if (control)
                control->Dispose();
        }
        Controls.clear();
        
        DisposeTexture();
        
        if (_MouseControl == this)
            SetMouseControl(nullptr);
        
        if (_FocusControl == this)
            SetFocusControl(nullptr);
        
        if (_Parent != nullptr)
        {
            auto& parentControls = _Parent->GetControls();
            parentControls.erase(std::remove(parentControls.begin(), parentControls.end(), shared_from_this()), parentControls.end());
        }
    }
    
    void DXControl::Dispose(bool disposing)
    {
        if (disposing)
        {
            Dispose();
        }
    }
    
    void DXControl::SetMouseControl(DXControl* value)
    {
        if (_MouseControl == value) return;
        
        DXControl* oldControl = _MouseControl;
        _MouseControl = value;
        
        if (oldControl != nullptr)
            oldControl->OnMouseLeave();
        
        if (_MouseControl != nullptr)
            _MouseControl->OnMouseEnter();
    }
    
    void DXControl::SetFocusControl(DXControl* value)
    {
        if (_FocusControl == value) return;
        
        DXControl* oldControl = _FocusControl;
        _FocusControl = value;
        
        if (oldControl != nullptr)
            oldControl->OnLostFocus();
        
        if (_FocusControl != nullptr)
            _FocusControl->OnFocus();
        
        // Handle DXTextBox focus logic would go here
    }
    
    void DXControl::SetActiveScene(DXScene* value)
    {
        if (_ActiveScene == value) return;
        
        _ActiveScene = value;
        
        if (_ActiveScene != nullptr)
            _ActiveScene->CheckIsVisible();
    }
    
    void DXControl::Process()
    {
        if (ProcessAction != nullptr)
            ProcessAction();
        
        for (auto& control : Controls)
        {
            if (control && control->GetIsVisible() && control->GetEnabled())
                control->Process();
        }
    }
    
    void DXControl::UpdateBorderInformation()
    {
        if (!_Border)
        {
            _BorderInformation.clear();
            OnBorderInformationChanged(_BorderInformation, _BorderInformation);
            return;
        }
        
        _BorderInformation = {
            Vector2(static_cast<float>(_DisplayArea.X), static_cast<float>(_DisplayArea.Y)),
            Vector2(static_cast<float>(_DisplayArea.X + _DisplayArea.Width), static_cast<float>(_DisplayArea.Y)),
            Vector2(static_cast<float>(_DisplayArea.X + _DisplayArea.Width), static_cast<float>(_DisplayArea.Y + _DisplayArea.Height)),
            Vector2(static_cast<float>(_DisplayArea.X), static_cast<float>(_DisplayArea.Y + _DisplayArea.Height))
        };
        
        OnBorderInformationChanged(_BorderInformation, _BorderInformation);
    }
    
    void DXControl::CheckIsVisible()
    {
        bool isVisible = _Visible;
        
        if (isVisible && _Parent != nullptr)
            isVisible = _Parent->GetIsVisible();
        
        if (_IsVisible != isVisible)
        {
            bool oldValue = _IsVisible;
            _IsVisible = isVisible;
            
            for (auto& control : Controls)
            {
                if (control)
                    control->CheckIsVisible();
            }
            
            OnIsVisibleChanged(oldValue, _IsVisible);
        }
    }
    
    void DXControl::CheckIsEnabled()
    {
        bool isEnabled = _Enabled;
        
        if (isEnabled && _Parent != nullptr)
            isEnabled = _Parent->GetIsEnabled();
        
        if (_IsEnabled != isEnabled)
        {
            bool oldValue = _IsEnabled;
            _IsEnabled = isEnabled;
            
            for (auto& control : Controls)
            {
                if (control)
                    control->CheckIsEnabled();
            }
            
            OnIsEnabledChanged(oldValue, _IsEnabled);
        }
    }
    
    void DXControl::UpdateDisplayArea()
    {
        Rectangle oldArea = _DisplayArea;
        _DisplayArea = Rectangle(_Location.X, _Location.Y, _Size.Width, _Size.Height);
        
        if (_Parent != nullptr)
        {
            _DisplayArea.X += _Parent->GetDisplayArea().X;
            _DisplayArea.Y += _Parent->GetDisplayArea().Y;
        }
        
        if (oldArea != _DisplayArea)
        {
            for (auto& control : Controls)
            {
                if (control)
                    control->UpdateDisplayArea();
            }
            
            UpdateBorderInformation();
            OnDisplayAreaChanged(oldArea, _DisplayArea);
        }
    }
    
    void DXControl::ResolutionChanged()
    {
        for (auto& control : Controls)
        {
            if (control)
                control->ResolutionChanged();
        }
    }
    
    void DXControl::OnSorted()
    {
        // Override in derived classes
    }
    
    void DXControl::BringToFront()
    {
        if (_Parent == nullptr) return;
        
        auto& controls = _Parent->GetControls();
        auto it = std::find(controls.begin(), controls.end(), shared_from_this());
        
        if (it != controls.end())
        {
            controls.erase(it);
            controls.push_back(shared_from_this());
        }
        
        if (_Sort)
            OnSorted();
    }
    
    void DXControl::SendToBack()
    {
        if (_Parent == nullptr) return;
        
        auto& controls = _Parent->GetControls();
        auto it = std::find(controls.begin(), controls.end(), shared_from_this());
        
        if (it != controls.end())
        {
            controls.erase(it);
            controls.insert(controls.begin(), shared_from_this());
        }
        
        if (_Sort)
            OnSorted();
    }
    
    void DXControl::InvokeMouseClick()
    {
        MouseEventArgs e;
        e.Location = Point(_DisplayArea.X + _Size.Width / 2, _DisplayArea.Y + _Size.Height / 2);
        e.Button = MouseButton::Left;
        
        OnMouseClick(e);
    }
    
    bool DXControl::IsMouseOver(Point p)
    {
        return p.X >= _DisplayArea.X && 
               p.X < _DisplayArea.X + _Size.Width && 
               p.Y >= _DisplayArea.Y && 
               p.Y < _DisplayArea.Y + _Size.Height;
    }
    
    void DXControl::OnMouseEnter()
    {
        MouseEnter?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnMouseLeave()
    {
        MouseLeave?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnMouseMove(MouseEventArgs e)
    {
        MouseMove?.Invoke(this, e);
        
        if (_IsMoving && _Movable && _Parent != nullptr)
        {
            Point newLocation = e.Location - MovePoint;
            
            // Constrain to parent bounds if needed
            if (!_IgnoreMoveBounds)
            {
                Rectangle parentArea = _Parent->GetDisplayArea();
                
                if (newLocation.X < parentArea.X)
                    newLocation.X = parentArea.X;
                else if (newLocation.X + _Size.Width > parentArea.X + parentArea.Width)
                    newLocation.X = parentArea.X + parentArea.Width - _Size.Width;
                
                if (newLocation.Y < parentArea.Y)
                    newLocation.Y = parentArea.Y;
                else if (newLocation.Y + _Size.Height > parentArea.Y + parentArea.Height)
                    newLocation.Y = parentArea.Y + parentArea.Height - _Size.Height;
            }
            
            SetLocation(newLocation);
            
            Moving?.Invoke(this, e);
        }
        else if (_IsResizing && _AllowResize)
        {
            Size newSize = e.Location - _Parent->GetDisplayArea().Location - ResizePoint;
            
            Size acceptableSize = GetAcceptableResize(newSize);
            
            if (acceptableSize != _Size)
                SetSize(acceptableSize);
        }
    }
    
    Size DXControl::GetAcceptableResize(Size size)
    {
        Size newSize = size;
        
        if (!_CanResizeWidth)
            newSize.Width = _Size.Width;
        else if (newSize.Width < 10)
            newSize.Width = 10;
        
        if (!_CanResizeHeight)
            newSize.Height = _Size.Height;
        else if (newSize.Height < 10)
            newSize.Height = 10;
        
        return newSize;
    }
    
    void DXControl::OnMouseDown(MouseEventArgs e)
    {
        MouseDown?.Invoke(this, e);
        
        if (!GetIsEnabled() || !GetIsVisible()) return;
        
        if (_IsControl)
            SetFocusControl(this);
        
        if (_Movable && e.Button == MouseButton::Left)
        {
            _IsMoving = true;
            MovePoint = e.Location - _Location;
            OnIsMovingChanged(_IsMoving, _IsMoving);
        }
        else if (_AllowResize && e.Button == MouseButton::Left)
        {
            _IsResizing = true;
            ResizePoint = e.Location - _Parent->GetDisplayArea().Location;
            
            ResizeLeft = e.Location.X < _DisplayArea.X + ResizeBuffer;
            ResizeRight = e.Location.X > _DisplayArea.X + _Size.Width - ResizeBuffer;
            ResizeUp = e.Location.Y < _DisplayArea.Y + ResizeBuffer;
            ResizeDown = e.Location.Y > _DisplayArea.Y + _Size.Height - ResizeBuffer;
            
            OnIsResizingChanged(_IsResizing, _IsResizing);
        }
    }
    
    void DXControl::OnMouseUp(MouseEventArgs e)
    {
        MouseUp?.Invoke(this, e);
        
        if (_IsMoving)
        {
            _IsMoving = false;
            OnIsMovingChanged(_IsMoving, _IsMoving);
        }
        
        if (_IsResizing)
        {
            _IsResizing = false;
            OnIsResizingChanged(_IsResizing, _IsResizing);
        }
    }
    
    void DXControl::OnMouseClick(MouseEventArgs e)
    {
        MouseClick?.Invoke(this, e);
        
        if (_Sound != SoundIndex::None && DXManager::SoundManager != nullptr)
        {
            // Play sound would go here
        }
    }
    
    void DXControl::OnMouseDoubleClick(MouseEventArgs e)
    {
        MouseDoubleClick?.Invoke(this, e);
    }
    
    void DXControl::OnMouseWheel(MouseEventArgs e)
    {
        MouseWheel?.Invoke(this, e);
        HandleMouseWheel(e);
    }
    
    void DXControl::HandleMouseWheel(MouseEventArgs e)
    {
        if (_Parent != nullptr)
            _Parent->HandleMouseWheel(e);
    }
    
    void DXControl::OnFocus()
    {
        Focus?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnLostFocus()
    {
        LostFocus?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnKeyPress(KeyPressEventArgs e)
    {
        KeyPress?.Invoke(this, e);
    }
    
    void DXControl::OnKeyDown(KeyEventArgs e)
    {
        KeyDown?.Invoke(this, e);
    }
    
    void DXControl::OnKeyUp(KeyEventArgs e)
    {
        KeyUp?.Invoke(this, e);
    }
    
    void DXControl::Draw()
    {
        if (!_IsVisible || !_IsEnabled) return;
        
        OnBeforeDraw();
        
        if (_DrawTexture && !TextureValid)
            CreateTexture();
        
        DrawControl();
        DrawBorder();
        
        OnBeforeChildrenDraw();
        DrawChildControls();
        
        OnAfterDraw();
    }
    
    void DXControl::CreateTexture()
    {
        // Implementation would use SlimDX to create texture
        TextureValid = true;
    }
    
    void DXControl::OnClearTexture()
    {
        // Override in derived classes
    }
    
    void DXControl::DisposeTexture()
    {
        if (ControlTexture != nullptr)
        {
            // Release SlimDX texture
            ControlTexture = nullptr;
        }
        
        if (ControlSurface != nullptr)
        {
            // Release SlimDX surface
            ControlSurface = nullptr;
        }
        
        TextureValid = false;
        OnClearTexture();
    }
    
    void DXControl::DrawBorder()
    {
        if (!_Border || _BorderInformation.empty()) return;
        
        // Implementation would use SlimDX to draw border lines
    }
    
    void DXControl::DrawChildControls()
    {
        for (auto& control : Controls)
        {
            if (control && control->GetIsVisible())
                control->Draw();
        }
    }
    
    void DXControl::DrawControl()
    {
        // Base implementation - override in derived classes
    }
    
    void DXControl::PresentTexture(void* texture, DXControl* parent, Rectangle displayArea,
                                   Color colour, DXControl* control, int offX, int offY, float scale)
    {
        // Implementation would use SlimDX to present texture
        // This is a placeholder for the actual DirectX rendering code
    }
    
    // Property setters with change notification
    void DXControl::SetAllowDragOut(bool value)
    {
        if (_AllowDragOut == value) return;
        bool oldValue = _AllowDragOut;
        _AllowDragOut = value;
        OnAllowDragOutChanged(oldValue, value);
    }
    
    void DXControl::SetAllowResize(bool value)
    {
        if (_AllowResize == value) return;
        bool oldValue = _AllowResize;
        _AllowResize = value;
        OnAllowResizeChanged(oldValue, value);
    }
    
    void DXControl::SetBackColour(Color value)
    {
        if (_BackColour == value) return;
        Color oldValue = _BackColour;
        _BackColour = value;
        OnBackColourChanged(oldValue, value);
    }
    
    void DXControl::SetBorder(bool value)
    {
        if (_Border == value) return;
        bool oldValue = _Border;
        _Border = value;
        OnBorderChanged(oldValue, value);
    }
    
    void DXControl::SetBorderColour(Color value)
    {
        if (_BorderColour == value) return;
        Color oldValue = _BorderColour;
        _BorderColour = value;
        OnBorderColourChanged(oldValue, value);
    }
    
    void DXControl::SetBorderInformation(const std::vector<Vector2>& value)
    {
        if (_BorderInformation == value) return;
        std::vector<Vector2> oldValue = _BorderInformation;
        _BorderInformation = value;
        OnBorderInformationChanged(oldValue, value);
    }
    
    void DXControl::SetBorderSize(float value)
    {
        if (_BorderSize == value) return;
        float oldValue = _BorderSize;
        _BorderSize = value;
        OnBorderSizeChanged(oldValue, value);
    }
    
    void DXControl::SetCanResizeHeight(bool value)
    {
        if (_CanResizeHeight == value) return;
        bool oldValue = _CanResizeHeight;
        _CanResizeHeight = value;
        OnCanResizeHeightChanged(oldValue, value);
    }
    
    void DXControl::SetCanResizeWidth(bool value)
    {
        if (_CanResizeWidth == value) return;
        bool oldValue = _CanResizeWidth;
        _CanResizeWidth = value;
        OnCanResizeWidthChanged(oldValue, value);
    }
    
    void DXControl::SetDrawTexture(bool value)
    {
        if (_DrawTexture == value) return;
        bool oldValue = _DrawTexture;
        _DrawTexture = value;
        OnDrawTextureChanged(oldValue, value);
    }
    
    void DXControl::SetDisplayArea(Rectangle value)
    {
        if (_DisplayArea == value) return;
        Rectangle oldValue = _DisplayArea;
        _DisplayArea = value;
        OnDisplayAreaChanged(oldValue, value);
    }
    
    void DXControl::SetEnabled(bool value)
    {
        if (_Enabled == value) return;
        bool oldValue = _Enabled;
        _Enabled = value;
        OnEnabledChanged(oldValue, value);
    }
    
    void DXControl::SetForeColour(Color value)
    {
        if (_ForeColour == value) return;
        Color oldValue = _ForeColour;
        _ForeColour = value;
        OnForeColourChanged(oldValue, value);
    }
    
    void DXControl::SetHint(string value)
    {
        if (_Hint == value) return;
        string oldValue = _Hint;
        _Hint = value;
        OnHintChanged(oldValue, value);
    }
    
    void DXControl::SetHintPosition(HintPosition value)
    {
        if (_HintPosition == value) return;
        HintPosition oldValue = _HintPosition;
        _HintPosition = value;
        OnHintPositionChanged(oldValue, value);
    }
    
    void DXControl::SetIsControl(bool value)
    {
        if (_IsControl == value) return;
        bool oldValue = _IsControl;
        _IsControl = value;
        OnIsControlChanged(oldValue, value);
    }
    
    void DXControl::SetLocation(Point value)
    {
        if (_Location == value) return;
        Point oldValue = _Location;
        _Location = value;
        OnLocationChanged(oldValue, value);
    }
    
    void DXControl::SetModal(bool value)
    {
        if (_Modal == value) return;
        bool oldValue = _Modal;
        _Modal = value;
        OnModalChanged(oldValue, value);
    }
    
    void DXControl::SetMovable(bool value)
    {
        if (_Movable == value) return;
        bool oldValue = _Movable;
        _Movable = value;
        OnMovableChanged(oldValue, value);
    }
    
    void DXControl::SetIgnoreMoveBounds(bool value)
    {
        if (_IgnoreMoveBounds == value) return;
        bool oldValue = _IgnoreMoveBounds;
        _IgnoreMoveBounds = value;
        OnIgnoreMoveBoundsChanged(oldValue, value);
    }
    
    void DXControl::SetClip(bool value)
    {
        if (_Clip == value) return;
        bool oldValue = _Clip;
        _Clip = value;
        OnClipChanged(oldValue, value);
    }
    
    void DXControl::SetOpacity(float value)
    {
        if (_Opacity == value) return;
        float oldValue = _Opacity;
        _Opacity = value;
        OnOpacityChanged(oldValue, value);
    }
    
    void DXControl::SetParent(DXControl* value)
    {
        if (_Parent == value) return;
        DXControl* oldValue = _Parent;
        _Parent = value;
        OnParentChanged(oldValue, value);
    }
    
    void DXControl::SetPassThrough(bool value)
    {
        if (_PassThrough == value) return;
        bool oldValue = _PassThrough;
        _PassThrough = value;
        OnPassThroughChanged(oldValue, value);
    }
    
    void DXControl::SetSize(Size value)
    {
        if (_Size == value) return;
        Size oldValue = _Size;
        _Size = value;
        OnSizeChanged(oldValue, value);
    }
    
    void DXControl::SetSort(bool value)
    {
        if (_Sort == value) return;
        bool oldValue = _Sort;
        _Sort = value;
        OnSortChanged(oldValue, value);
    }
    
    void DXControl::SetSound(SoundIndex value)
    {
        if (_Sound == value) return;
        SoundIndex oldValue = _Sound;
        _Sound = value;
        OnSoundChanged(oldValue, value);
    }
    
    void DXControl::SetTag(any value)
    {
        if (_Tag == value) return;
        any oldValue = _Tag;
        _Tag = value;
        OnTagChanged(oldValue, value);
    }
    
    void DXControl::SetText(string value)
    {
        if (_Text == value) return;
        string oldValue = _Text;
        _Text = value;
        OnTextChanged(oldValue, value);
    }
    
    void DXControl::SetVisible(bool value)
    {
        if (_Visible == value) return;
        bool oldValue = _Visible;
        _Visible = value;
        OnVisibleChanged(oldValue, value);
    }
    
    void DXControl::SetIsEnabled(bool value)
    {
        if (_IsEnabled == value) return;
        bool oldValue = _IsEnabled;
        _IsEnabled = value;
        OnIsEnabledChanged(oldValue, value);
    }
    
    void DXControl::SetIsVisible(bool value)
    {
        if (_IsVisible == value) return;
        bool oldValue = _IsVisible;
        _IsVisible = value;
        OnIsVisibleChanged(oldValue, value);
    }
    
    void DXControl::SetIsMoving(bool value)
    {
        if (_IsMoving == value) return;
        bool oldValue = _IsMoving;
        _IsMoving = value;
        OnIsMovingChanged(oldValue, value);
    }
    
    void DXControl::SetIsResizing(bool value)
    {
        if (_IsResizing == value) return;
        bool oldValue = _IsResizing;
        _IsResizing = value;
        OnIsResizingChanged(oldValue, value);
    }
    
    void DXControl::OnBeforeDraw()
    {
        BeforeDraw?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBeforeChildrenDraw()
    {
        BeforeChildrenDraw?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnAfterDraw()
    {
        AfterDraw?.Invoke(this, EventArgs::Empty);
    }
    
    // Virtual event handlers - default implementations
    void DXControl::OnAllowDragOutChanged(bool oValue, bool nValue)
    {
        AllowDragOutChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnAllowResizeChanged(bool oValue, bool nValue)
    {
        AllowResizeChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBackColourChanged(Color oValue, Color nValue)
    {
        TextureValid = false;
        BackColourChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBorderChanged(bool oValue, bool nValue)
    {
        UpdateBorderInformation();
        BorderChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBorderColourChanged(Color oValue, Color nValue)
    {
        BorderColourChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBorderInformationChanged(const std::vector<Vector2>& oValue, const std::vector<Vector2>& nValue)
    {
        BorderInformationChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnBorderSizeChanged(float oValue, float nValue)
    {
        BorderSizeChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnCanResizeHeightChanged(bool oValue, bool nValue)
    {
        CanResizeHeightChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnCanResizeWidthChanged(bool oValue, bool nValue)
    {
        CanResizeWidthChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnDrawTextureChanged(bool oValue, bool nValue)
    {
        TextureValid = false;
        DrawTextureChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnDisplayAreaChanged(Rectangle oValue, Rectangle nValue)
    {
        for (auto& control : Controls)
        {
            if (control)
                control->UpdateDisplayArea();
        }
        
        UpdateBorderInformation();
        DisplayAreaChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnEnabledChanged(bool oValue, bool nValue)
    {
        CheckIsEnabled();
        EnabledChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnForeColourChanged(Color oValue, Color nValue)
    {
        ForeColourChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnHintChanged(string oValue, string nValue)
    {
        HintChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnHintPositionChanged(HintPosition oValue, HintPosition nValue)
    {
        HintPositionChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIsControlChanged(bool oValue, bool nValue)
    {
        if (!nValue)
        {
            if (GetFocusControl() == this)
                SetFocusControl(nullptr);
            
            if (GetMouseControl() == this)
                SetMouseControl(nullptr);
        }
        
        IsControlChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnLocationChanged(Point oValue, Point nValue)
    {
        UpdateDisplayArea();
        LocationChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnModalChanged(bool oValue, bool nValue)
    {
        ModalChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnMovableChanged(bool oValue, bool nValue)
    {
        MovableChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIgnoreMoveBoundsChanged(bool oValue, bool nValue)
    {
        IgnoreMoveBoundsChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnClipChanged(bool oValue, bool nValue)
    {
        ClipChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnOpacityChanged(float oValue, float nValue)
    {
        OpacityChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnParentChanged(DXControl* oValue, DXControl* nValue)
    {
        if (oValue != nullptr)
        {
            auto& oldControls = oValue->GetControls();
            oldControls.erase(std::remove(oldControls.begin(), oldControls.end(), shared_from_this()), oldControls.end());
        }
        
        if (nValue != nullptr)
            nValue->GetControls().push_back(shared_from_this());
        
        UpdateDisplayArea();
        CheckIsVisible();
        CheckIsEnabled();
        
        ParentChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnPassThroughChanged(bool oValue, bool nValue)
    {
        PassThroughChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnSizeChanged(Size oValue, Size nValue)
    {
        UpdateDisplayArea();
        TextureValid = false;
        SizeChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnSortChanged(bool oValue, bool nValue)
    {
        SortChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnSoundChanged(SoundIndex oValue, SoundIndex nValue)
    {
        SoundChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnTagChanged(any oValue, any nValue)
    {
        TagChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnTextChanged(string oValue, string nValue)
    {
        TextureValid = false;
        TextChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnVisibleChanged(bool oValue, bool nValue)
    {
        CheckIsVisible();
        VisibleChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIsEnabledChanged(bool oValue, bool nValue)
    {
        IsEnabledChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIsVisibleChanged(bool oValue, bool nValue)
    {
        IsVisibleChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIsMovingChanged(bool oValue, bool nValue)
    {
        IsMovingChanged?.Invoke(this, EventArgs::Empty);
    }
    
    void DXControl::OnIsResizingChanged(bool oValue, bool nValue)
    {
        IsResizingChanged?.Invoke(this, EventArgs::Empty);
    }
}
