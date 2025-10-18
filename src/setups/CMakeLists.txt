

set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(setups_files
        "${setups_include_dir}/setup.hpp" "setup.cpp"
        "${setups_include_dir}/TreeManager.hpp" "TreeManager.cpp"
)
add_library(setups ${setups_files})

target_link_libraries(setups PUBLIC threepp::threepp
        assimp::assimp
        models)
target_include_directories(setups PUBLIC ${setups_include_dir})