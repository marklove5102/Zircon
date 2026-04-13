// DBBindingList.h - MirDB 数据库绑定列表
// 对应 C# MirDB.DBBindingList<T>

#ifndef MIRDB_DB_BINDING_LIST_H
#define MIRDB_DB_BINDING_LIST_H

#include "../Common/CSharpCompat.h"
#include <vector>
#include <string>
#include "Attributes.h"

namespace MirDB
{

// 前向声明
class DBObject;
class Session;

// ============================================================================
// DBBindingList<T> - 数据库绑定列表
// ============================================================================

template<typename T>
class DBBindingList : public std::vector<T*> {
private:
    Session* Session = nullptr;
    DBObject* Parent = nullptr;
    std::string PropertyName;
    AssociationAttribute* Link = nullptr;

public:
    // 构造函数
    DBBindingList(DBObject* parent, const std::string& propertyName);

    // 析构函数
    ~DBBindingList();

    // 添加项
    void Add(T* item);
    
    // 移除项
    void Remove(T* item);
    
    // 清除
    void Clear();

    // 创建链接
    void CreateLink(T* ob);
    
    // 移除链接
    void RemoveLink(T* ob);

private:
    // 内部插入
    void InsertItem(int32 index, T* item);
    void RemoveItem(int32 index);
};

} // namespace MirDB

#endif // MIRDB_DB_BINDING_LIST_H
