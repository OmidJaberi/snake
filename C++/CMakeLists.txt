cmake_minimum_required(VERSION 3.10)
project(SnakeGame CXX)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-DWIDTH=15 -DHEIGHT=10)

include_directories(include)

file(GLOB SRC_FILES "src/*.cpp")

set(MAIN_FILE main.cpp)

set(ALL_FILES ${MAIN_FILE} ${SRC_FILES})

add_executable(snake ${ALL_FILES})

# Find and link ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(snake ${CURSES_LIBRARIES})

# Link threads
find_package(Threads REQUIRED)
target_link_libraries(snake Threads::Threads)

