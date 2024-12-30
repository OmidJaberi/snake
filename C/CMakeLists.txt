cmake_minimum_required(VERSION 3.10)
project(SnakeGame C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB SRC_FILES "src/*.c")

set(MAIN_FILE main.c)

set(ALL_FILES ${MAIN_FILE} ${SRC_FILES})

add_executable(snake ${ALL_FILES})

find_package(Threads REQUIRED)
target_link_libraries(snake Threads::Threads)
