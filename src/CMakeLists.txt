# Collect all cpp files in src
file(GLOB SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# main is in root so add it manually
set(MAIN_FILE "${CMAKE_SOURCE_DIR}/main.cpp")

add_executable(CarGame
        ${MAIN_FILE}
        ${SRC_FILES}
)

target_include_directories(CarGame PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
)

find_package(OpenCV REQUIRED)

target_link_libraries(CarGame PRIVATE
        threepp::threepp
        assimp::assimp
        imgui::imgui
        models
        keyListeners
        setups
        collision
        ${OpenCV_LIBS}
)
