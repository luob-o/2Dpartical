
cmake_minimum_required(VERSION 3.20)

project(raycasting LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.2
    GIT_SHALLOW ON
)

FetchContent_MakeAvailable(SFML)

add_executable(main
    src/main.cpp
)
add_executable(a
    src/a.cpp
)

add_executable(kangwei
    src/kangwei.cpp
)
target_link_libraries(kangwei PRIVATE sfml-graphics)
add_executable(testt src/testt.cpp)
target_link_libraries(testt PRIVATE sfml-graphics)
if(MSVC)
    target_compile_options(kangwei PRIVATE /utf-8)
endif()
target_link_libraries(main PRIVATE
    sfml-graphics
)

target_link_libraries(a PRIVATE sfml-graphics)
