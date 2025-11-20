cmake_minimum_required(VERSION 4.0)
project(CarGame)
set(CMAKE_CXX_STANDARD 20)
enable_testing()

file(COPY ${CMAKE_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

# dont need tests and examples so i dont fetch them
set(THREEPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(THREEPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 49d9d222494431060b1571cf12352154eb4ac417
)
FetchContent_MakeAvailable(threepp)


set(ASSIMP_BUILD_ZLIB OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.2.5
)
FetchContent_MakeAvailable(assimp)


FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.11.0
)
FetchContent_MakeAvailable(catch2)


#This was suggested by chaGPT
# -----------------------------------------
# OpenCV import (put this before src/libs)
# -----------------------------------------
add_library(opencv SHARED IMPORTED)
add_library(opencv::opencv ALIAS opencv)

set(OPENCV_ROOT "${CMAKE_SOURCE_DIR}/libs/opencv")

set_target_properties(opencv PROPERTIES
        IMPORTED_IMPLIB_RELEASE "${OPENCV_ROOT}/opencv_world4120.lib"
        IMPORTED_LOCATION_RELEASE "${OPENCV_ROOT}/opencv_world4120.dll"

        IMPORTED_IMPLIB_DEBUG "${OPENCV_ROOT}/opencv_world4120d.lib"
        IMPORTED_LOCATION_DEBUG "${OPENCV_ROOT}/opencv_world4120d.dll"

        INTERFACE_INCLUDE_DIRECTORIES "${OPENCV_ROOT}/include"
)

add_subdirectory(libs)
add_subdirectory(src)
add_subdirectory(tests)
set(DATA_DIR "${CMAKE_SOURCE_DIR}/Data")

target_compile_definitions(CarGame PRIVATE DATA_DIR="${DATA_DIR}")