cmake_minimum_required(VERSION 3.10)
project(EventScheduler CXX)  # Ensure CXX is specified for C++ projects
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(eventscheduler src/main.cpp src/schd.cpp)