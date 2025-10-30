add_executable(tests Acceleration.cpp)

target_include_directories(tests PRIVATE ${CMAKE_SOURCE_DIR}/include)


target_link_libraries(tests
        PRIVATE
        Catch2::Catch2WithMain
        threepp::threepp
        assimp::assimp
        models
        keylisteners
        setups
        collision
)

# Enable CTest + Catch2 integration
include(CTest)
include(Catch)
catch_discover_tests(tests)
