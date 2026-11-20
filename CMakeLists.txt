cmake_minimum_required(VERSION 3.27)
project(AP4a)

set(CMAKE_CXX_STANDARD 17)

add_executable(AP4a main.cpp
        Server.cpp
        Server.h
        Sensor.cpp
        Sensor.h
        Scheduler.cpp
        Scheduler.h)
