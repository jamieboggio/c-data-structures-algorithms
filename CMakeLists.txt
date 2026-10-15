cmake_minimum_required(VERSION 3.23)

project(dsa_c C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_COMPILER clang)

add_executable(driver
    src/main.c
)


add_executable(vector-test
    tests/vector-test.c
)

set_target_properties(vector-test PROPERTIES C_STANDARD 17)

add_library(dsa STATIC
   src/vector.c 
)

target_link_libraries(driver dsa)
target_link_libraries(vector-test dsa)
target_include_directories(dsa PUBLIC include)


