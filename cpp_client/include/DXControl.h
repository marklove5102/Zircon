// DXControl.h - C++ 翻译的核心 UI 控制类
// 对应 C# 中的 Client.Controls.DXControl

#pragma once

#include <vector>
#include <memory>
#include <functional>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>

// 前向声明
class DXScene;
class DXManager;

// 颜色结构 (对应 System.Drawing.Color)
struct Color {
    unsigned char R, G, B, A;
    
    static Color FromArgb(int argb) {
        return {
            (unsigned char)((argb >> 16) & 0xFF),
            (unsigned char)((argb >> 8) & 0xFF),
            (unsigned char)(argb & 0xFF),
            (unsigned char)((argb >> 24) & 0xFF)
        };
    }
    
    static Color White() { return {255, 255, 255, 255}; }
    static Color Black() { return {0, 0, 0, 255}; }
    static Color Empty() { return {0, 0, 0, 0}; }
};

// 点结构 (对应 System.Drawing.Point)
struct Point {
    int X, Y;
    
    bool IsEmpty() const { return X == 0 && Y == 0; }
};

// 矩形结构 (对应 System.Drawing.Rectangle)
struct Rectangle {
    int X, Y, Width, Height;
    
    bool IsEmpty() const { return Width <= 0 || Height <= 0; }
    
    static Rectangle Intersect(const Rectangle& a, const Rectangle& b) {
        int x = std::max(a.X, b.X);
        int y = std::max(a.Y, b.Y);
        int w = std::min(a.X + a.Width, b.X + b.Width) - x;
        int h = std::min(a.Y + a.Height, b.Y + b.Height) - y;
        
        if (w < 0 || h < 0) return {0, 0, 0, 0};
        return {x, y, w, h};
    }
};

// Hint 位置枚举
enum class HintPosition {
    Top,
    Bottom,
    Left,
    Right
};

// 声音索引枚举
enum class SoundIndex {
    None = -1
};

// 事件处理类型
using EventHandler = std::function<void(class DXControl*)>;
using MouseEventHandler = std::function<void(class DXControl*, int, int, int)>;
using KeyEventHandler = std::function<void(class DXControl*, int)>;

/**
 * @brief 核心 UI 控制基类
 * 
 * 这是客户端绘图系统的核心基类，所有 UI 控件都继承自此类
 * 负责渲染、事件处理、层级管理等核心功能
 */
class DXControl : public std::enable_shared_from_this<DXControl> {
public:
    // ==================== 静态成员 ====================
    
    // 鼠标焦点控制
    static std::shared_ptr<DXControl> MouseControl;
    static std::shared_ptr<DXControl> FocusControl;
    static std::shared_ptr<DXScene> ActiveScene;
    
    // 静态属性 (从 InterfaceLibrary 读取的默认尺寸)
    static int DefaultHeight;
    static int TabHeight;
    static int HeaderBarSize;
    static int HeaderSize;
    static int FooterSize;
    static int NoFooterSize;
    static int SmallButtonHeight;
    
    // 调试标签
    static std::shared_ptr<class DXLabel> DebugLabel;
    static std::shared_ptr<class DXLabel> HintLabel;
    static std::shared_ptr<class DXLabel> PingLabel;
    
    // ==================== 实例属性 ====================
    
protected:
    // 子控件列表
    std::vector<std::shared_ptr<DXControl>> Controls;
    
    // 基本属性
    bool _AllowDragOut = false;
    bool _AllowResize = false;
    Color _BackColour = Color::Empty();
    bool _Border = false;
    Color _BorderColour = Color::Black();
    float _BorderSize = 1.0f;
    bool _CanResizeHeight = false;
    bool _CanResizeWidth = false;
    bool _DrawTexture = true;
    Rectangle _DisplayArea = {0, 0, 0, 0};
    bool _Enabled = true;
    Color _ForeColour = Color::White();
    std::string _Hint;
    HintPosition _HintPosition = HintPosition::Top;
    bool _IsControl = true;
    Point _Location = {0, 0};
    bool _Modal = false;
    bool _Movable = false;
    bool _IgnoreMoveBounds = false;
    float _Opacity = 1.0f;
    std::shared_ptr<DXControl> _Parent;
    bool _PassThrough = false;
    Point _Size = {0, 0};
    bool _Sort = false;
    SoundIndex _Sound = SoundIndex::None;
    void* _Tag = nullptr;
    std::string _Text;
    bool _Visible = true;
    
    // 内部状态
    bool _IsEnabled = true;
    bool _IsVisible = true;
    bool _IsMoving = false;
    bool _IsResizing = false;
    
    // 纹理相关
    LPDIRECT3DTEXTURE9 ControlTexture = nullptr;
    bool TextureValid = false;
    Point TextureSize = {0, 0};
    DateTime ExpireTime;
    
    // 移动/调整大小相关
    Point MovePoint = {0, 0};
    Point ResizePoint = {0, 0};
    bool ResizeLeft = false;
    bool ResizeRight = false;
    bool ResizeUp = false;
    bool ResizeDown = false;
    
    // 边框信息
    std::vector<D3DXVECTOR2> BorderInformation;

public:
    // ==================== 构造函数/析构函数 ====================
    
    DXControl();
    virtual ~DXControl();
    
    // 禁止拷贝，允许移动
    DXControl(const DXControl&) = delete;
    DXControl& operator=(const DXControl&) = delete;
    
    // ==================== 属性访问器 ====================
    
    // Location
    Point GetLocation() const { return _Location; }
    void SetLocation(const Point& value);
    
    // Size
    Point GetSize() const { return _Size; }
    void SetSize(const Point& value);
    
    // Visible
    bool IsVisible() const { return _IsVisible; }
    void SetVisible(bool value);
    
    // Enabled
    bool IsEnabled() const { return _IsEnabled; }
    void SetEnabled(bool value);
    
    // Parent
    std::shared_ptr<DXControl> GetParent() const { return _Parent; }
    void SetParent(std::shared_ptr<DXControl> parent);
    
    // DisplayArea
    Rectangle GetDisplayArea() const { return _DisplayArea; }
    
    // Opacity
    float GetOpacity() const { return _Opacity; }
    void SetOpacity(float value);
    
    // Text
    std::string GetText() const { return _Text; }
    void SetText(const std::string& value);
    
    // BackColour
    Color GetBackColour() const { return _BackColour; }
    void SetBackColour(const Color& value);
    
    // ForeColour
    Color GetForeColour() const { return _ForeColour; }
    void SetForeColour(const Color& value);
    
    // Border
    bool HasBorder() const { return _Border; }
    void SetBorder(bool value);
    
    // DrawTexture
    bool ShouldDrawTexture() const { return _DrawTexture; }
    void SetDrawTexture(bool value);
    
    // ==================== 核心方法 ====================
    
    /**
     * @brief 绘制控件及其子控件
     * 
     * 渲染流程：
     * 1. OnBeforeDraw() - 触发绘制前事件
     * 2. DrawControl() - 绘制控件本体
     * 3. OnBeforeChildrenDraw() - 触发子控件绘制前事件
     * 4. DrawChildControls() - 绘制所有子控件
     * 5. DrawBorder() - 绘制边框
     * 6. OnAfterDraw() - 触发绘制后事件
     */
    virtual void Draw();
    
    /**
     * @brief 创建控件纹理
     * 
     * 在显存中创建用于缓存控件内容的纹理
     */
    virtual void CreateTexture();
    
    /**
     * @brief 释放纹理资源
     */
    virtual void DisposeTexture();
    
    /**
     * @brief 更新显示区域
     * 
     * 根据位置和父控件计算实际显示区域
     */
    virtual void UpdateDisplayArea();
    
    /**
     * @brief 检查可见性
     */
    virtual void CheckIsVisible();
    
    /**
     * @brief 检查启用状态
     */
    virtual void CheckIsEnabled();
    
    // ==================== 事件处理 ====================
    
    virtual void OnMouseDown(int button, int x, int y);
    virtual void OnMouseUp(int button, int x, int y);
    virtual void OnMouseMove(int x, int y);
    virtual void OnMouseClick(int button, int x, int y);
    virtual void OnMouseDoubleClick(int button, int x, int y);
    virtual void OnMouseWheel(int delta);
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();
    virtual void OnFocus();
    virtual void OnLostFocus();
    virtual void OnKeyDown(int key);
    virtual void OnKeyUp(int key);
    virtual void OnKeyPress(wchar_t key);
    
    // ==================== 事件回调 ====================
    
    EventHandler BeforeDraw;
    EventHandler AfterDraw;
    EventHandler BeforeChildrenDraw;
    EventHandler AllowDragOutChanged;
    EventHandler AllowResizeChanged;
    EventHandler BackColourChanged;
    EventHandler BorderChanged;
    EventHandler BorderColourChanged;
    EventHandler DisplayAreaChanged;
    EventHandler EnabledChanged;
    EventHandler ForeColourChanged;
    EventHandler HintChanged;
    EventHandler LocationChanged;
    EventHandler OpacityChanged;
    EventHandler ParentChanged;
    EventHandler SizeChanged;
    EventHandler TextChanged;
    EventHandler VisibleChanged;
    EventHandler IsEnabledChanged;
    EventHandler IsVisibleChanged;
    
    MouseEventHandler MouseDown;
    MouseEventHandler MouseUp;
    MouseEventHandler MouseMove;
    MouseEventHandler MouseClick;
    MouseEventHandler MouseDoubleClick;
    MouseEventHandler MouseWheel;
    EventHandler MouseEnter;
    EventHandler MouseLeave;
    EventHandler Focus;
    EventHandler LostFocus;
    KeyEventHandler KeyDown;
    KeyEventHandler KeyUp;
    KeyEventHandler KeyPress;
    
    // ==================== 受保护方法 ====================
    
protected:
    virtual void OnBeforeDraw();
    virtual void OnBeforeChildrenDraw();
    virtual void OnAfterDraw();
    virtual void DrawControl();
    virtual void DrawChildControls();
    virtual void DrawBorder();
    
    virtual void OnLocationChanged(const Point& oldValue, const Point& newValue);
    virtual void OnSizeChanged(const Point& oldValue, const Point& newValue);
    virtual void OnVisibleChanged(bool oldValue, bool newValue);
    virtual void OnEnabledChanged(bool oldValue, bool newValue);
    virtual void OnParentChanged(std::shared_ptr<DXControl> oldValue, std::shared_ptr<DXControl> newValue);
    virtual void OnBackColourChanged(const Color& oldValue, const Color& newValue);
    virtual void OnDrawTextureChanged(bool oldValue, bool newValue);
    
    void UpdateBorderInformation();
    
    /**
     * @brief 呈现纹理到屏幕
     * 
     * @param texture Direct3D 纹理
     * @param parent 父控件
     * @param displayArea 显示区域
     * @param colour 颜色调制
     * @param control 源控件
     * @param offX X 偏移
     * @param offY Y 偏移
     * @param scale 缩放比例
     */
    static void PresentTexture(
        LPDIRECT3DTEXTURE9 texture,
        std::shared_ptr<DXControl> parent,
        const Rectangle& displayArea,
        const Color& colour,
        std::shared_ptr<DXControl> control,
        int offX = 0,
        int offY = 0,
        float scale = 1.0f
    );
    
    // ==================== IDisposable 模式 ====================
    
public:
    bool IsDisposed = false;
    virtual void Dispose();
    
protected:
    virtual void Dispose(bool disposing);
    std::function<void(DXControl*)> Disposing;
};
