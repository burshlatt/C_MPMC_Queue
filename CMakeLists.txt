cmake_minimum_required(VERSION 3.10)
project(mpmc_queue C)

set(CMAKE_C_STANDARD 11)

add_executable(mpmc_queue src/main.c src/mpmc_q_imp/mpmc_queue.c)

include_directories(
    src/mpmc_q_imp
)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mpmc_queue PRIVATE Threads::Threads)
