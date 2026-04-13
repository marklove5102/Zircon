// MirImage.h - C++ 翻译的镜像图像类
// 对应 C# 中的 Client.Envir.MirImage

#pragma once

#include <cstdint>
#include <d3d9.h>
#include "DXManager.h"

// 图像类型枚举 (对应 Library.ImageType)
enum class ImageType {
    Image,
    Shadow,
    Overlay
};

/**
 * @brief 镜像图像数据类
 * 
 * 存储从库文件加载的图像数据及其 Direct3D 纹理
 * 支持图像、阴影和覆盖层三种类型
 */
class MirImage {
public:
    // ==================== 基本信息 ====================
    
    int Version = 0;
    int Position = 0;
    
    // ==================== 图像属性 ====================
    
    // 主图像
    int16_t Width = 0;
    int16_t Height = 0;
    int16_t OffSetX = 0;
    int16_t OffSetY = 0;
    uint8_t ShadowType = 0;
    
    LPDIRECT3DTEXTURE9 Image = nullptr;
    bool ImageValid = false;
    uint8_t* ImageData = nullptr;
    
    // 阴影
    int16_t ShadowWidth = 0;
    int16_t ShadowHeight = 0;
    int16_t ShadowOffSetX = 0;
    int16_t ShadowOffSetY = 0;
    
    LPDIRECT3DTEXTURE9 Shadow = nullptr;
    bool ShadowValid = false;
    uint8_t* ShadowData = nullptr;
    
    // 覆盖层
    int16_t OverlayWidth = 0;
    int16_t OverlayHeight = 0;
    
    LPDIRECT3DTEXTURE9 Overlay = nullptr;
    bool OverlayValid = false;
    uint8_t* OverlayData = nullptr;
    
    // ==================== 过期时间 ====================
    
    // 用于缓存管理，超过此时间的纹理会被释放
    uint64_t ExpireTime = 0;
    
    // ==================== 构造函数 ====================
    
    MirImage() = default;
    ~MirImage();
    
    // 禁止拷贝
    MirImage(const MirImage&) = delete;
    MirImage& operator=(const MirImage&) = delete;
    
    // ==================== 数据大小计算 ====================
    
    /**
     * @brief 计算图像数据大小
     * 
     * @return int 字节数
     */
    int GetImageDataSize() const {
        int w = Width + (4 - Width % 4) % 4;
        int h = Height + (4 - Height % 4) % 4;
        
        if (Version > 0) {
            return w * h;
        } else {
            return w * h / 2;
        }
    }
    
    /**
     * @brief 计算阴影数据大小
     * 
     * @return int 字节数
     */
    int GetShadowDataSize() const {
        int w = ShadowWidth + (4 - ShadowWidth % 4) % 4;
        int h = ShadowHeight + (4 - ShadowHeight % 4) % 4;
        
        if (Version > 0) {
            return w * h;
        } else {
            return w * h / 2;
        }
    }
    
    /**
     * @brief 计算覆盖层数据大小
     * 
     * @return int 字节数
     */
    int GetOverlayDataSize() const {
        int w = OverlayWidth + (4 - OverlayWidth % 4) % 4;
        int h = OverlayHeight + (4 - OverlayHeight % 4) % 4;
        
        if (Version > 0) {
            return w * h;
        } else {
            return w * h / 2;
        }
    }
    
    // ==================== 像素检测 ====================
    
    /**
     * @brief 检测指定位置是否有可见像素
     * 
     * @param x X 坐标
     * @param y Y 坐标
     * @param accurate 是否精确检测
     * @return true 有可见像素
     * @return false 无可见像素或透明
     */
    bool VisiblePixel(int x, int y, bool accurate = true);
    
    // ==================== 纹理创建 ====================
    
    /**
     * @brief 从二进制读取器创建图像纹理
     * 
     * @param reader 二进制数据
     * @param dataSize 数据大小
     * @return true 成功
     * @return false 失败
     */
    bool CreateImage(const uint8_t* data, size_t dataSize);
    
    /**
     * @brief 从二进制读取器创建阴影纹理
     * 
     * @param reader 二进制数据
     * @param dataSize 数据大小
     * @return true 成功
     * @return false 失败
     */
    bool CreateShadow(const uint8_t* data, size_t dataSize);
    
    /**
     * @brief 从二进制读取器创建覆盖层纹理
     * 
     * @param reader 二进制数据
     * @param dataSize 数据大小
     * @return true 成功
     * @return false 失败
     */
    bool CreateOverlay(const uint8_t* data, size_t dataSize);
    
    // ==================== 纹理释放 ====================
    
    /**
     * @brief 释放图像纹理
     */
    void DisposeImage();
    
    /**
     * @brief 释放阴影纹理
     */
    void DisposeShadow();
    
    /**
     * @brief 释放覆盖层纹理
     */
    void DisposeOverlay();
    
    /**
     * @brief 释放所有纹理
     */
    void DisposeAll();
    
private:
    /**
     * @brief 获取 Direct3D 格式
     * 
     * @return D3DFORMAT
     */
    D3DFORMAT GetDrawFormat() const {
        switch (Version) {
            case 0:
                return D3DFMT_DXT1;
            default:
                return D3DFMT_DXT5;
        }
    }
};
