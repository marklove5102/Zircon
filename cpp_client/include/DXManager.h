// DXManager.h - C++ 翻译的 Direct3D 管理类
// 对应 C# 中的 Client.Envir.DXManager

#pragma once

#include <vector>
#include <memory>
#include <string>
#include <d3d9.h>
#include <d3dx9.h>

// 前向声明
class DXControl;
class DXScene;
class MirImage;
class DXSound;

// 混合模式枚举 (对应 SlimDX.Direct3D9.BlendMode)
enum class BlendMode {
    NORMAL,
    INVLIGHT,
    COLORFY,
    MASK,
    EFFECTMASK,
    HIGHLIGHT
};

// 尺寸结构
struct Size {
    int Width, Height;
    
    bool operator==(const Size& other) const {
        return Width == other.Width && Height == other.Height;
    }
};

/**
 * @brief Direct3D 渲染管理器
 * 
 * 负责管理 Direct3D 设备、纹理、精灵批处理等核心渲染资源
 * 这是整个绘图系统的底层基础设施
 */
class DXManager {
public:
    // ==================== 单例模式 ====================
    
    static DXManager& Instance() {
        static DXManager instance;
        return instance;
    }
    
    // 禁止拷贝
    DXManager(const DXManager&) = delete;
    DXManager& operator=(const DXManager&) = delete;
    
    // ==================== Direct3D 资源 ====================
    
    // Direct3D 设备
    LPDIRECT3DDEVICE9 Device = nullptr;
    
    // 精灵批处理器 (用于 2D 绘制)
    LPD3DXSPRITE Sprite = nullptr;
    
    // 线条绘制器 (用于边框等)
    LPD3DXLINE Line = nullptr;
    
    // 表面
    LPDIRECT3DSURFACE9 CurrentSurface = nullptr;
    LPDIRECT3DSURFACE9 MainSurface = nullptr;
    
    // Scratch 纹理/表面 (用于离屏渲染)
    LPDIRECT3DTEXTURE9 ScratchTexture = nullptr;
    LPDIRECT3DSURFACE9 ScratchSurface = nullptr;
    
    // 特殊纹理
    LPDIRECT3DTEXTURE9 ColourPallete = nullptr;
    LPDIRECT3DTEXTURE9 LightTexture = nullptr;
    LPDIRECT3DSURFACE9 LightSurface = nullptr;
    LPDIRECT3DTEXTURE9 PoisonTexture = nullptr;
    
    // ==================== 渲染状态 ====================
    
    // 透明度
    float Opacity = 1.0f;
    
    // 混合状态
    bool Blending = false;
    float BlendRate = 1.0f;
    BlendMode BlendMode = BlendMode::NORMAL;
    
    // 设备丢失状态
    bool DeviceLost = false;
    
    // ==================== 对象列表 ====================
    
    // 所有控件列表
    std::vector<std::shared_ptr<DXControl>> ControlList;
    
    // 所有纹理列表
    std::vector<std::shared_ptr<MirImage>> TextureList;
    
    // 所有声音列表
    std::vector<std::shared_ptr<DXSound>> SoundList;
    
    // 有效分辨率列表
    std::vector<Size> ValidResolutions;
    
    // ==================== 常量 ====================
    
    static const int LightWidth = 1024;
    static const int LightHeight = 768;
    
    // ==================== 初始化/清理 ====================
    
    /**
     * @brief 创建 Direct3D 设备和资源
     * 
     * @param hwnd 窗口句柄
     * @param width 窗口宽度
     * @param height 窗口高度
     * @param windowed 是否窗口模式
     * @param vsync 是否启用垂直同步
     * @return true 成功
     * @return false 失败
     */
    bool Create(HWND hwnd, int width, int height, bool windowed, bool vsync);
    
    /**
     * @brief 卸载所有资源
     */
    void Unload();
    
    /**
     * @brief 内存清理 (释放过期纹理)
     */
    void MemoryClear();
    
    // ==================== 表面管理 ====================
    
    /**
     * @brief 设置当前渲染表面
     * 
     * @param surface 目标表面
     */
    void SetSurface(LPDIRECT3DSURFACE9 surface);
    
    /**
     * @brief 设置全局透明度
     * 
     * @param opacity 透明度值 (0.0 - 1.0)
     */
    void SetOpacity(float opacity);
    
    /**
     * @brief 设置混合模式
     * 
     * @param value 是否启用混合
     * @param rate 混合速率
     * @param mode 混合模式
     */
    void SetBlend(bool value, float rate = 1.0f, BlendMode mode = BlendMode::NORMAL);
    
    /**
     * @brief 设置颜色调制
     * 
     * @param colour 颜色值 (ARGB 格式)
     */
    void SetColour(int colour);
    
    /**
     * @brief 设置分辨率
     * 
     * @param size 新分辨率
     */
    void SetResolution(const Size& size);
    
    // ==================== 呈现参数 ====================
    
    struct PresentParams {
        int BackBufferWidth;
        int BackBufferHeight;
        bool Windowed;
        bool VSync;
        D3DFORMAT BackBufferFormat;
    };
    
    PresentParams GetPresentParams() const { return _PresentParams; }
    
private:
    DXManager() = default;
    ~DXManager();
    
    PresentParams _PresentParams;
    
    /**
     * @brief 加载初始纹理
     */
    void LoadTextures();
    
    /**
     * @brief 清理资源
     */
    void CleanUp();
    
    /**
     * @brief 创建光照纹理
     */
    void CreateLight();
    
    /**
     * @brief 配置 Graphics 对象
     */
    void ConfigureGraphics();
};

// 便捷访问宏
#define DXMANAGER DXManager::Instance()
