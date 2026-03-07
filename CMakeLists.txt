cmake_minimum_required(VERSION 3.10)
project(dio)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(dio ${SOURCES})
