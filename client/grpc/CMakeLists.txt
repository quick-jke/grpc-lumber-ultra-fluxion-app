add_library(grpc INTERFACE)

add_subdirectory(services)

target_link_libraries(grpc
    INTERFACE
        Services
)


target_include_directories(grpc
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)