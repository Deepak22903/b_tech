# Minimum required CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(BubbleSort)

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable with the source file
add_executable(BubbleSort main.cpp)

# Set the output directory for the executable
set_target_properties(BubbleSort PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)
