cmake_minimum_required(VERSION 3.28)

project(raylib_adventures CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include("${PROJECT_SOURCE_DIR}/dependencies.cmake")
include("${PROJECT_SOURCE_DIR}/assets.cmake")

add_subdirectory(src bin)

