cmake_minimum_required(VERSION 3.23)

project(dsa_c C)

option(dsa_c_ENABLE_TESTING "Enable testing" ${PROJECT_IS_TOP_LEVEL})

if(dsa_c_ENABLE_TESTING)
    enable_testing()
    find_package(cmocka REQUIRED)
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)


add_executable(driver
    src/main.c
)


add_library(dsa STATIC
   src/vector.c
   src/slist.c
)

target_link_libraries(driver dsa)
target_include_directories(dsa PUBLIC include)
if(dsa_c_ENABLE_TESTING)
    add_executable(vector-test
        tests/vector-test.c
    )
    target_link_libraries(vector-test PRIVATE cmocka::cmocka)
    target_link_libraries(vector-test PUBLIC dsa)
    add_test(NAME vector-test COMMAND vector-test)
endif()
