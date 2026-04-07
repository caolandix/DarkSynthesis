# Sets the minimum version of CMake required to build the project
cmake_minimum_required(VERSION 3.31.6)

# Sets the project name and version
project(DarkSynthesis VERSION 1.0)

# Specifies the C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Adds an executable target called "MyExecutable" built from "main.cpp"
add_executable(DarkSynthesis main.cpp)

file(GLOB SOURCE_FILES "./src/*.cpp")
file(GLOB HEADER_FILES "./inc/*.h")

