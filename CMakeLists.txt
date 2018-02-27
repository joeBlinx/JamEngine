cmake_minimum_required(VERSION 3.9)
project(2Dengine)

set(CMAKE_CXX_STANDARD 17)
file(GLOB_RECURSE HPP_FILES inc/2dEngine/*.hpp inc/2dEngine/*.tpp inc/2dEngine/*.h)
file(GLOB_RECURSE CPP_FILES src/*.cpp)

include_directories(BEFORE_SYSTEM PRIVATE inc)
include_directories(BEFORE_SYSTEM PRIVATE inc/2dEngine)

set(SOURCE_FILES ${HPP_FILES} ${CPP_FILES} )

add_compile_options(-Wall -pedantic -Wextra )
add_subdirectory(glish)

add_library(2Dengine ${SOURCE_FILES})
target_link_libraries(2Dengine glish SDL2 SDL2_image)


file(GLOB_RECURSE TEST_HPP_FILES test/*.hpp )
file(GLOB_RECURSE TEST_CPP_FILES test/*.cpp)


set(TEST_SOURCE_FILES ${TEST_HPP_FILES} ${TEST_CPP_FILES} )
add_executable(2dtest ${TEST_SOURCE_FILES})

add_dependencies(2dtest 2Dengine)
target_link_libraries(2dtest 2Dengine SDL2 GL GLEW glish GLU)