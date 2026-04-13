// Events.h - 高级事件系统
// 提供更完整的 C# 风格事件实现

#ifndef EVENTS_H
#define EVENTS_H

#include "CSharpCompat.h"
#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
#include <mutex>

namespace CSharpCompat
{

// ============================================================================
// 线程安全事件
// ============================================================================

template<typename... Args>
class ThreadSafeEvent
{
public:
    using Handler = std::function<void(Args...)>;
    using HandlerId = size_t;

    // 订阅事件，返回订阅 ID
    HandlerId operator+=(Handler handler) {
        std::lock_guard<std::mutex> lock(mutex_);
        handlers_.push_back({nextId_, handler});
        return nextId_++;
    }

    // 通过 ID 取消订阅
    void Remove(HandlerId id) {
        std::lock_guard<std::mutex> lock(mutex_);
        handlers_.erase(
            std::remove_if(handlers_.begin(), handlers_.end(),
                [id](const auto& pair) { return pair.first == id; }),
            handlers_.end()
        );
    }

    // 触发事件
    void Invoke(Args... args) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (const auto& [id, handler] : handlers_) {
            if (handler) {
                handler(args...);
            }
        }
    }

    // 清空所有订阅
    void Clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        handlers_.clear();
    }

    // 检查是否有订阅者
    bool HasSubscribers() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return !handlers_.empty();
    }

    // 获取订阅者数量
    size_t SubscriberCount() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return handlers_.size();
    }

private:
    mutable std::mutex mutex_;
    std::vector<std::pair<HandlerId, Handler>> handlers_;
    HandlerId nextId_ = 0;
};

// ============================================================================
// 弱引用事件（避免循环引用）
// ============================================================================

template<typename TObserver, typename... Args>
class WeakEvent
{
public:
    using Handler = std::function<void(TObserver*, Args...)>;

    // 订阅事件（使用 weak_ptr）
    void Subscribe(std::weak_ptr<TObserver> observer, Handler handler) {
        handlers_.push_back({observer, handler});
    }

    // 触发事件（自动清理过期观察者）
    void Invoke(Args... args) {
        // 清理过期的 weak_ptr
        handlers_.erase(
            std::remove_if(handlers_.begin(), handlers_.end(),
                [](const auto& pair) { return pair.first.expired(); }),
            handlers_.end()
        );

        // 通知所有有效的观察者
        for (auto& [weakObs, handler] : handlers_) {
            if (auto obs = weakObs.lock()) {
                handler(obs.get(), args...);
            }
        }
    }

    // 清空所有订阅
    void Clear() {
        handlers_.clear();
    }

private:
    std::vector<std::pair<std::weak_ptr<TObserver>, Handler>> handlers_;
};

// ============================================================================
// 带参数验证的事件
// ============================================================================

template<typename... Args>
class ValidatedEvent
{
public:
    using Handler = std::function<void(Args...)>;
    using Validator = std::function<bool(const Args&...)>;

    // 添加验证器
    void AddValidator(Validator validator) {
        validators_.push_back(validator);
    }

    // 订阅事件
    void operator+=(Handler handler) {
        handlers_.push_back(handler);
    }

    // 取消订阅
    void operator-=(Handler handler) {
        handlers_.erase(
            std::remove(handlers_.begin(), handlers_.end(), handler),
            handlers_.end()
        );
    }

    // 触发事件（先验证）
    bool Invoke(Args... args) {
        // 运行所有验证器
        for (const auto& validator : validators_) {
            if (!validator(args...)) {
                return false;  // 验证失败
            }
        }

        // 触发所有处理器
        for (const auto& handler : handlers_) {
            if (handler) {
                handler(args...);
            }
        }

        return true;  // 成功
    }

    // 清空
    void Clear() {
        handlers_.clear();
        validators_.clear();
    }

private:
    std::vector<Handler> handlers_;
    std::vector<Validator> validators_;
};

// ============================================================================
// 一次性事件（触发后自动清空）
// ============================================================================

template<typename... Args>
class OneTimeEvent
{
public:
    using Handler = std::function<void(Args...)>;

    // 订阅事件
    void operator+=(Handler handler) {
        handlers_.push_back(handler);
    }

    // 触发事件（然后清空）
    void Invoke(Args... args) {
        for (const auto& handler : handlers_) {
            if (handler) {
                handler(args...);
            }
        }
        handlers_.clear();  // 清空所有订阅
    }

    // 手动清空
    void Clear() {
        handlers_.clear();
    }

private:
    std::vector<Handler> handlers_;
};

// ============================================================================
// 异步事件（在后台线程触发）
// ============================================================================

template<typename... Args>
class AsyncEvent
{
public:
    using Handler = std::function<void(Args...)>;

    // 订阅事件
    void operator+=(Handler handler) {
        handlers_.push_back(handler);
    }

    // 取消订阅
    void operator-=(Handler handler) {
        handlers_.erase(
            std::remove(handlers_.begin(), handlers_.end(), handler),
            handlers_.end()
        );
    }

    // 异步触发事件
    void InvokeAsync(Args... args) {
        // 在实际应用中，这里应该使用线程池
        std::thread([this, args...]() {
            for (const auto& handler : handlers_) {
                if (handler) {
                    handler(args...);
                }
            }
        }).detach();
    }

    // 同步触发事件
    void Invoke(Args... args) {
        for (const auto& handler : handlers_) {
            if (handler) {
                handler(args...);
            }
        }
    }

private:
    std::vector<Handler> handlers_;
};

// ============================================================================
// 事件聚合器（组合多个事件）
// ============================================================================

template<typename... Args>
class EventAggregator
{
public:
    using Handler = std::function<void(Args...)>;

    // 添加要聚合的事件
    void AddEvent(Event<Args...>* event) {
        events_.push_back(event);
    }

    // 订阅所有聚合的事件
    void operator+=(Handler handler) {
        for (auto* event : events_) {
            *event += handler;
        }
    }

    // 从所有聚合的事件取消订阅
    void operator-=(Handler handler) {
        for (auto* event : events_) {
            *event -= handler;
        }
    }

private:
    std::vector<Event<Args...>*> events_;
};

} // namespace CSharpCompat

#endif // EVENTS_H
