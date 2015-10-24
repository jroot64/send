cmake_minimum_required(VERSION 3.2)
project(raspberry_remote_master)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    daemon.cpp
    daemon.h
    RCSwitch.cpp
    RCSwitch.h
    send.cpp)

add_executable(raspberry_remote_master ${SOURCE_FILES})