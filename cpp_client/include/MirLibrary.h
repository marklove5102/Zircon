// MirLibrary.h - C++ 翻译的镜像库类
// 对应 C# 中的 Client.Envir.MirLibrary

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <mutex>
#include "MirImage.h"

/**
 * @brief 镜像资源库类
 * 
 * 负责加载和管理.WIL/.WZL 格式的资源库文件
 * 包含多个 MirImage 对象，用于存储游戏图形资源
 */
class MirLibrary {
public:
    // ==================== 基本信息 ====================
    
    // 库版本
    int Version = 0;
    
    // 文件名
    std::string FileName;
    
    // 加载状态
    bool Loaded = false;
    bool Loading = false;
    
    // 互斥锁 (用于线程安全加载)
    std::mutex LoadLocker;
    
    // 图像数组
    std::vector<std::unique_ptr<MirImage>> Images;
    
    // ==================== 构造函数/析构函数 ====================
    
    /**
     * @brief 构造函数
     * 
     * @param fileName 库文件路径
     */
    explicit MirLibrary(const std::string& fileName);
    
    ~MirLibrary();
    
    // 禁止拷贝
    MirLibrary(const MirLibrary&) = delete;
    MirLibrary& operator=(const MirLibrary&) = delete;
    
    // ==================== 库读取 ====================
    
    /**
     * @brief 读取库文件头信息
     * 
     * 解析库文件结构，创建 MirImage 对象数组
     */
    void ReadLibrary();
    
    // ==================== 图像访问 ====================
    
    /**
     * @brief 获取指定索引图像的尺寸
     * 
     * @param index 图像索引
     * @return Size 宽度和高度
     */
    Size GetSize(int index);
    
    /**
     * @brief 获取指定索引图像的偏移量
     * 
     * @param index 图像索引
     * @return Point X 和 Y 偏移
     */
    Point GetOffSet(int index);
    
    /**
     * @brief 获取指定索引的图像对象
     * 
     * @param index 图像索引
     * @return MirImage* 图像对象指针
     */
    MirImage* GetImage(int index);
    
    /**
     * @brief 创建并返回指定类型的图像
     * 
     * @param index 图像索引
     * @param type 图像类型 (Image/Shadow/Overlay)
     * @return MirImage* 图像对象指针
     */
    MirImage* CreateImage(int index, ImageType type);
    
    // ==================== 像素检测 ====================
    
    /**
     * @brief 检测指定位置是否有可见像素
     * 
     * @param index 图像索引
     * @param location 检测位置
     * @param accurate 是否精确检测
     * @param offSet 是否考虑偏移
     * @return true 有可见像素
     * @return false 无可见像素或透明
     */
    bool VisiblePixel(int index, const Point& location, bool accurate = true, bool offSet = false);
    
    // ==================== 绘制方法 ====================
    
    /**
     * @brief 绘制图像到屏幕
     * 
     * @param index 图像索引
     * @param x X 坐标
     * @param y Y 坐标
     * @param colour 颜色调制
     * @param area 裁剪区域
     * @param opacity 透明度
     * @param type 图像类型
     * @param shadow 阴影类型
     */
    void Draw(int index, float x, float y, uint32_t colour, 
              const Rectangle& area, float opacity, ImageType type, uint8_t shadow = 0);
    
    /**
     * @brief 绘制图像到屏幕 (使用偏移)
     * 
     * @param index 图像索引
     * @param x X 坐标
     * @param y Y 坐标
     * @param colour 颜色调制
     * @param useOffSet 是否使用偏移
     * @param opacity 透明度
     * @param type 图像类型
     * @param scale 缩放比例
     */
    void Draw(int index, float x, float y, uint32_t colour, 
              bool useOffSet, float opacity, ImageType type, float scale = 1.0f);
    
    /**
     * @brief 绘制混合效果图像
     * 
     * @param index 图像索引
     * @param size 尺寸
     * @param colour 颜色调制
     * @param x X 坐标
     * @param y Y 坐标
     * @param angle 旋转角度
     * @param opacity 透明度
     * @param type 图像类型
     * @param useOffSet 是否使用偏移
     * @param shadow 阴影类型
     */
    void DrawBlend(int index, float size, uint32_t colour, float x, float y, 
                   float angle, float opacity, ImageType type, 
                   bool useOffSet = false, uint8_t shadow = 0);
    
    /**
     * @brief 绘制混合效果图像 (简化版)
     * 
     * @param index 图像索引
     * @param x X 坐标
     * @param y Y 坐标
     * @param colour 颜色调制
     * @param useOffSet 是否使用偏移
     * @param rate 混合速率
     * @param type 图像类型
     * @param shadow 阴影类型
     */
    void DrawBlend(int index, float x, float y, uint32_t colour, 
                   bool useOffSet, float rate, ImageType type, uint8_t shadow = 0);
    
private:
    // 文件流
    std::ifstream FileStream;
    
    // 二进制数据
    std::vector<uint8_t> FileData;
    
    /**
     * @brief 检查图像索引是否有效
     * 
     * @param index 图像索引
     * @return true 有效
     * @return false 无效
     */
    bool CheckImage(int index);
};
