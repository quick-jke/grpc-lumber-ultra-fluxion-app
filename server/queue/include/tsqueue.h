#ifndef TSQUEUE_H
#define TSQUEUE_H

#include <queue>
#include <condition_variable>
#include <mutex>

template <typename T>
class TsQueue {
public:
    void push(T const& val) {
        std::lock_guard<std::mutex> queue_lock{queue_mutex_};
        queue_.push(val);
        queue_cv_.notify_one();
    }

    T pop() {
        std::unique_lock<std::mutex> queue_lock{queue_mutex_};
        queue_cv_.wait(queue_lock, [&]{ return !queue_.empty(); });

        T ret = queue_.front();
        queue_.pop();
        return ret;
    }

private:
    std::queue<T> queue_;
    std::condition_variable queue_cv_;
    std::mutex queue_mutex_;
};

#endif
