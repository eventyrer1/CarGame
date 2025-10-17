#inspirert av https://github.com/Joranikus/Asteroids/blob/master/src/game_systems/CMakeLists.txt
set(models_include_dir "${CMAKE_SOURCE_DIR}/include/models")
set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(models_src_files
        "${models_include_dir}/Car.hpp" "${CMAKE_SOURCE_DIR}/src/models/Car.cpp"
        "${models_include_dir}/Tree.hpp" "${CMAKE_SOURCE_DIR}/src/models/Tree.cpp"
)

add_library(models ${models_src_files})

target_link_libraries(models PUBLIC threepp::threepp assimp::assimp)

# Include both models and setups directories
target_include_directories(models PUBLIC
        ${models_include_dir}
        ${setups_include_dir}
)

target_compile_definitions(models PUBLIC DATA_DIR="${CMAKE_SOURCE_DIR}/data")
