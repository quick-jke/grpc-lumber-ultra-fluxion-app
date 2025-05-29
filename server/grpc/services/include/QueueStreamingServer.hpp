#ifndef QUEUE_STREAMING_SERVICE_HPP
#define QUEUE_STREAMING_SERVICE_HPP

#include <grpcpp/grpcpp.h>
#include "queue/QueueStreaming.grpc.pb.h"
#include "queue/QueueStreaming.pb.h"

#include "threadpool.h"
#include "tsqueue.h"
#include "db.hpp"

#include <memory>
#include <string>
#include <sstream>


class QueueStreamingServer final : public queue::QueueStreaming::Service {
public:
    QueueStreamingServer();
    grpc::Status QueuePush(grpc::ServerContext* context, grpc::ServerReaderWriter<queue::MessageResponce, queue::NumberRequest>* stream) override;
    grpc::Status QueuePop(grpc::ServerContext* context, ::grpc::ServerReaderWriter<queue::QueueStringResponce, queue::EmptyRequest>* stream) override;

private:
    DB db_;
    std::unique_ptr<ThreadPool> pool_;
    std::mutex mutex_;
};

#endif