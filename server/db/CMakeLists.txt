file(GLOB DB_SOURCES "src/*.cc")

add_library(DataBase STATIC ${DB_SOURCES})

target_include_directories(DataBase PUBLIC include)

