cmake_minimum_required(VERSION 3.20)
project(grpcserver)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(queue)
add_subdirectory(grpc)
add_subdirectory(proto)
add_subdirectory(db)

add_executable(${PROJECT_NAME} server.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE grpc)

