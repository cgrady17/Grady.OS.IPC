cmake_minimum_required(VERSION 3.4)
project(Grady_OS_IPC)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c")

set(SOURCE_FILES ForkPipe.c)
add_executable(Grady_OS_IPC ${SOURCE_FILES})