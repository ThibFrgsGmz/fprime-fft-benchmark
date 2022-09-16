cmake_minimum_required(VERSION 3.13)
project(
    StandaloneStaticLibrary
    VERSION 0.0.1
    DESCRIPTION "Example of F´ integration as standalone static library"
    HOMEPAGE_URL "https://"
    LANGUAGES CXX)
set(EXAMPLE_APP app.elf)
set(EXAMPLE_SRCS ../../Top/Main.cpp)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
add_executable(EXAMPLE_APP ${EXAMPLE_SRCS})
target_link_libraries(EXAMPLE_APP PRIVATE ${CMAKE_SOURCE_DIR}/libRef.a Threads::Threads)