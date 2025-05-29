#include "threadpool.h"

ThreadPool::ThreadPool(std::size_t n_threads) {
    for (std::size_t i = 0; i < n_threads; ++i) {
        threads_.push_back(make_thread_handler(queue_));
    }
}

ThreadPool::~ThreadPool() {
    Task const stop_task{TaskType::STOP, {}, {}};
    for (std::size_t i = 0; i < threads_.size(); ++i) {
        push(stop_task);
    }
    for (auto& thread : threads_) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

bool ThreadPool::push(Task const& task) {
    queue_.push(task);
    return true;
}

std::thread ThreadPool::make_thread_handler(TsQueue<Task>& queue) {
    return std::thread{
        [&queue] {
            while (true) {
                auto const elem = queue.pop();
                switch (elem.type) {
                case TaskType::EXECUTE:
                    elem.task(elem.arguments);
                    break;
                case TaskType::STOP:
                    return;
                }
            }
        }
    };
}
