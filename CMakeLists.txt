cmake_minimum_required(VERSION 3.16)
project(tower_defense_cxx)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directory
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Options
option(SFML_STATIC_LIBRARIES "Link SFML statically" OFF)

# Find SFML
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

# Find TGUI
find_package(TGUI REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System TGUI::TGUI)
