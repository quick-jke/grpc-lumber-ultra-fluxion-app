add_library(grpc INTERFACE)

add_subdirectory(core)
add_subdirectory(services)

target_link_libraries(grpc
    INTERFACE
        Core
        Services
)


target_include_directories(grpc
    INTERFACE
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)