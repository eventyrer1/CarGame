#inspirert av https://github.com/Joranikus/Asteroids/blob/master/src/game_systems/CMakeLists.txt
set(models_include_dir "${CMAKE_SOURCE_DIR}/include/models")
set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(models_src_files
        "${models_include_dir}/Car.hpp" "Car.cpp"
        "${models_include_dir}/Tree.hpp" "Tree.cpp"
        "${models_include_dir}/SpawnableObject.hpp" "SpawnableObject.cpp"
        "${models_include_dir}/Human.hpp" "Human.cpp"

)

add_library(models ${models_src_files})

find_package(OpenCV REQUIRED)

target_link_libraries(models PUBLIC 
        threepp::threepp
        assimp::assimp
        collision
        ${OpenCV_LIBS}
)

# Include both models and setups directories
target_include_directories(models PUBLIC
        ${models_include_dir}
        ${setups_include_dir}
)
