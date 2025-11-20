
add_executable(CarGame main.cpp)
# Automatically copy OpenCV DLLs to the output folder
#this was done by chatgpt and honestly scares me a little
add_custom_command(TARGET CarGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/opencv/opencv_world4120d.dll"
        "$<TARGET_FILE_DIR:CarGame>"
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/opencv/opencv_world4120.dll"
        "$<TARGET_FILE_DIR:CarGame>"
)


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


