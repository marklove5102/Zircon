// DBObject.cpp - MirDB 数据库对象基类实现

#include "DBObject.h"
#include "DBMapping.h"
#include "ADBCollection.h"
#include "Session.h"
#include <sstream>

namespace MirDB
{

// ============================================================================
// INotifyPropertyChanged 实现
// ============================================================================

void INotifyPropertyChanged::OnPropertyChanged(const std::string& propertyName) {
    PropertyChanged.Invoke(this, PropertyChangedEventArgs(propertyName));
}

// ============================================================================
// DBObject 实现
// ============================================================================

DBObject::DBObject() {
    ThisType = &typeid(*this);
}

void DBObject::UseKeys() {
    // C++ 版本需要具体实现外键解析逻辑
    // 这依赖于具体的派生类和 Session 实现
    ForeignKeys.clear();
}

void DBObject::Load(DBMapping* mapping) {
    if (!mapping) return;
    
    std::istringstream mStream(std::string(RawData.begin(), RawData.end()));
    
    for (const auto& dbValue : mapping->Properties) {
        // TODO: 实现具体的值读取逻辑
        // 这里需要根据 DBValue 的类型读取相应的数据
    }
}

void DBObject::Save(DBMapping* mapping) {
    if (!mapping) return;
    
    std::ostringstream mStream;
    
    for (const auto& dbValue : mapping->Properties) {
        // TODO: 实现具体的值写入逻辑
    }
    
    std::string data = mStream.str();
    RawData.assign(data.begin(), data.end());
    
    OnSaved();
}

void DBObject::Delete() {
    if (!Collection || Collection->ReadOnly) return;
    
    if (Collection->Session) {
        Collection->Session->Delete(this);
    }
}

void DBObject::OnCreated() {
    IsModified = true;
    IsLoaded = true;
}

void DBObject::OnLoaded() {
    IsLoaded = true;
}

void DBObject::OnSaved() {
    IsModified = false;
}

void DBObject::OnDeleted() {
    IsDeleted = true;
}

void DBObject::OnChanged(const std::string& propertyName) {
    // 如果尚未加载，标记为已修改
    if (!IsLoaded) {
        IsModified = true;
        return;
    }
    
    // 如果启用了属性变更通知，触发事件
    if (Collection && Collection->RaisePropertyChanges) {
        OnPropertyChanged(propertyName);
    }
}

void DBObject::CreateBindings() {
    // TODO: 实现 DBBindingList 的创建逻辑
    // 这需要反射或模板元编程来查找和初始化 DBBindingList<> 类型的属性
}

void DBObject::CreateLink(void* ob, const std::string& infoName) {
    // TODO: 实现关联链接逻辑
    if (!ob) return;
}

void DBObject::RemoveLink(void* ob, const std::string& infoName) {
    // TODO: 实现关联移除逻辑
    if (!ob) return;
}

} // namespace MirDB
