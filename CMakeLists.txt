cmake_minimum_required(VERSION 3.10)
project(dio)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

list(FILTER SOURCES EXCLUDE REGEX "main.cpp")

add_library(dio_lib ${SOURCES})

target_include_directories(dio_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}
    src/main.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE dio_lib
)

add_subdirectory(tests)
