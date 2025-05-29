file(GLOB QUEUE_SOURCES "src/*.cc")

add_library(Queue STATIC ${QUEUE_SOURCES})

target_include_directories(Queue PUBLIC include)
