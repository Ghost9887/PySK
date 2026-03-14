cmake_minimum_required(VERSION 3.10)
project(dio)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE LIB_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cc
)

list(REMOVE_ITEM LIB_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cc")

file(GLOB_RECURSE TESTS
    ${CMAKE_SOURCE_DIR}/tests/*.cc
)

add_library(dio_lib ${LIB_SOURCES})

target_include_directories(dio_lib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

add_executable(dio src/main.cc)

target_link_libraries(dio
    PRIVATE dio_lib
)

add_executable(dio_tests ${TESTS})

target_link_libraries(dio_tests
    PRIVATE
    dio_lib
    Catch2::Catch2WithMain
)

