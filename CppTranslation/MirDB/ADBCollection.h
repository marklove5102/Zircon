// ADBCollection.h - MirDB 抽象数据库集合类
// 对应 C# MirDB.ADBCollection

#ifndef MIRDB_AD_COLLECTION_H
#define MIRDB_AD_COLLECTION_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <typeinfo>

namespace MirDB
{

// 前向声明
class DBObject;
class Session;
class DBMapping;

// ============================================================================
// ADBCollection - 抽象数据库集合基类
// ============================================================================

class ADBCollection {
public:
    // 属性
    virtual int32 Count() const = 0;

    // 内部属性
    DBMapping* Mapping = nullptr;
    bool IsSystemData = false;
    Session* Session = nullptr;
    const std::type_info* Type = nullptr;
    bool ReadOnly = false;
    bool RaisePropertyChanges = true;

    // 虚方法
    virtual void Load(const std::vector<CSharpCompat::byte>& data, DBMapping* mapping) = 0;
    virtual void SaveObjects() = 0;
    virtual std::vector<CSharpCompat::byte> GetSaveData() = 0;
    virtual void Delete(DBObject* ob) = 0;

    // 创建对象
    virtual DBObject* CreateObject() = 0;

    // 获取对象
    virtual DBObject* GetObjectByIndex(int32 index) = 0;
    virtual DBObject* GetObjectByFieldName(const std::string& fieldName, const std::any& value) = 0;

    // 加载完成回调
    virtual void OnLoaded() = 0;

    // 虚析构函数
    virtual ~ADBCollection() = default;

protected:
    ADBollection() = default;
};

} // namespace MirDB

#endif // MIRDB_AD_COLLECTION_H
