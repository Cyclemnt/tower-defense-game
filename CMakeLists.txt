cmake_minimum_required(VERSION 3.16)
project(TowerDefense CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include directory
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Create executable
add_executable(tower_defense ${SOURCES})