cmake_minimum_required(VERSION 4.0)
project(threepp_fetchcontent_demo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin")

include(FetchContent)

set(THREEPP_BUILD_TESTS OFF)
set(THREEPP_BUILD_EXAMPLES OFF)
FetchContent_Declare(
        threepp
        GIT_REPOSITORY https://github.com/markaren/threepp.git
        GIT_TAG 49d9d222494431060b1571cf12352154eb4ac417
)
FetchContent_MakeAvailable(threepp)

add_executable(main main.cpp
        Tank.hpp)
target_link_libraries(main PRIVATE threepp::threepp)

