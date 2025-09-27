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

# Find SFML
find_package(SFML 2.5 REQUIRED COMPONENTS graphics window system)

# Find TGUI
find_package(TGUI REQUIRED)

# Create executable
add_executable(tower_defense ${SOURCES})

# Link libraries
target_link_libraries(tower_defense PRIVATE sfml-graphics sfml-window sfml-system tgui)
