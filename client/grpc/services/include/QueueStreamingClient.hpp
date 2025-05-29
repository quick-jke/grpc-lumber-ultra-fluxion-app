#ifndef QUEUE_STREAMING_SERVICE_HPP
#define QUEUE_STREAMING_SERVICE_HPP

#include <iostream>
#include <string>
#include <memory>
#include <random>
#include <thread>

#include <grpcpp/grpcpp.h>
#include "queue/QueueStreaming.grpc.pb.h"
#include "queue/QueueStreaming.pb.h"

class QueueStreamingClient{
public:
    QueueStreamingClient(const std::string& connection_string);
    ~QueueStreamingClient();
    void Push();
    void Pop();

private:
    std::unique_ptr<queue::QueueStreaming::Stub> stub_;
    std::shared_ptr<grpc::ChannelInterface> channel_;

};

#endif