cmake_minimum_required(VERSION 3.3)
project(towwer-defense-game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
    include/
)

set(SOURCES
    src/main.cpp
)

set(HEADERS
    #include/pca9685.hpp
)

set(CMAKE_BUILD_TYPE Debug) 
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")  

add_executable( main ${SOURCES} ${HEADERS} )
target_link_libraries( main )