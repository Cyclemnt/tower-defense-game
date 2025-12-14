cmake_minimum_required(VERSION 3.16)
project(tower_defense_cxx VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp ${CMAKE_SOURCE_DIR}/src/*.cc ${CMAKE_SOURCE_DIR}/src/*.cxx)

add_executable(${PROJECT_NAME} ${SOURCES})

# include top-level include so that #include "core/..." works
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Allow overriding SFML_DIR / CMAKE_PREFIX_PATH from environment or command line
# (ex: cmake -DSFML_DIR=/chemin/vers/sfml/lib/cmake/SFML -B build)
if(NOT DEFINED SFML_DIR)
  set(SFML_DIR $ENV{SFML_DIR})
endif()

option(SFML_STATIC_LIBRARIES "Link SFML statically" OFF)
find_package(SFML 3 REQUIRED COMPONENTS Graphics Audio Window System)
find_package(TGUI REQUIRED)

target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Audio SFML::Window SFML::System TGUI::TGUI)
