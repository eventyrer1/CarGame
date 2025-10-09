cmake_minimum_required(VERSION 4.0)
project(CarGame)
set(CMAKE_CXX_STANDARD 20)

file(COPY ${CMAKE_SOURCE_DIR}/data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

# threepp
set(THREEPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(THREEPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 49d9d222494431060b1571cf12352154eb4ac417
)
FetchContent_MakeAvailable(threepp)

# Assimp (fetched and built as part of the configure step)
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        assimp
        GIT_REPOSITORY https://github.com/assimp/assimp.git
        GIT_TAG v5.2.5
)


FetchContent_MakeAvailable(assimp)


add_subdirectory(src)
#add_subdirectory(tests)
