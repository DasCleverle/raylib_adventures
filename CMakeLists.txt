cmake_minimum_required(VERSION 3.28)

project(cleverles_attacking CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include("${PROJECT_SOURCE_DIR}/dependencies.cmake")

add_subdirectory(src bin)
