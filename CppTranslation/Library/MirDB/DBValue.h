// DBValue.h - MirDB 数据库值类型类
// 对应 C# MirDB.DBValue

#ifndef MIRDB_DB_VALUE_H
#define MIRDB_DB_VALUE_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <unordered_map>
#include <functional>
#include <typeinfo>

namespace MirDB
{

// 前向声明
class DBObject;

// ============================================================================
// DBValue - 数据库属性值
// ============================================================================

class DBValue {
public:
    // 属性
    std::string PropertyName;
    const std::type_info* PropertyType = nullptr;
    std::string PropertyTypeName;
    
    // 属性信息（用于反射）
    std::string PropertyInfoName;  // C++ 中无法直接存储 PropertyInfo，用名称代替
    bool HasPropertyInfo = false;

    // 静态类型注册表
    static std::unordered_map<std::string, const std::type_info*> TypeList;
    
    // 读取函数表
    using ReadFunc = std::function<std::any(CSharpCompat::IO::BinaryReader&)>;
    static std::unordered_map<std::string, ReadFunc> TypeRead;
    
    // 写入函数表
    using WriteFunc = std::function<void(const std::any&, CSharpCompat::IO::BinaryWriter&)>;
    static std::unordered_map<std::string, WriteFunc> TypeWrite;

    // 初始化静态表
    static void InitializeTypes();

    // 构造函数
    DBValue() = default;
    DBValue(CSharpCompat::IO::BinaryReader& reader, const std::type_info* type);
    // C++ 版本使用属性名称和类型信息构造
    DBValue(const std::string& propertyName, const std::type_info* propertyType);

    // 保存
    void Save(CSharpCompat::IO::BinaryWriter& writer);

    // 读取值
    std::any ReadValue(CSharpCompat::IO::BinaryReader& reader);
    
    // 写入值
    void WriteValue(const std::any& value, CSharpCompat::IO::BinaryWriter& writer);

    // 检查是否匹配
    bool IsMatch(const DBValue* value) const;
};

} // namespace MirDB

#endif // MIRDB_DB_VALUE_H
