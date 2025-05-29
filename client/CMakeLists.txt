cmake_minimum_required(VERSION 3.20)
project(grpcclient)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(grpc)
add_subdirectory(proto)

option(BUILD_PUSH_CLIENT "Build client with Push functionality" OFF)
option(BUILD_POP_CLIENT "Build client with Pop functionality" OFF)

if(BUILD_PUSH_CLIENT AND BUILD_POP_CLIENT)
    message(FATAL_ERROR "Выберите только один режим: BUILD_PUSH_CLIENT или BUILD_POP_CLIENT")
elseif(NOT BUILD_PUSH_CLIENT AND NOT BUILD_POP_CLIENT)
    message(FATAL_ERROR "Не выбран режим сборки: установите BUILD_PUSH_CLIENT или BUILD_POP_CLIENT")
endif()

add_executable(${PROJECT_NAME} client.cc)

target_link_libraries(${PROJECT_NAME} PRIVATE grpc)

if(BUILD_PUSH_CLIENT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPUSH_CLIENT)
elseif(BUILD_POP_CLIENT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPOP_CLIENT)
endif()


