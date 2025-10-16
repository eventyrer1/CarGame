# inspired from https://github.com/jonakselm/ais1003-prosjekt/blob/master/tests/CMakeLists.txt

add_executable(tests collisionTest.cpp)

target_link_libraries(tests
        PRIVATE Catch2::Catch2WithMain
        PUBLIC libBoard
)

add_test(NAME tests COMMAND tests)
