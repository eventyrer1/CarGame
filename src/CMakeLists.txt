add_executable(CarGame main.cpp)
target_include_directories(CarGame PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(CarGame PRIVATE
        threepp::threepp
        assimp::assimp)


add_subdirectory(models)