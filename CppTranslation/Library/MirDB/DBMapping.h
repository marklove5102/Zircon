// DBMapping.h - MirDB 数据库映射类
// 对应 C# MirDB.DBMapping

#ifndef MIRDB_DB_MAPPING_H
#define MIRDB_DB_MAPPING_H

#include "../Common/CSharpCompat.h"
#include <string>
#include <vector>
#include <typeinfo>

namespace MirDB
{

// 前向声明
class DBValue;

// ============================================================================
// DBMapping - 数据库类型映射
// ============================================================================

class DBMapping {
public:
    // 属性
    const std::type_info* Type = nullptr;
    std::string TypeName;
    std::vector<DBValue*> Properties;

    // 构造函数
    DBMapping() = default;
    explicit DBMapping(const std::type_info* type);
    
    // 从读取器加载
    DBMapping(CSharpCompat::IO::BinaryReader& reader);

    // 保存到写入器
    void Save(CSharpCompat::IO::BinaryWriter& writer);

    // 检查是否匹配
    bool IsMatch(const DBMapping* mapping) const;

    // 析构函数
    ~DBMapping();
};

} // namespace MirDB

#endif // MIRDB_DB_MAPPING_H
