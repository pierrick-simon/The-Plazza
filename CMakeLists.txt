cmake_minimum_required(VERSION 3.28.3)
project(ThePlazza CXX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/plugins)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
)

set(SRCS
    src/Plazza.cpp
    src/Kitchen.cpp
    src/Connect.cpp
)

set(HEADERS
    include/
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif()

add_executable(plazza ${MAIN} ${SRCS})

target_compile_options(plazza PRIVATE)

add_custom_target(main
    DEPENDS plazza
)

find_library(CRITERION criterion REQUIRED)

set(SRCS_TESTS
    tests/tests_init.cpp
    tests/tests_parsing.cpp
    tests/tests_parse_order.cpp
)

add_executable(tests_run_bin EXCLUDE_FROM_ALL ${SRCS_TESTS} ${SRCS})

target_compile_options(tests_run_bin PRIVATE --coverage)
target_link_options(tests_run_bin PRIVATE --coverage)
target_link_libraries(tests_run_bin criterion )

add_custom_target(tests_run
    COMMAND find ${CMAKE_BINARY_DIR} -name "*.gcda" -delete
    COMMAND ${CMAKE_COMMAND} -E rm -f screenshots/test_save.ppm screenshots/test.ppm
    COMMAND ./tests_run_bin
    DEPENDS tests_run_bin
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
