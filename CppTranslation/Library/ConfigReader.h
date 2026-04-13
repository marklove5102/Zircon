// ConfigReader.h - Library 配置文件读取器
// 对应 C# Library.ConfigReader

#ifndef LIBRARY_CONFIG_READER_H
#define LIBRARY_CONFIG_READER_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <unordered_map>
#include <regex>

namespace Library
{

// 前向声明
class ConfigPath;
class ConfigSection;

// ============================================================================
// ConfigReader - 静态配置读取器类
// ============================================================================

class ConfigReader {
public:
    // 静态成员
    static std::unordered_map<std::type_index, void*> ConfigObjects;
    
private:
    static std::regex HeaderRegex;
    static std::regex EntryRegex;
    static std::regex ColorRegex;
    
    // 配置内容存储
    using SectionMap = std::unordered_map<std::string, std::string>;
    using ConfigMap = std::unordered_map<std::string, SectionMap>;
    static std::unordered_map<std::type_index, ConfigMap> ConfigContents;
    
public:
    // 加载所有配置
    static void Load();
    
    // 保存所有配置
    static void Save();
    
    // 读取各种类型的值
    template<typename T>
    static T Read(const std::type_index& type, const std::string& section, 
                  const std::string& key, T defaultValue);
    
    // 写入各种类型的值
    template<typename T>
    static void Write(const std::type_index& type, const std::string& section,
                      const std::string& key, T value);
    
private:
    static void ReadConfig(const std::type_index& type, const std::string& path, void* ob);
    static void SaveConfig(const std::type_index& type, const std::string& path, void* ob);
    static bool TryGetEntry(const std::type_index& type, const std::string& section, 
                           const std::string& key, std::string& value);
};

// ============================================================================
// ConfigPath - 配置路径属性
// ============================================================================

class ConfigPath {
public:
    std::string Path;
    
    ConfigPath(const std::string& path) : Path(path) {}
};

// ============================================================================
// ConfigSection - 配置节属性
// ============================================================================

class ConfigSection {
public:
    std::string Section;
    
    ConfigSection(const std::string& section) : Section(section) {}
};

} // namespace Library

#endif // LIBRARY_CONFIG_READER_H
