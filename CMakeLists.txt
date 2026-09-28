#
# @author Diego García Hernández
# @brief CMakeLists.txt simple example. You can use this as a template for your projects
#        This does not generate documentation
#        It doesn't build any library
# CMakeLists.txt defines the whole build
# CMake reads CMakeLists.txt sequentially
#
# Build process:
#   1. cd <project_folder>
#   2. mkdir build
#   3. cd build
#   4. cmake ..
#   5. make

cmake_minimum_required(VERSION 3.20)

project(P5_MS-CFLP-CI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})

file(GLOB_RECURSE SOURCES
    ${PROJECT_ROOT}/src/*.cc
    ${PROJECT_ROOT}/src/*.cpp
)

file(GLOB_RECURSE HEADERS
    ${PROJECT_ROOT}/includes/*.h
    ${PROJECT_ROOT}/includes/*.hpp
)

add_executable(P1_Automata_pila ${SOURCES} ${HEADERS})

target_include_directories(P1_Automata_pila PRIVATE
    ${PROJECT_ROOT}/include
)

target_compile_options(P1_Automata_pila PRIVATE -Wall -Wextra -Wpedantic)