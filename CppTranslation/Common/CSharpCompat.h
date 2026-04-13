// CSharpCompat.h - C# 到 C++ 兼容性工具库
// 提供 C# 特性的 C++ 实现

#ifndef CSHARP_COMPAT_H
#define CSHARP_COMPAT_H

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <optional>
#include <functional>
#include <memory>
#include <algorithm>
#include <numeric>
#include <type_traits>
#include <stdexcept>
#include <sstream>
#include <cstdint>
#include <chrono>
#include <mutex>
#include <atomic>

namespace CSharpCompat
{

// ============================================================================
// 类型别名 - 匹配 C# 类型
// ============================================================================

using byte = uint8_t;
using sbyte = int8_t;
using int16 = int16_t;
using uint16 = uint16_t;
using int32 = int32_t;
using uint32 = uint32_t;
using int64 = int64_t;
using uint64 = uint64_t;
using single = float;
using double_ = double;
using decimal = double;  // C# decimal 使用 double 近似
using char16 = char16_t;
using string = std::string;
using object = std::any;

// ============================================================================
// 可空类型
// ============================================================================

template<typename T>
using Nullable = std::optional<T>;

// 辅助函数
template<typename T>
inline bool HasValue(const std::optional<T>& opt) {
    return opt.has_value();
}

template<typename T>
inline T GetValueOrDefault(const std::optional<T>& opt, T defaultValue = T{}) {
    return opt.value_or(defaultValue);
}

// ============================================================================
// 委托类型 - 对应 C# Action/Func
// ============================================================================

// Action (无参数无返回值)
using Action = std::function<void()>;

// Action<T1..T8>
template<typename T1>
using Action1 = std::function<void(T1)>;

template<typename T1, typename T2>
using Action2 = std::function<void(T1, T2)>;

template<typename T1, typename T2, typename T3>
using Action3 = std::function<void(T1, T2, T3)>;

template<typename T1, typename T2, typename T3, typename T4>
using Action4 = std::function<void(T1, T2, T3, T4)>;

// Func<TResult>
template<typename TResult>
using Func0 = std::function<TResult()>;

// Func<T, TResult>
template<typename T, typename TResult>
using Func1 = std::function<TResult(T)>;

template<typename T1, typename T2, typename TResult>
using Func2 = std::function<TResult(T1, T2)>;

template<typename T1, typename T2, typename T3, typename TResult>
using Func3 = std::function<TResult(T1, T2, T3)>;

template<typename T1, typename T2, typename T3, typename T4, typename TResult>
using Func4 = std::function<TResult(T1, T2, T3, T4)>;

// Predicate<T>
template<typename T>
using Predicate = std::function<bool(T)>;

// ============================================================================
// 事件系统 - 模拟 C# event
// ============================================================================

// 通用事件处理器模板
template<typename... Args>
class Event
{
public:
    using Handler = std::function<void(Args...)>;
    
    // 订阅事件
    void operator+=(Handler handler) {
        handlers.push_back(handler);
    }
    
    // 取消订阅
    void operator-=(Handler handler) {
        handlers.erase(
            std::remove(handlers.begin(), handlers.end(), handler),
            handlers.end()
        );
    }
    
    // 触发事件
    void Invoke(Args... args) {
        for (auto& handler : handlers) {
            if (handler) {
                handler(args...);
            }
        }
    }
    
    // 清空所有订阅
    void Clear() {
        handlers.clear();
    }
    
    // 检查是否有订阅者
    bool HasSubscribers() const {
        return !handlers.empty();
    }

private:
    std::vector<Handler> handlers;
};

// EventHandler (object sender, EventArgs e)
struct EventArgs {
    static EventArgs Empty;
};

template<typename TEventArgs = EventArgs>
class EventHandler : public Event<object*, TEventArgs> {
    // 继承 Event 的所有功能
};

// ============================================================================
// LINQ 风格扩展函数
// ============================================================================

namespace Linq
{

// Where - 过滤
template<typename T, typename Predicate>
std::vector<T> Where(const std::vector<T>& source, Predicate pred) {
    std::vector<T> result;
    std::copy_if(source.begin(), source.end(), std::back_inserter(result), pred);
    return result;
}

// Select - 投影
template<typename T, typename U, typename Selector>
std::vector<U> Select(const std::vector<T>& source, Selector selector) {
    std::vector<U> result;
    result.reserve(source.size());
    std::transform(source.begin(), source.end(), std::back_inserter(result), selector);
    return result;
}

// FirstOrDefault - 第一个或默认
template<typename T, typename Predicate>
std::optional<T> FirstOrDefault(const std::vector<T>& source, Predicate pred) {
    auto it = std::find_if(source.begin(), source.end(), pred);
    if (it != source.end()) {
        return *it;
    }
    return std::nullopt;
}

template<typename T>
std::optional<T> FirstOrDefault(const std::vector<T>& source) {
    if (!source.empty()) {
        return source.front();
    }
    return std::nullopt;
}

// First - 第一个（抛出异常如果没有）
template<typename T, typename Predicate>
T First(const std::vector<T>& source, Predicate pred) {
    auto it = std::find_if(source.begin(), source.end(), pred);
    if (it != source.end()) {
        return *it;
    }
    throw std::runtime_error("Sequence contains no matching element");
}

template<typename T>
T First(const std::vector<T>& source) {
    if (source.empty()) {
        throw std::runtime_error("Sequence contains no elements");
    }
    return source.front();
}

// Any - 是否有任何元素满足条件
template<typename T, typename Predicate>
bool Any(const std::vector<T>& source, Predicate pred) {
    return std::any_of(source.begin(), source.end(), pred);
}

template<typename T>
bool Any(const std::vector<T>& source) {
    return !source.empty();
}

// All - 是否所有元素都满足条件
template<typename T, typename Predicate>
bool All(const std::vector<T>& source, Predicate pred) {
    return std::all_of(source.begin(), source.end(), pred);
}

// Count - 计数
template<typename T, typename Predicate>
size_t Count(const std::vector<T>& source, Predicate pred) {
    return std::count_if(source.begin(), source.end(), pred);
}

template<typename T>
size_t Count(const std::vector<T>& source) {
    return source.size();
}

// Sum - 求和
template<typename T>
auto Sum(const std::vector<T>& source) {
    return std::accumulate(source.begin(), source.end(), T{});
}

template<typename T, typename Selector>
auto Sum(const std::vector<T>& source, Selector selector) {
    using ResultType = decltype(selector(T{}));
    return std::accumulate(source.begin(), source.end(), ResultType{},
        [selector](ResultType acc, const T& item) {
            return acc + selector(item);
        });
}

// OrderBy - 排序
template<typename T, typename KeySelector>
std::vector<T> OrderBy(std::vector<T> source, KeySelector selector) {
    std::sort(source.begin(), source.end(),
        [selector](const T& a, const T& b) {
            return selector(a) < selector(b);
        });
    return source;
}

// OrderByDescending - 降序排序
template<typename T, typename KeySelector>
std::vector<T> OrderByDescending(std::vector<T> source, KeySelector selector) {
    std::sort(source.begin(), source.end(),
        [selector](const T& a, const T& b) {
            return selector(a) > selector(b);
        });
    return source;
}

// Distinct - 去重
template<typename T>
std::vector<T> Distinct(std::vector<T> source) {
    std::sort(source.begin(), source.end());
    source.erase(std::unique(source.begin(), source.end()), source.end());
    return source;
}

// Take - 取前 N 个
template<typename T>
std::vector<T> Take(const std::vector<T>& source, size_t count) {
    if (count >= source.size()) {
        return source;
    }
    return std::vector<T>(source.begin(), source.begin() + count);
}

// Skip - 跳过前 N 个
template<typename T>
std::vector<T> Skip(const std::vector<T>& source, size_t count) {
    if (count >= source.size()) {
        return {};
    }
    return std::vector<T>(source.begin() + count, source.end());
}

// Concat - 连接
template<typename T>
std::vector<T> Concat(std::vector<T> source, const std::vector<T>& other) {
    source.insert(source.end(), other.begin(), other.end());
    return source;
}

// Aggregate - 聚合
template<typename T, typename Accumulator>
T Aggregate(const std::vector<T>& source, Accumulator acc) {
    if (source.empty()) {
        throw std::runtime_error("Sequence contains no elements");
    }
    return std::accumulate(source.begin() + 1, source.end(), source.front(), acc);
}

// Contains - 包含
template<typename T>
bool Contains(const std::vector<T>& source, const T& value) {
    return std::find(source.begin(), source.end(), value) != source.end();
}

// ToList - 转换为 vector (用于其他容器)
template<typename T>
std::vector<T> ToList(const std::set<T>& source) {
    return std::vector<T>(source.begin(), source.end());
}

template<typename K, typename V>
std::vector<std::pair<K, V>> ToList(const std::unordered_map<K, V>& source) {
    return std::vector<std::pair<K, V>>(source.begin(), source.end());
}

} // namespace Linq

// ============================================================================
// 字符串工具
// ============================================================================

namespace StringExtensions
{

// IsNullOrEmpty
inline bool IsNullOrEmpty(const std::string& str) {
    return str.empty();
}

// IsNullOrWhiteSpace
inline bool IsNullOrWhiteSpace(const std::string& str) {
    return str.find_first_not_of(" \t\n\r") == std::string::npos;
}

// Format
template<typename... Args>
std::string Format(const std::string& format, Args... args) {
    std::ostringstream oss;
    // 简单实现，可以使用 fmt 库获得更好的支持
    oss << format;  // TODO: 实现完整的格式化
    return oss.str();
}

// Split
inline std::vector<std::string> Split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Join
inline std::string Join(const std::string& separator, const std::vector<std::string>& strings) {
    if (strings.empty()) return "";
    
    std::ostringstream oss;
    oss << strings[0];
    for (size_t i = 1; i < strings.size(); ++i) {
        oss << separator << strings[i];
    }
    return oss.str();
}

// Substring
inline std::string Substring(const std::string& str, size_t start, size_t length = std::string::npos) {
    return str.substr(start, length);
}

// IndexOf
inline size_t IndexOf(const std::string& str, const std::string& value, size_t start = 0) {
    size_t pos = str.find(value, start);
    return pos != std::string::npos ? pos : static_cast<size_t>(-1);
}

// LastIndexOf
inline size_t LastIndexOf(const std::string& str, const std::string& value) {
    size_t pos = str.rfind(value);
    return pos != std::string::npos ? pos : static_cast<size_t>(-1);
}

// Replace
inline std::string Replace(const std::string& str, const std::string& oldValue, const std::string& newValue) {
    std::string result = str;
    size_t pos = 0;
    while ((pos = result.find(oldValue, pos)) != std::string::npos) {
        result.replace(pos, oldValue.length(), newValue);
        pos += newValue.length();
    }
    return result;
}

// ToUpper
inline std::string ToUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

// ToLower
inline std::string ToLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

// Trim
inline std::string Trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

// StartsWith
inline bool StartsWith(const std::string& str, const std::string& prefix) {
    return str.size() >= prefix.size() && str.compare(0, prefix.size(), prefix) == 0;
}

// EndsWith
inline bool EndsWith(const std::string& str, const std::string& suffix) {
    return str.size() >= suffix.size() && 
           str.compare(str.size() - suffix.size(), suffix.size(), suffix) == 0;
}

} // namespace StringExtensions

// ============================================================================
// 时间相关
// ============================================================================

using TimeSpan = std::chrono::duration<int64_t, std::ratio<1, 10000000>>; // 100-nanosecond ticks like C#
using DateTime = std::chrono::system_clock::time_point;

namespace TimeUtils
{

// DateTime.Now
inline DateTime Now() {
    return std::chrono::system_clock::now();
}

// DateTime.UtcNow
inline DateTime UtcNow() {
    return std::chrono::system_clock::now();
}

// DateTime.MinValue
inline DateTime MinValue() {
    return DateTime::min();
}

// DateTime.MaxValue  
inline DateTime MaxValue() {
    return DateTime::max();
}

// TimeSpan.FromSeconds
inline TimeSpan FromSeconds(double seconds) {
    return std::chrono::duration_cast<TimeSpan>(std::chrono::duration<double>(seconds));
}

// TimeSpan.FromMinutes
inline TimeSpan FromMinutes(int minutes) {
    return std::chrono::duration_cast<TimeSpan>(std::chrono::minutes(minutes));
}

// TimeSpan.FromHours
inline TimeSpan FromHours(int hours) {
    return std::chrono::duration_cast<TimeSpan>(std::chrono::hours(hours));
}

// TimeSpan.FromDays
inline TimeSpan FromDays(int days) {
    return std::chrono::duration_cast<TimeSpan>(std::chrono::hours(days * 24));
}

// TimeSpan.FromMilliseconds
inline TimeSpan FromMilliseconds(int milliseconds) {
    return std::chrono::duration_cast<TimeSpan>(std::chrono::milliseconds(milliseconds));
}

// TimeSpan.FromTicks
inline TimeSpan FromTicks(int64_t ticks) {
    return TimeSpan(ticks);
}

// Get total seconds from TimeSpan
inline double TotalSeconds(const TimeSpan& span) {
    return std::chrono::duration<double>(span).count();
}

// Get total minutes from TimeSpan
inline double TotalMinutes(const TimeSpan& span) {
    return TotalSeconds(span) / 60.0;
}

// Get total hours from TimeSpan
inline double TotalHours(const TimeSpan& span) {
    return TotalMinutes(span) / 60.0;
}

// Get total days from TimeSpan
inline double TotalDays(const TimeSpan& span) {
    return TotalHours(span) / 24.0;
}

// Get ticks from TimeSpan
inline int64_t Ticks(const TimeSpan& span) {
    return span.count();
}

// Add TimeSpan to DateTime
inline DateTime Add(DateTime dt, TimeSpan span) {
    return dt + std::chrono::duration_cast<std::chrono::system_clock::duration>(span);
}

// Subtract DateTime to get TimeSpan
inline TimeSpan Subtract(DateTime dt1, DateTime dt2) {
    auto diff = dt1 - dt2;
    return std::chrono::duration_cast<TimeSpan>(diff);
}

// Compare two DateTimes
inline int Compare(DateTime dt1, DateTime dt2) {
    if (dt1 < dt2) return -1;
    if (dt1 > dt2) return 1;
    return 0;
}

// Max of two TimeSpans
inline TimeSpan Max(TimeSpan a, TimeSpan b) {
    return a > b ? a : b;
}

// Min of two TimeSpans
inline TimeSpan Min(TimeSpan a, TimeSpan b) {
    return a < b ? a : b;
}

} // namespace TimeUtils

// ============================================================================
// Math 工具
// ============================================================================

namespace MathUtils
{

template<typename T>
T Max(T a, T b) {
    return std::max(a, b);
}

template<typename T>
T Min(T a, T b) {
    return std::min(a, b);
}

template<typename T>
T Clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

template<typename T>
T Abs(T value) {
    return std::abs(value);
}

inline int32 Round(double value) {
    return static_cast<int32>(std::round(value));
}

inline int32 Floor(double value) {
    return static_cast<int32>(std::floor(value));
}

inline int32 Ceil(double value) {
    return static_cast<int32>(std::ceil(value));
}

} // namespace MathUtils

// ============================================================================
// 数组工具
// ============================================================================

namespace ArrayUtils
{

// Empty array singleton
template<typename T>
const std::vector<T>& Empty() {
    static const std::vector<T> empty;
    return empty;
}

// Resize array
template<typename T>
void Resize(std::vector<T>& array, size_t newSize) {
    array.resize(newSize);
}

// Reverse array
template<typename T>
void Reverse(std::vector<T>& array) {
    std::reverse(array.begin(), array.end());
}

// Find index
template<typename T, typename Predicate>
int32 FindIndex(const std::vector<T>& array, Predicate pred) {
    auto it = std::find_if(array.begin(), array.end(), pred);
    if (it != array.end()) {
        return static_cast<int32>(it - array.begin());
    }
    return -1;
}

// Find last index
template<typename T, typename Predicate>
int32 FindLastIndex(const std::vector<T>& array, Predicate pred) {
    for (auto it = array.rbegin(); it != array.rend(); ++it) {
        if (pred(*it)) {
            return static_cast<int32>(array.rend() - it - 1);
        }
    }
    return -1;
}

} // namespace ArrayUtils

// ============================================================================
// 字典工具
// ============================================================================

namespace DictionaryUtils
{

// TryGetValue for unordered_map
template<typename K, typename V>
bool TryGetValue(const std::unordered_map<K, V>& dict, const K& key, V& value) {
    auto it = dict.find(key);
    if (it != dict.end()) {
        value = it->second;
        return true;
    }
    return false;
}

// TryGetValue for map
template<typename K, typename V>
bool TryGetValue(const std::map<K, V>& dict, const K& key, V& value) {
    auto it = dict.find(key);
    if (it != dict.end()) {
        value = it->second;
        return true;
    }
    return false;
}

// ContainsKey
template<typename K, typename V, typename MapType>
bool ContainsKey(const MapType& dict, const K& key) {
    return dict.find(key) != dict.end();
}

// ContainsValue
template<typename K, typename V>
bool ContainsValue(const std::unordered_map<K, V>& dict, const V& value) {
    return std::any_of(dict.begin(), dict.end(),
        [&value](const auto& pair) { return pair.second == value; });
}

} // namespace DictionaryUtils

// ============================================================================
// 反射工具（简化版）
// ============================================================================

namespace ReflectionUtils
{

// Get type name
template<typename T>
std::string GetTypeName() {
    // C++ 没有直接的 typeof 名称获取，这是简化版本
    return typeid(T).name();
}

// Check if type is same
template<typename T, typename U>
constexpr bool IsSameType() {
    return std::is_same<T, U>::value;
}

} // namespace ReflectionUtils

// ============================================================================
// 线程安全工具
// ============================================================================

namespace ThreadingUtils
{

// Lock guard wrapper
class LockGuard {
public:
    explicit LockGuard(std::mutex& mtx) : lock_(mtx) {}
    
private:
    std::lock_guard<std::mutex> lock_;
};

// Monitor.Enter/Exit
class Monitor {
public:
    static void Enter(std::mutex& mtx) {
        mtx.lock();
    }
    
    static void Exit(std::mutex& mtx) {
        mtx.unlock();
    }
};

// Interlocked operations
class Interlocked {
public:
    static int32 Increment(std::atomic<int32>& value) {
        return ++value;
    }
    
    static int32 Decrement(std::atomic<int32>& value) {
        return --value;
    }
    
    static int32 Exchange(std::atomic<int32>& target, int32 value) {
        return target.exchange(value);
    }
    
    static int32 CompareExchange(std::atomic<int32>& target, int32 value, int32 comparand) {
        target.compare_exchange_strong(comparand, value);
        return comparand;
    }
    
    static int64 Increment(std::atomic<int64>& value) {
        return ++value;
    }
    
    static int64 Decrement(std::atomic<int64>& value) {
        return --value;
    }
};

} // namespace ThreadingUtils

// ============================================================================
// IDisposable 接口模拟
// ============================================================================

class IDisposable {
public:
    virtual ~IDisposable() = default;
    virtual void Dispose() = 0;
};

// RAII helper for IDisposable
template<typename T>
class DisposableGuard {
public:
    explicit DisposableGuard(T* disposable) : disposable_(disposable) {}
    
    ~DisposableGuard() {
        if (disposable_) {
            disposable_->Dispose();
        }
    }
    
    // 禁止拷贝
    DisposableGuard(const DisposableGuard&) = delete;
    DisposableGuard& operator=(const DisposableGuard&) = delete;
    
private:
    T* disposable_;
};

// ============================================================================
// 常量定义
// ============================================================================

namespace Constants
{

// DateTime epoch (C# uses January 1, 0001)
// For simplicity, we use Unix epoch
constexpr int64_t UnixEpochTicks = 621355968000000000LL;

// Max values
constexpr int32 MaxInt32 = std::numeric_limits<int32>::max();
constexpr int32 MinInt32 = std::numeric_limits<int32>::min();
constexpr int64 MaxInt64 = std::numeric_limits<int64>::max();
constexpr int64 MinInt64 = std::numeric_limits<int64>::min();

} // namespace Constants

} // namespace CSharpCompat

#endif // CSHARP_COMPAT_H
