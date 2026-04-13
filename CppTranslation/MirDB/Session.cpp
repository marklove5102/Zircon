// Session.cpp - MirDB 数据库会话类实现
// 对应 C# MirDB.Session

#include "Session.h"
#include "ADBCollection.h"
#include "DBCollection.h"
#include "../Common/CSharpCompat.h"
#include <fstream>
#include <filesystem>
#include <zlib.h>

namespace fs = std::filesystem;

namespace MirDB
{

// ============================================================================
// Session - 构造函数和析构函数
// ============================================================================

Session::Session(SessionMode mode, const std::string& root, const std::string& backup)
    : Root(root), BackupRoot(backup), Mode(mode), BackUpDelay(0)
{
    // 构建路径
    SystemPath = Root + "System" + Extension;
    SystemBackupPath = BackupRoot + "System/";
    UsersPath = Root + "Users" + Extension;
    UsersBackupPath = BackupRoot + "Users/";
    
    Initialize();
}

Session::~Session()
{
    // 清理集合
    for (auto& pair : Collections) {
        delete pair.second;
    }
    Collections.clear();
}

// ============================================================================
// 初始化方法
// ============================================================================

void Session::Initialize()
{
    // 创建根目录
    if (!fs::exists(Root)) {
        fs::create_directories(Root);
    }

    Collections.clear();
    
    // TODO: 获取所有 DBObject 子类并创建对应的集合
    // C++ 中没有像 C# Reflection 那样简单的方法，需要手动注册或使用模板技巧
    
    InitializeSystem();

    if ((Mode & SessionMode::Users) != SessionMode::None) {
        InitializeUsers();
    }

    // 处理待解析外键的对象
    while (!KeyedObjects.empty()) {
        DBObject* ob = KeyedObjects.front();
        KeyedObjects.pop();
        
        if (ob) {
            ob->UseKeys();
        }
    }

    // 通知所有集合已加载完成
    for (auto& pair : Collections) {
        pair.second->OnLoaded();
    }
}

void Session::InitializeSystem()
{
    std::vector<DBMapping*> mappings;
    
    if ((Mode & SessionMode::System) != SessionMode::None) {
        // 收集所有系统数据的映射
        for (auto& pair : Collections) {
            if (pair.second->IsSystemData) {
                mappings.push_back(&pair.second->Mapping);
            }
        }

        // 写入系统头信息
        CSharpCompat::MemoryStream stream;
        BinaryWriter writer(stream);
        
        writer.Write(static_cast<int32>(mappings.size()));
        for (auto* mapping : mappings) {
            mapping->Save(writer);
        }

        SystemHeader = stream.ToArray();
        mappings.clear();
    }

    // 加载系统数据文件
    if (!fs::exists(SystemPath)) {
        return;
    }

    std::ifstream file(SystemPath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    BinaryReader reader(file);
    
    int32 count = reader.ReadInt32();
    
    for (int32 i = 0; i < count; ++i) {
        mappings.push_back(new DBMapping(reader));
    }

    // 异步加载数据（简化为同步）
    for (auto* mapping : mappings) {
        int32 dataSize = reader.ReadInt32();
        std::vector<CSharpCompat::byte> data = reader.ReadBytes(dataSize);

        ADBCollection* collection = nullptr;
        if (mapping->Type && Collections.count(mapping->Type) > 0) {
            collection = Collections[mapping->Type];
        }

        if (collection) {
            collection->Load(data, *mapping);
        }
    }

    // 清理临时创建的映射
    for (auto* mapping : mappings) {
        delete mapping;
    }
}

void Session::InitializeUsers()
{
    std::vector<DBMapping*> mappings;

    // 收集所有用户数据的映射
    for (auto& pair : Collections) {
        if (!pair.second->IsSystemData) {
            mappings.push_back(&pair.second->Mapping);
        }
    }

    // 写入用户头信息
    CSharpCompat::MemoryStream stream;
    BinaryWriter writer(stream);
    
    writer.Write(static_cast<int32>(mappings.size()));
    for (auto* mapping : mappings) {
        mapping->Save(writer);
    }

    UsersHeader = stream.ToArray();
    mappings.clear();

    // 加载用户数据文件
    if (!fs::exists(UsersPath)) {
        return;
    }

    std::ifstream file(UsersPath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    BinaryReader reader(file);
    
    int32 count = reader.ReadInt32();
    
    for (int32 i = 0; i < count; ++i) {
        mappings.push_back(new DBMapping(reader));
    }

    // 异步加载数据（简化为同步）
    for (auto* mapping : mappings) {
        int32 dataSize = reader.ReadInt32();
        std::vector<CSharpCompat::byte> data = reader.ReadBytes(dataSize);

        ADBCollection* collection = nullptr;
        if (mapping->Type && Collections.count(mapping->Type) > 0) {
            collection = Collections[mapping->Type];
        }

        if (collection) {
            collection->Load(data, *mapping);
        }
    }

    // 清理临时创建的映射
    for (auto* mapping : mappings) {
        delete mapping;
    }
}

// ============================================================================
// 保存方法
// ============================================================================

void Session::Save(bool commit)
{
    // 保存所有集合中的对象
    for (auto& pair : Collections) {
        pair.second->SaveObjects();
    }

    if (commit) {
        Commit();
    }
}

void Session::Commit()
{
    SaveSystem();
    SaveUsers();
}

void Session::SaveSystem()
{
    if ((Mode & SessionMode::System) == SessionMode::None) {
        return;
    }

    if (!fs::exists(Root)) {
        fs::create_directories(Root);
    }

    // 写入临时文件
    std::string tempPath = SystemPath + TempExtension;
    std::ofstream file(tempPath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    BinaryWriter writer(file);
    
    // 写入头信息
    writer.Write(SystemHeader);

    // 写入各集合数据
    for (auto& pair : Collections) {
        if (!pair.second->IsSystemData) {
            continue;
        }

        std::vector<CSharpCompat::byte> data = pair.second->GetSaveData();
        writer.Write(static_cast<int32>(data.size()));
        writer.Write(data);
    }

    file.close();

    // 创建备份目录
    if (!fs::exists(SystemBackupPath)) {
        fs::create_directories(SystemBackupPath);
    }

    // 备份旧文件
    if (fs::exists(SystemPath)) {
        std::string backupFileName = SystemBackupPath + "System " + 
                                      ToBackUpFileName(CSharpCompat::TimeUtils::Now()) + 
                                      Extension + CompressExtension;
        
        // 使用 GZip 压缩备份
        std::ifstream source(SystemPath, std::ios::binary);
        std::ofstream dest(backupFileName, std::ios::binary);
        
        if (source.is_open() && dest.is_open()) {
            // TODO: 实现 GZip 压缩
            // 简化版本：直接复制
            dest << source.rdbuf();
        }

        fs::remove(SystemPath);
    }

    // 移动新文件
    fs::rename(tempPath, SystemPath);
}

void Session::SaveUsers()
{
    if ((Mode & SessionMode::Users) == SessionMode::None) {
        return;
    }

    if (!fs::exists(Root)) {
        fs::create_directories(Root);
    }

    // 写入临时文件
    std::string tempPath = UsersPath + TempExtension;
    std::ofstream file(tempPath, std::ios::binary);
    if (!file.is_open()) {
        return;
    }

    BinaryWriter writer(file);
    
    // 写入头信息
    writer.Write(UsersHeader);

    // 写入各集合数据
    for (auto& pair : Collections) {
        if (pair.second->IsSystemData) {
            continue;
        }

        std::vector<CSharpCompat::byte> data = pair.second->GetSaveData();
        writer.Write(static_cast<int32>(data.size()));
        writer.Write(data);
    }

    file.close();

    // 创建备份目录
    if (!fs::exists(UsersBackupPath)) {
        fs::create_directories(UsersBackupPath);
    }

    // 备份旧文件
    if (fs::exists(UsersPath)) {
        std::string backupFileName = UsersBackupPath + "Users " + 
                                      ToBackUpFileName(CSharpCompat::TimeUtils::Now()) + 
                                      Extension + CompressExtension;
        
        // 使用 GZip 压缩备份
        std::ifstream source(UsersPath, std::ios::binary);
        std::ofstream dest(backupFileName, std::ios::binary);
        
        if (source.is_open() && dest.is_open()) {
            // TODO: 实现 GZip 压缩
            // 简化版本：直接复制
            dest << source.rdbuf();
        }

        fs::remove(UsersPath);
    }

    // 移动新文件
    fs::rename(tempPath, UsersPath);
}

// ============================================================================
// 对象操作方法
// ============================================================================

DBObject* Session::GetObject(const std::type_info* type, int32 index)
{
    std::string typeName = typeid(type).name();
    if (Collections.find(typeName) == Collections.end()) {
        return nullptr;
    }
    
    return Collections[typeName]->GetObjectByIndex(index);
}

DBObject* Session::GetObject(const std::type_info* type, const std::string& fieldName, const std::any& value)
{
    std::string typeName = typeid(type).name();
    if (Collections.find(typeName) == Collections.end()) {
        return nullptr;
    }
    
    return Collections[typeName]->GetObjectbyFieldName(fieldName, value);
}

void Session::Delete(DBObject* ob)
{
    if (!ob || ob->IsDeleted) {
        return;
    }

    std::string typeName = typeid(*ob).name();
    if (Collections.find(typeName) == Collections.end()) {
        return;
    }

    Collections[typeName]->Delete(ob);
    ob->OnDeleted();

    // TODO: 处理属性引用和集合清理
    // C++ 中需要使用反射或手动处理
}

// ============================================================================
// 工具方法
// ============================================================================

std::string Session::ToFileName(const CSharpCompat::DateTime& time)
{
    auto time_t_val = CSharpCompat::TimeUtils::ToTimeT(time);
    std::tm* tm_val = std::gmtime(&time_t_val);
    
    char buffer[64];
    std::snprintf(buffer, sizeof(buffer), "%04d-%02d-%02d %02d-%02d",
                  tm_val->tm_year + 1900,
                  tm_val->tm_mon + 1,
                  tm_val->tm_mday,
                  tm_val->tm_hour,
                  tm_val->tm_min);
    
    return std::string(buffer);
}

std::string Session::ToBackUpFileName(const CSharpCompat::DateTime& time)
{
    if (BackUpDelay == 0) {
        return ToFileName(time);
    }

    // 对齐到备份延迟的整数倍
    auto ticks = CSharpCompat::TimeUtils::Ticks(time);
    int64_t delayTicks = static_cast<int64_t>(BackUpDelay) * CSharpCompat::TimeUtils::TicksPerMinute;
    ticks = ticks - (ticks % delayTicks);
    
    auto adjustedTime = CSharpCompat::TimeUtils::FromTicks(ticks);
    return ToFileName(adjustedTime);
}

} // namespace MirDB
