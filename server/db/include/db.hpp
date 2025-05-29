#ifndef DATA_BASE_HPP
#define DATA_BASE_HPP

#include <iostream>
#include <queue>
#include <optional>

class DB{
public:
    DB();
    void push(int value);
    void pop();
    std::optional<int> front();
    std::queue<int>& getQueue();
private:
    std::queue<int> queue_;
};

#endif