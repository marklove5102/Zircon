// DBCollection.h - MirDB 泛型数据库集合类
// 对应 C# MirDB.DBCollection<T>

#ifndef MIRDB_DB_COLLECTION_H
#define MIRDB_DB_COLLECTION_H

#include "../Common/CSharpCompat.h"
#include <vector>
#include <unordered_map>
#include <string>
#include "ADBCollection.h"

namespace MirDB
{

// 前向声明
class DBObject;
class Session;
class DBMapping;

// ============================================================================
// DBCollection<T> - 泛型数据库集合
// ============================================================================

template<typename T>
class DBCollection : public ADBCollection {
private:
    int32 Index = 0;
    
    // 绑定列表
    std::vector<T*> Binding;
    
    // 字典用于快速查找 (index -> object)
    std::unordered_map<int32, T*> Dictionary;
    
    // 版本有效性标志
    bool VersionValid = false;
    
    // 保存列表
    std::vector<T*>* SaveList = nullptr;

public:
    // 索引器
    T* operator[](int32 index) {
        return Binding[index];
    }

    // 计数
    int32 Count() const override {
        return static_cast<int32>(Binding.size());
    }

    // 获取绑定列表
    std::vector<T*>& GetBinding() {
        return Binding;
    }

    // 构造函数
    explicit DBCollection(Session* session);

    // 析构函数
    ~DBCollection();

    // 创建新对象并添加到集合
    T* CreateNewObject();

    // 重写基类方法
    void Load(const std::vector<CSharpCompat::byte>& data, DBMapping* mapping) override;
    void SaveObjects() override;
    std::vector<CSharpCompat::byte> GetSaveData() override;
    void Delete(DBObject* ob) override;
    DBObject* CreateObject() override;
    DBObject* GetObjectByIndex(int32 index) override;
    DBObject* GetObjectByFieldName(const std::string& fieldName, const std::any& value) override;
    void OnLoaded() override;

private:
    // 创建新对象
    T* CreateNew();
};

} // namespace MirDB

#endif // MIRDB_DB_COLLECTION_H
