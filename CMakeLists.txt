cmake_minimum_required(VERSION 2.6)
project(OBJsimplifier)

SET(CMAKE_CXX_FLAGS "-std=c++11")

add_executable(OBJsimplifier main.cpp)

install(TARGETS OBJsimplifier RUNTIME DESTINATION bin)
