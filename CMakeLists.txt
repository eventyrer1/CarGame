
cmake_minimum_required(VERSION 4.0)

# ----------------------------------------------------------
# vcpkg auto-init section (Done by AI)
# ----------------------------------------------------------
if (NOT EXISTS "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    message(STATUS "Initializing vcpkg submodule…")
    execute_process(
            COMMAND git submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    )
endif()

set(CMAKE_TOOLCHAIN_FILE
        "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "" FORCE
)
# ----------------------------------------------------------

project(CarGame)
set(CMAKE_CXX_STANDARD 20)
enable_testing()

# Define DATA_DIR once globally before any targets
set(DATA_DIR "${CMAKE_SOURCE_DIR}/Data")
add_compile_definitions(DATA_DIR="${DATA_DIR}")

# Copy data assets next to runtime output (CarGame executable resides under src build dir)
file(COPY ${CMAKE_SOURCE_DIR}/Data/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/src/)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)

# External deps
set(THREEPP_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(THREEPP_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 49d9d222494431060b1571cf12352154eb4ac417
)
FetchContent_MakeAvailable(threepp)


set(ASSIMP_IGNORE_DIsR_IN_ZIP TRUE)
set(ASSIMP_BUILD_ZLIB OFF)
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

# Internal libraries ordering (dependency aware)
add_subdirectory(libs)          # imgui
add_subdirectory(src/collision) # collision base used by models
add_subdirectory(src/models)    # models depends on collision
add_subdirectory(src/keyListeners)
add_subdirectory(src/setups)    # setups depends on models/imgui
add_subdirectory(src)           # executable depends on all libs
add_subdirectory(tests)         # test targets
