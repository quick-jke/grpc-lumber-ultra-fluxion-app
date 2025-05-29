#include "QueueStreamingServer.hpp"
std::mutex write_mutex_;
QueueStreamingServer::QueueStreamingServer(){
    pool_ = std::make_unique<ThreadPool>(std::thread::hardware_concurrency());
}

std::string queueToString(std::queue<int> q) {
    std::ostringstream oss;
    oss << "[";

    while (!q.empty()) {
        oss << q.front();
        q.pop();
        if (!q.empty()) {
            oss << ", ";
        }
    }

    oss << "]";
    return oss.str();
}

grpc::Status QueueStreamingServer::QueuePush(grpc::ServerContext* context, grpc::ServerReaderWriter<queue::MessageResponce, queue::NumberRequest>* stream){

    std::cout << "Streaming QueuePush opened" << std::endl << std::endl;

    queue::NumberRequest request;

    if (stream->Read(&request)) {

        while (stream->Read(&request)) {
            
            pool_->push({
                TaskType::EXECUTE,
                [this, request, stream](std::vector<Param>){
                    std::unique_lock<std::mutex> lock(mutex_);

                    db_.push(request.value());
                    
                    queue::MessageResponce response;
                    auto res = queueToString(db_.getQueue());
                    response.set_message(res);
                    std::cout << "=======push=======" << std::endl << request.value() << " pushed in queue" << std::endl;
                    std::cout << "current queue: " << res << std::endl << std::endl;

                    if (stream) {
                        stream->Write(response, grpc::WriteOptions());
                    }
                },
                {}
            });
            
        }
    }
    std::cout << "User disconnected" << std::endl;
    std::cout << "Streaming RPC closed" << std::endl;
    return grpc::Status::OK;

}

grpc::Status QueueStreamingServer::QueuePop(grpc::ServerContext* context, ::grpc::ServerReaderWriter<queue::QueueStringResponce, queue::EmptyRequest>* stream){
    std::cout << "Streaming QueuePop opened" << std::endl << std::endl;

    queue::EmptyRequest request;

    if (stream->Read(&request)) {
        while (stream->Read(&request)) {
            pool_->push({
                TaskType::EXECUTE,
                [this, request, stream](std::vector<Param>){
                    queue::QueueStringResponce response;
                    auto front = db_.front();
                    if(front.has_value()){
                        response.set_message(std::to_string(front.value()));
                        std::cout << "=======pop========" << std::endl << "queue pop: " << front.value() << std::endl << std::endl;
                    }else{
                        response.set_message("no value");
                    }
                    db_.pop();
                    std::lock_guard<std::mutex> lock(write_mutex_);
                    if (stream) {
                        stream->Write(response, grpc::WriteOptions());
                    }else{
                        std::cerr << "Failed to send message to client" << std::endl;
                    }

                },
                {}
            });
        }
    }
    std::cout << "User disconnected" << std::endl;
    std::cout << "Streaming RPC closed" << std::endl;
    return grpc::Status::OK;
}