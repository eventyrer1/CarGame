set(CMAKE_DEBUG_POSTFIX "")  #have to add this beacuse if not then visual studio adds a d at the end of the lib name

set(SETUPS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SETUPS_INC_DIR "${CMAKE_SOURCE_DIR}/include/setups")

set(setups_files
        "${SETUPS_SRC_DIR}/Setup.cpp"
        "${SETUPS_SRC_DIR}/UiManager.cpp"
        "${SETUPS_SRC_DIR}/HumanDetector.cpp"

        "${SETUPS_INC_DIR}/Setup.hpp"
        "${SETUPS_INC_DIR}/ObjectSpawner.hpp"
        "${SETUPS_INC_DIR}/UiManager.hpp"
        "${SETUPS_INC_DIR}/HumanDetector.hpp"
)

add_library(setups ${setups_files})

find_package(OpenCV REQUIRED)

target_link_libraries(setups PUBLIC
        threepp::threepp
        assimp::assimp
        imgui::imgui
        models

        ${OpenCV_LIBS}
)

target_include_directories(setups PUBLIC
        ${SETUPS_INC_DIR}
)
