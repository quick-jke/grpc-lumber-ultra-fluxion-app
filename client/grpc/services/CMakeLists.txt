file(GLOB SERVICES_SOURCES "src/*.cc")

add_library(Services STATIC ${SERVICES_SOURCES})

target_include_directories(Services PUBLIC include)

target_link_libraries(
    Services 
        PUBLIC 
            protolib
)
