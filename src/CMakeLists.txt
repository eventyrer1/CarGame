
add_executable(CarGame main.cpp)
# Automatically copy OpenCV DLLs to the output folder
#this was done by chatgpt and honestly scares me a little



target_include_directories(CarGame PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(CarGame PRIVATE
        threepp::threepp
        assimp::assimp
        models
        keyListeners
        setups
        collision
        imgui::imgui


)


add_subdirectory(models)
add_subdirectory(keyListeners)
add_subdirectory(setups)
add_subdirectory(collision)


