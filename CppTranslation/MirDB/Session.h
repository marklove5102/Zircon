// Session.h - MirDB 数据库会话类
// 对应 C# MirDB.Session

#ifndef MIRDB_SESSION_H
#define MIRDB_SESSION_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <unordered_map>
#include <queue>
#include <typeinfo>
#include "Attributes.h"

namespace MirDB
{

// 前向声明
class DBObject;
class ADBCollection;

// ============================================================================
// Session - 数据库会话
// ============================================================================

class Session {
private:
    static constexpr const char* Extension = ".db";
    static constexpr const char* TempExtension = ".TMP";
    static constexpr const char* CompressExtension = ".gz";

    std::string Root;
    std::string BackupRoot;
    SessionMode Mode;

    std::string SystemPath;
    std::string SystemBackupPath;
    std::vector<CSharpCompat::byte> SystemHeader;

    std::string UsersPath;
    std::string UsersBackupPath;
    std::vector<CSharpCompat::byte> UsersHeader;

    // 待解析外键的对象队列
    std::queue<DBObject*> KeyedObjects;

    // 集合字典 (typeName -> collection)
    std::unordered_map<std::string, ADBCollection*> Collections;

public:
    int32 BackUpDelay = 0;

    // 构造函数
    explicit Session(SessionMode mode, 
                     const std::string& root = "./Database/",
                     const std::string& backup = "./Backup/");

    // 析构函数
    ~Session();

    // 保存数据
    void Save(bool commit);
    
    // 提交更改
    void Commit();

    // 获取集合
    template<typename T>
    ADBCollection* GetCollection();

    // 获取对象
    DBObject* GetObject(const std::type_info* type, int32 index);
    DBObject* GetObject(const std::type_info* type, const std::string& fieldName, const std::any& value);

    // 创建对象
    template<typename T>
    T* CreateObject();

    // 删除对象
    void Delete(DBObject* ob);

private:
    // 初始化
    void Initialize();
    void InitializeSystem();
    void InitializeUsers();

    // 保存
    void SaveSystem();
    void SaveUsers();

    // 文件名转换
    static std::string ToFileName(const CSharpCompat::DateTime& time);
    std::string ToBackUpFileName(const CSharpCompat::DateTime& time);
};

} // namespace MirDB

#endif // MIRDB_SESSION_H
