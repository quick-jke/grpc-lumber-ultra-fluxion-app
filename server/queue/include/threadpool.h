#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "tsqueue.h"

#include <thread>
#include <vector>
#include <variant>
#include <functional>
#include <iostream>

using Param = std::variant<int, float, std::string>;

enum class TaskType {
    EXECUTE,
    STOP
};

struct Task {
    TaskType type;
    std::function<void(std::vector<Param>)> task;
    std::vector<Param> arguments;
};

class ThreadPool {
public:
    ThreadPool(std::size_t n_threads);
    ~ThreadPool();

    bool push(Task const& task);

private:
    std::thread make_thread_handler(TsQueue<Task>& queue);
    TsQueue<Task> queue_;
    std::vector<std::thread> threads_;
};

#endif
