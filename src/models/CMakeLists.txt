#inspirert av https://github.com/Joranikus/Asteroids/blob/master/src/game_systems/CMakeLists.txt
set(models_include_dir "${CMAKE_SOURCE_DIR}/include/models")
set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(models_src_files
        "${models_include_dir}/CarVisual.hpp" "CarVisual.cpp"
        "${models_include_dir}/CarLogic.hpp" "CarLogic.cpp"
        "${models_include_dir}/Tree.hpp" "Tree.cpp"
        "${models_include_dir}/SpawnableObject.hpp" "SpawnableObject.cpp"


)

add_library(models ${models_src_files})

target_link_libraries(models PUBLIC 
        threepp::threepp
        assimp::assimp
        collision
)

# Include both models and setups directories
target_include_directories(models PUBLIC
        ${models_include_dir}
        ${setups_include_dir}
)
