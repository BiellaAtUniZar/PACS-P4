cmake_minimum_required(VERSION 3.0.2)
project(lab1)
set(CMAKE_BUILD_TYPE Release)
set(DCMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
include_directories(include)
add_executable(thread_pool_ src/smallpt_thread_pool.cpp)
target_link_libraries(thread_pool_ PRIVATE pthread)