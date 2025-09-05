cmake_minimum_required(VERSION 3.10)
project(LearnThruFailure)

set(CMAKE_CXX_STANDARD 17)   # or 20 if you want modern C++ features

# Add the main executable
add_executable(tests tests.cpp insertion_sort.cpp)

# Optional: add include directories
target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR})
