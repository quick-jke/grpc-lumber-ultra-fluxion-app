#include "server_impl.hpp"

ServerImpl::ServerImpl(){
    
}

void ServerImpl::run(const int& port){
    std::cout << "Starting server..." << std::endl;
    std::string server_address("0.0.0.0:" + std::to_string(port));

    QueueStreamingServer service;

    grpc::EnableDefaultHealthCheckService(true);
    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);


    std::unique_ptr<grpc::Server> server;
    try {
        server = builder.BuildAndStart();
        std::cout << "Server built" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to start server: " << e.what() << std::endl;
        return;
    }

    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();

}
