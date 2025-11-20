set(DATA_DIR "${CMAKE_SOURCE_DIR}/Data")
set(setups_include_dir "${CMAKE_SOURCE_DIR}/include/setups")

set(setups_files
        "${setups_include_dir}/Setup.hpp" "Setup.cpp"
        "${setups_include_dir}/ObjectSpawner.hpp"
        "UiManager.cpp"
        "${setups_include_dir}/HumanDetector.hpp" "HumanDetector.cpp"
)
add_library(setups ${setups_files})

target_link_libraries(setups PUBLIC threepp::threepp
        assimp::assimp
        models
        imgui::imgui
        opencv::opencv
)

target_include_directories(setups PUBLIC ${setups_include_dir})
target_compile_definitions(setups PUBLIC DATA_DIR="${DATA_DIR}")
