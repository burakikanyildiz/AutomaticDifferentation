cmake_minimum_required(VERSION 2.8.12.2)
project(project4-burak-yildiz-2015400069-master)

set(CMAKE_CXX_STANDARD 11 )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp variable.cpp variable.h graph.cpp graph.h function.cpp function.h)
add_executable(project4 ${SOURCE_FILES})