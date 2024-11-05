cmake_minimum_required(VERSION 3.0.2)
project(lab4)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -O3")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(smallpt_thread_pool src/smallpt_thread_pool.cc)

target_include_directories(smallpt_thread_pool
        PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src/include")
target_link_libraries(pi_taylor_parallel PRIVATE pthread)
target_link_libraries(pi_taylor_parallel_kahan PRIVATE pthread)