cmake_minimum_required(VERSION 3.10)
project(SnakeGame C)

# Set C standard
set(CMAKE_C_STANDARD 99)

# Include header files
include_directories(include)

# Source files in the src directory
file(GLOB SRC_FILES "src/*.c")

# Add the main.c file separately
set(MAIN_FILE main.c)

# Combine all source files
set(ALL_FILES ${MAIN_FILE} ${SRC_FILES})

# Create the executable
add_executable(snake ${ALL_FILES})

# Link pthread
find_package(Threads REQUIRED)
target_link_libraries(snake Threads::Threads)
