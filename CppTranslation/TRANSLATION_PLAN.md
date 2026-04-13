# C# 到 C++ 翻译计划

## 项目概述
- **源语言**: C# (.NET)
- **目标语言**: C++17
- **总文件数**: 805 个 C# 文件
- **主要项目**: 14 个项目文件夹

## 项目结构与文件统计

| 项目名称 | 文件数 | 优先级 | 说明 |
|---------|--------|--------|------|
| MirDB | 23 | 1 | 数据库核心，无外部依赖 |
| LibraryCore | 56 | 2 | 核心库，依赖 MirDB |
| Library | 48 | 3 | 客户端/服务器共享库 |
| ServerLibrary | 417 | 4 | 服务器核心逻辑 |
| Client | 107 | 5 | 客户端渲染和UI |
| Server | 89 | 6 | 服务器主程序 |
| LibraryEditor | 17 | 7 | 编辑器工具 |
| PluginCore | 13 | 8 | 插件系统 |
| PatchManager | 8 | 9 | 补丁管理 |
| Launcher | 8 | 10 | 启动器 |
| Patcher | 6 | 11 | 补丁程序 |
| PluginStandalone | 4 | 12 | 独立插件 |
| ImageManager | 8 | 13 | 图片管理 |
| ServerCore | 1 | 14 | 服务器核心 |

## 翻译顺序（按依赖关系）

### 阶段 1: 基础层
1. **MirDB** - 数据库对象系统
2. **LibraryCore** - 核心枚举、函数、网络包

### 阶段 2: 共享库
3. **Library** - 客户端/服务器共享代码

### 阶段 3: 服务器端
4. **ServerLibrary** - 服务器游戏逻辑
5. **Server** - 服务器主程序

### 阶段 4: 客户端
6. **Client** - 客户端渲染、场景、UI控件

### 阶段 5: 工具程序
7. **LibraryEditor**, **PluginCore**, **PatchManager**, **Launcher**, **Patcher**

---

## C# 特性到 C++ 映射表

### 类型系统映射

| C# 类型 | C++ 类型 | 头文件 |
|--------|---------|--------|
| `bool` | `bool` | `<boolean>` |
| `byte` | `uint8_t` | `<cstdint>` |
| `sbyte` | `int8_t` | `<cstdint>` |
| `short` | `int16_t` | `<cstdint>` |
| `ushort` | `uint16_t` | `<cstdint>` |
| `int` | `int32_t` | `<cstdint>` |
| `uint` | `uint32_t` | `<cstdint>` |
| `long` | `int64_t` | `<cstdint>` |
| `ulong` | `uint64_t` | `<cstdint>` |
| `float` | `float` | - |
| `double` | `double` | - |
| `decimal` | `double` 或自定义 | - |
| `char` | `char16_t` (Unicode) | `<cstdint>` |
| `string` | `std::string` | `<string>` |
| `object` | `std::any` 或模板 | `<any>` |
| `var` | `auto` | - |

### 容器映射

| C# 类型 | C++ 类型 | 头文件 |
|--------|---------|--------|
| `List<T>` | `std::vector<T>` | `<vector>` |
| `Dictionary<K,V>` | `std::unordered_map<K,V>` | `<unordered_map>` |
| `SortedDictionary<K,V>` | `std::map<K,V>` | `<map>` |
| `HashSet<T>` | `std::unordered_set<T>` | `<unordered_set>` |
| `Queue<T>` | `std::queue<T>` | `<queue>` |
| `Stack<T>` | `std::stack<T>` | `<stack>` |
| `LinkedList<T>` | `std::list<T>` | `<list>` |
| `BindingList<T>` | `std::vector<T>` + 通知机制 | 自定义 |
| `IEnumerable<T>` | 迭代器/范围 | `<iterator>` |
| `IEnumerator<T>` | 迭代器 | `<iterator>` |

### 可空类型映射

| C# 类型 | C++ 类型 | 头文件 |
|--------|---------|--------|
| `T?` (值类型) | `std::optional<T>` | `<optional>` |
| `T?` (引用类型) | `T*` 或 `std::shared_ptr<T>` | `<memory>` |
| `Nullable<T>` | `std::optional<T>` | `<optional>` |

### 智能指针映射

| C# 概念 | C++ 实现 |
|--------|---------|
| 引用类型自动GC | `std::shared_ptr<T>` |
| 弱引用 | `std::weak_ptr<T>` |
| 独占所有权 | `std::unique_ptr<T>` |
| IDisposable | RAII + 析构函数 |

### 委托和事件映射

| C# 类型 | C++ 类型 | 头文件 |
|--------|---------|--------|
| `Action` | `std::function<void()>` | `<functional>` |
| `Action<T>` | `std::function<void(T)>` | `<functional>` |
| `Func<T,R>` | `std::function<R(T)>` | `<functional>` |
| `event EventHandler` | 自定义事件系统 | 自定义 |
| `delegate` | `std::function` | `<functional>` |

### LINQ 到 STL 算法映射

| C# LINQ | C++ STL | 头文件 |
|--------|---------|--------|
| `.Where()` | `std::copy_if` / 范围过滤 | `<algorithm>` |
| `.Select()` | `std::transform` | `<algorithm>` |
| `.FirstOrDefault()` | 手动查找 | `<algorithm>` |
| `.First()` | `std::find_if` + 解引用 | `<algorithm>` |
| `.Any()` | `std::any_of` | `<algorithm>` |
| `.All()` | `std::all_of` | `<algorithm>` |
| `.Count()` | `std::distance` 或 `.size()` | `<iterator>` |
| `.Sum()` | `std::accumulate` | `<numeric>` |
| `.Aggregate()` | `std::accumulate` | `<numeric>` |
| `.OrderBy()` | `std::sort` + lambda | `<algorithm>` |
| `.GroupBy()` | 手动分组到 map | `<unordered_map>` |
| `.Join()` | 手动嵌套循环或 map | - |
| `.Distinct()` | `std::unique` (需排序) | `<algorithm>` |
| `.Concat()` | `insert` 或 `copy` | `<algorithm>` |
| `.Take()` | 范围或子向量 | - |
| `.Skip()` | 迭代器偏移 | - |

### 类特性映射

| C# 特性 | C++ 实现 |
|--------|---------|
| `class` | `class` |
| `struct` | `struct` |
| `interface` | 纯虚基类 (abstract class) |
| `abstract class` | 含纯虚函数的类 |
| `sealed class` | `final` 类 |
| `static class` | `namespace` 或含静态成员的类 |
| `partial class` | .h/.cpp 分离声明 |
| `record` | `struct` + `operator==` |

### 成员特性映射

| C# 特性 | C++ 实现 |
|--------|---------|
| `property { get; set; }` | getter/setter 方法 |
| `readonly` | `const` 成员 |
| `const` | `constexpr` |
| `static` | `static` |
| `virtual` | `virtual` |
| `override` | `override` (C++11) |
| `new` (隐藏) | 重名方法 (隐藏基类) |
| `base.Method()` | `BaseClass::Method()` |
| `this` | `this` |

### 访问修饰符映射

| C# | C++ |
|----|-----|
| `public` | `public` |
| `private` | `private` |
| `protected` | `protected` |
| `internal` | `friend` 或约定 |
| `protected internal` | `protected` + `friend` |

### 异常处理映射

| C# | C++ |
|----|-----|
| `try-catch-finally` | `try-catch` + RAII |
| `throw new Exception()` | `throw std::runtime_error()` |
| `Exception` | `std::exception` |
| `ArgumentNullException` | `std::invalid_argument` |
| `InvalidOperationException` | `std::logic_error` |
| `NotImplementedException` | `throw std::runtime_error("Not implemented")` |

### 反射和特性映射

| C# | C++ 实现 |
|----|---------|
| `typeof(T)` | `typeid(T)` |
| `GetType()` | `typeid(*this)` |
| `Attribute` | 宏或元数据类 |
| `GetCustomAttribute<T>()` | 自定义元数据系统 |
| `PropertyInfo` | 自定义反射系统 |
| `MethodInfo` | 函数指针/`std::function` |

### 序列化映射

| C# | C++ |
|----|-----|
| `BinaryWriter` | 自定义二进制写入 |
| `BinaryReader` | 自定义二进制读取 |
| `MemoryStream` | `std::stringstream` |
| `FileStream` | `std::fstream` |
| `JsonSerializer` | nlohmann/json 或 rapidjson |

### 其他特性映射

| C# | C++ |
|----|-----|
| `foreach` | range-based for (`for (auto& x : container)`) |
| `lock(obj)` | `std::lock_guard<std::mutex>` |
| `async/await` | `std::async`/`std::future` 或协程 |
| `yield return` | 生成器模式或协程 |
| `using (var x = ...)` | RAII / `std::unique_ptr` |
| `??` 空合并 | `value.value_or(default)` |
| `?.` 空传播 | 条件检查 |
| `nameof(x)` | 字符串字面量或 `__func__` |
| `fixed` | 栈数组或 `std::array` |
| `unsafe` | 原始指针 (避免使用) |
| `checked/unchecked` | 手动溢出检查或不检查 |

---

## 命名约定

保持与 C# 完全一致的命名：
- 文件夹名：相同
- 文件名：相同（.cs → .h/.cpp）
- 类名：相同（ PascalCase）
- 方法名：相同（PascalCase）
- 属性名：相同（PascalCase）
- 字段名：相同（_前缀或驼峰）
- 参数名：相同（camelCase）
- 命名空间：相同（使用 C++ namespace）

---

## 文件组织结构

每个 C# 文件对应：
- `XXX.h` - 头文件（声明）
- `XXX.cpp` - 实现文件（定义）

对于简单的类或模板，可以只有 `.h` 文件。

### 目录结构示例
```
CppTranslation/
├── Common/           # 通用工具函数
│   ├── CSharpCompat.h
│   ├── CSharpCompat.cpp
│   ├── Events.h
│   └── Events.cpp
├── MirDB/
│   ├── DBObject.h
│   ├── DBObject.cpp
│   └── ...
├── LibraryCore/
│   ├── Enum.h
│   ├── Functions.h
│   ├── Functions.cpp
│   └── ...
└── ...
```

---

## 编译配置建议

### CMakeLists.txt 要点
- C++17 标准
- 包含所有项目目录
- 链接必要的库（Boost等）
- 平台特定设置

### 依赖库
- **Boost**: 可选，用于更多容器和工具
- **nlohmann/json**: JSON 序列化
- **fmt**: 格式化输出
- **spdlog**: 日志记录

---

## 特殊注意事项

1. **内存管理**: C# 有 GC，C++ 需要手动管理或使用智能指针
2. **字符串**: C# string 是 Unicode，C++ 需要使用 std::u16string 或转换
3. **集合行为**: C# 集合抛出异常 vs C++ 未定义行为
4. **线程安全**: C# lock vs C++ mutex
5. **事件系统**: 需要实现类似 C# 的事件订阅/取消订阅机制
6. **属性系统**: C# properties 需要转换为 getter/setter 方法
7. **泛型**: C# 泛型 vs C++ 模板
8. **反射**: C# 内置反射 vs C++ 需要自定义实现

---

## 测试策略

1. 单元测试每个翻译的类
2. 对比 C# 和 C++ 的输出
3. 集成测试整个系统
4. 性能基准测试

---

## 进度追踪

- [ ] 创建工具函数库
- [ ] 翻译 MirDB (23 文件)
- [ ] 翻译 LibraryCore (56 文件)
- [ ] 翻译 Library (48 文件)
- [ ] 翻译 ServerLibrary (417 文件)
- [ ] 翻译 Client (107 文件)
- [ ] 翻译 Server (89 文件)
- [ ] 翻译其他项目 (47 文件)
- [ ] 创建 CMake 构建系统
- [ ] 编译测试
- [ ] 功能验证
