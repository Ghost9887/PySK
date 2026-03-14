cmake_minimum_required(VERSION 3.10)
project(dio)

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cc
)

add_executable(dio ${SOURCES})

target_include_directories(dio
    PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)
