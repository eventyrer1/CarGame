set(DATA_DIR "${CMAKE_SOURCE_DIR}/Data")
target_compile_definitions(CarGame PRIVATE DATA_DIR="${DATA_DIR}")

set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(setups_files
        "${setups_include_dir}/Setup.hpp" "Setup.cpp"
        "${setups_include_dir}/TreeManager.hpp" "TreeManager.cpp"
        "UiManager.cpp"
)
add_library(setups ${setups_files})

target_link_libraries(setups PUBLIC threepp::threepp
        assimp::assimp
        models
        imgui::imgui)
target_include_directories(setups PUBLIC ${setups_include_dir})