#include "QueueStreamingClient.hpp"

QueueStreamingClient::QueueStreamingClient(const std::string& connection_string){
    channel_ = grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials());
    stub_ = queue::QueueStreaming::NewStub(channel_);
}

QueueStreamingClient::~QueueStreamingClient(){
}

void QueueStreamingClient::Push(){

    grpc::ClientContext context;

    std::unique_ptr<grpc::ClientReaderWriter<queue::NumberRequest, queue::MessageResponce>> push_stream_(
        stub_->QueuePush(&context));


    std::thread writer([this, &push_stream_]() {
        while (true) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> rvalue(500, 1000);
            std::uniform_int_distribution<std::mt19937::result_type> duration(200, 300);

            queue::NumberRequest request;
            int value = rvalue(rng);
            int mill = duration(rng);
            request.set_value(value);
            std::this_thread::sleep_for(std::chrono::milliseconds(mill));       
            if (!push_stream_->Write(request)) {
                std::cerr << "Failed to write request." << std::endl;
                break;
            }else{
                std::cout << "pushed: " << value << " in " << mill << " milliseconds" << std::endl; 
            }
        }
        push_stream_->WritesDone();
    });

    // std::thread reader([this, &push_stream_]() {
        queue::MessageResponce response;
        while (push_stream_->Read(&response)) {
            std::cout << "Server response: " << response.message() << std::endl;
        }
    // });

    writer.join();
    // reader.join();
    grpc::Status status = push_stream_->Finish();

    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
}
void QueueStreamingClient::Pop(){
    grpc::ClientContext context;

    std::unique_ptr<grpc::ClientReaderWriter<queue::EmptyRequest, queue::QueueStringResponce>> pop_stream_(
        stub_->QueuePop(&context));
    std::thread writer([this, &pop_stream_]() {
        while (true) {
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> duration(200, 300);

            queue::EmptyRequest request;
            int mill = duration(rng);
            std::this_thread::sleep_for(std::chrono::milliseconds(mill));
            if (!pop_stream_->Write(request)) {
                std::cerr << "Failed to write request." << std::endl;
                break;
            }else{
                std::cout << "pop in " << mill << " milliseconds" << std::endl; 
            }
            
        }
        pop_stream_->WritesDone();
    });

    // std::thread reader([this]() {
        queue::QueueStringResponce response;
        while (pop_stream_->Read(&response)) {
            std::cout << "Server response: " << response.message() << std::endl;
        }
    // });

    writer.join();
    // reader.join();
    grpc::Status status = pop_stream_->Finish();

    if (!status.ok()) {
        std::cerr << "RPC failed: " << status.error_message() << std::endl;
    }
}
