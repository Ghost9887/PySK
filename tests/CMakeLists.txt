cmake_minimum_required(VERSION 3.10)

find_package(Catch2 3 REQUIRED)

add_executable(dio_tests
    tokenization_test.cpp
)

target_link_libraries(dio_tests
    PRIVATE
        dio_lib
        Catch2::Catch2WithMain
)
