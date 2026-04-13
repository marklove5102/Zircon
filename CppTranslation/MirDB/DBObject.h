// DBObject.h - MirDB 数据库对象基类
// 对应 C# MirDB.DBObject

#ifndef MIRDB_DB_OBJECT_H
#define MIRDB_DB_OBJECT_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <functional>
#include <typeinfo>

namespace MirDB
{

// 前向声明
class ADBCollection;
class Session;
class DBMapping;

// ============================================================================
// 属性变更事件参数
// ============================================================================

struct PropertyChangedEventArgs {
    std::string PropertyName;
    
    explicit PropertyChangedEventArgs(const std::string& name) : PropertyName(name) {}
};

// ============================================================================
// INotifyPropertyChanged 接口模拟
// ============================================================================

class INotifyPropertyChanged {
public:
    virtual ~INotifyPropertyChanged() = default;
    
    CSharpCompat::Event<void*, const PropertyChangedEventArgs&> PropertyChanged;
    
protected:
    void OnPropertyChanged(const std::string& propertyName);
};

// ============================================================================
// DBObject 基类
// ============================================================================

class DBObject : public INotifyPropertyChanged {
public:
    // 属性
    int32 Index = 0;
    
    // 内部属性
    ADBCollection* Collection = nullptr;
    
    // 外键映射 (propertyName -> index)
    std::unordered_map<std::string, int32> ForeignKeys;
    
    // 类型信息
    const std::type_info* ThisType;
    
    // 状态标志
    bool IsLoaded = false;
    bool IsDeleted = false;
    bool IsModified = false;
    bool IsTemporary = false;
    
    // 原始数据
    std::vector<CSharpCompat::byte> RawData;
    
    // 构造函数
    DBObject();
    virtual ~DBObject() = default;
    
    // 使用外键解析引用
    void UseKeys();
    
    // 加载/保存数据
    void Load(DBMapping* mapping);
    void Save(DBMapping* mapping);
    
    // 删除对象
    void Delete();
    
    // 虚方法
    virtual void OnCreated();
    virtual void OnLoaded();
    virtual void OnSaved();
    virtual void OnDeleted();
    virtual void OnChanged(const std::string& propertyName);
    
    // 属性变更通知辅助方法
protected:
    template<typename T>
    void SetProperty(T& field, const T& value, const std::string& propertyName) {
        if (field == value) return;
        field = value;
        OnChanged(propertyName);
    }
    
    // 友元声明
    friend class ADBCollection;
    friend class Session;
    
private:
    void CreateBindings();
    void CreateLink(void* ob, const std::string& infoName);
    void RemoveLink(void* ob, const std::string& infoName);
};

// ============================================================================
// 特性标记类（用于元数据）
// ============================================================================

class IsIdentityAttribute {};
class IgnorePropertyAttribute {};
class UserObjectAttribute {};
class AssociationAttribute {
public:
    std::string Identity;
};

} // namespace MirDB

#endif // MIRDB_DB_OBJECT_H
