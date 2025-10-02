cmake_minimum_required(VERSION 3.16)
project(TowerDefense CXX)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Find SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Find TGUI
find_package(TGUI REQUIRED)

# Create executable
add_executable(tower_defense ${SOURCES})

# Link libraries
target_link_libraries(tower_defense PRIVATE SFML::Graphics SFML::Window SFML::System TGUI::TGUI)
