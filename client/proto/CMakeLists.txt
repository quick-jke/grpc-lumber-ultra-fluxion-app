find_package(Protobuf CONFIG REQUIRED)
find_package(gRPC REQUIRED)
find_package(Threads)

include_directories(${gRPC_INCLUDE_DIRS})
get_target_property(grpc_cpp_plugin_location gRPC::grpc_cpp_plugin LOCATION)


set(PROTO_FILES
    queue/QueueStreaming.proto
)

add_library(protolib ${PROTO_FILES})

target_link_libraries(protolib
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc
        gRPC::grpc++
        Threads::Threads
)

target_include_directories(protolib
    PUBLIC
        ${gRPC_INCLUDE_DIRS}
        ${Protobuf_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
)

protobuf_generate(
    TARGET protolib
    LANGUAGE cpp
)

protobuf_generate(
    TARGET protolib
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=${grpc_cpp_plugin_location}"
)
