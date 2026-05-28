cmake_minimum_required(VERSION 3.28.3)
project(ThePlazza CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../${CMAKE_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MAIN
    src/Main.cpp
)

set(SRCS
    ../src/Kitchen.cpp
    ../src/Connect.cpp
    ../src/Reception.cpp
    ../src/Utils.cpp
    ../src/Cook.cpp
    ../src/Chef.cpp
    ../src/IngredientMap.cpp
)

set(BONUS_SRCS
    src/Plazza.cpp
)

set(HEADERS
    include/
    ../include/
)

include_directories(${HEADERS})

option(ENABLE_ASAN "Enable Address Sanitizer" OFF)

if (ENABLE_ASAN)
    set(ASAN_FLAGS -fsanitize=address -fno-omit-frame-pointer)
    add_compile_options(${ASAN_FLAGS})
    add_link_options(${ASAN_FLAGS})
endif()

add_executable(plazza ${MAIN} ${SRCS} ${BONUS_SRCS})

target_compile_options(plazza PRIVATE)

target_link_libraries(plazza sfml-graphics sfml-window sfml-system sfml-audio)

add_custom_target(main
    DEPENDS plazza
)
