# C# 到 C++ 翻译项目

## 项目状态

本文档记录了将 C# 项目翻译成 C++ 的进度和计划。

## 已完成的工作

### 1. 翻译计划文档
- ✅ 创建了详细的翻译计划 (`TRANSLATION_PLAN.md`)
- ✅ 包含 C# 到 C++ 特性映射表
- ✅ 定义了翻译顺序（按依赖关系）
- ✅ 列出了所有 14 个项目文件夹和 805 个文件

### 2. 工具函数库
- ✅ `Common/CSharpCompat.h` - 核心兼容性库 (843 行)
  - 类型别名 (byte, int32, uint64 等)
  - 可空类型 (Nullable/optional)
  - 委托类型 (Action, Func, Predicate)
  - 事件系统 (Event, EventHandler)
  - LINQ 风格函数 (Where, Select, FirstOrDefault 等)
  - 字符串扩展 (IsNullOrEmpty, Split, Join 等)
  - 时间工具 (DateTime, TimeSpan)
  - 数学工具 (Max, Min, Clamp)
  - 数组工具 (FindIndex, Reverse)
  - 字典工具 (TryGetValue, ContainsKey)
  - 线程安全工具 (LockGuard, Interlocked)
  - IDisposable 接口模拟

- ✅ `Common/CSharpCompat.cpp` - 工具库实现
- ✅ `Common/Events.h` - 高级事件系统 (297 行)
  - ThreadSafeEvent (线程安全事件)
  - WeakEvent (弱引用事件)
  - ValidatedEvent (带验证的事件)
  - OneTimeEvent (一次性事件)
  - AsyncEvent (异步事件)
  - EventAggregator (事件聚合器)

### 3. 目录结构
- ✅ 创建了所有目标文件夹
  ```
  CppTranslation/
  ├── Common/           # 通用工具
  ├── MirDB/            # 数据库核心
  ├── LibraryCore/      # 核心库
  │   ├── SystemModels/
  │   └── Network/
  ├── Library/          # 共享库
  │   ├── SystemModels/
  │   └── Network/
  ├── ServerLibrary/    # 服务器库
  ├── Client/           # 客户端
  └── ...
  ```

### 4. MirDB 项目开始
- ✅ `MirDB/DBObject.h` - DBObject 基类头文件
- ✅ `MirDB/DBObject.cpp` - DBObject 实现

## 待完成的工作

### 阶段 1: MirDB (23 文件) - 进行中
- [ ] DBObject (已创建框架)
- [ ] ADBCollection
- [ ] DBCollection
- [ ] DBBindingList
- [ ] DBMapping
- [ ] Session
- [ ] DBValue
- [ ] 所有 SystemModels (ItemInfo, MonsterInfo, MapInfo 等)

### 阶段 2: LibraryCore (56 文件)
- [ ] Enum.cs
- [ ] Functions.cs
- [ ] Encryption.cs
- [ ] Libraries.cs
- [ ] FrameSet.cs
- [ ] Network 包系统
- [ ] SystemModels

### 阶段 3: Library (48 文件)
- [ ] 网络包
- [ ] 共享模型

### 阶段 4: ServerLibrary (417 文件)
- [ ] 游戏逻辑
- [ ] 数据库模型
- [ ] 环境系统

### 阶段 5: Client (107 文件)
- [ ] 渲染系统
- [ ] UI 控件
- [ ] 场景管理

### 阶段 6: Server (89 文件)
- [ ] 服务器主程序

### 阶段 7: 其他项目 (47 文件)
- [ ] LibraryEditor
- [ ] PluginCore
- [ ] PatchManager
- [ ] Launcher
- [ ] Patcher
- [ ] PluginStandalone
- [ ] ImageManager
- [ ] ServerCore

### 构建系统
- [ ] CMakeLists.txt
- [ ] 编译配置
- [ ] 测试框架

## 关键设计决策

### 1. 命名保持
- 所有文件夹、文件、类、方法名与 C# 完全一致
- 使用 C++ namespace 对应 C# namespace

### 2. 文件组织
- 每个 .cs 文件对应 .h + .cpp
- 简单类可以只有 .h 文件

### 3. 内存管理
- 使用智能指针 (shared_ptr, unique_ptr)
- RAII 模式替代 IDisposable
- 避免原始 new/delete

### 4. 集合类型
- List<T> → std::vector<T>
- Dictionary<K,V> → std::unordered_map<K,V>
- BindingList<T> → std::vector<T> + 通知机制

### 5. 事件系统
- 使用自定义 Event 模板类
- 支持 +=/-= 操作符
- 提供线程安全版本

### 6. 字符串处理
- 使用 std::string
- 提供 StringExtensions 辅助函数

### 7. 时间处理
- DateTime → std::chrono::system_clock::time_point
- TimeSpan → std::chrono::duration

## 下一步行动

1. **完成 MirDB 项目**
   - 实现 ADBCollection, DBCollection, Session
   - 翻译所有 SystemModels

2. **创建 CMake 构建系统**
   - 基本 CMakeLists.txt
   - 编译测试

3. **继续 LibraryCore**
   - 枚举定义
   - 函数库
   - 网络包系统

## 技术挑战

1. **反射系统**: C# 有内置反射，C++ 需要手动实现或使用库
2. **属性系统**: C# properties → C++ getter/setter
3. **LINQ**: 使用 STL 算法 + 自定义扩展
4. **泛型**: C# 泛型 → C++ 模板
5. **异常处理**: 确保异常安全
6. **Unicode 字符串**: C# string 是 UTF-16，需要考虑转换

## 参考资源

- C# 源代码：`/workspace/`
- 翻译计划：`CppTranslation/TRANSLATION_PLAN.md`
- 工具库：`CppTranslation/Common/`

## 联系

如有问题或建议，请查看翻译计划文档中的详细说明。
