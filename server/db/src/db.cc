#include "db.hpp"


DB::DB(){}

std::queue<int>& DB::getQueue(){
    return queue_;
}

void DB::push(int value){
    queue_.push(value);
}

void DB::pop(){
    if(!queue_.empty()){
        queue_.pop();
    }
}

std::optional<int> DB::front(){
    if(!queue_.empty()){
        return queue_.front();
    }else{
        return std::nullopt;
    }
}


