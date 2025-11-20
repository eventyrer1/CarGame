#Taken from threepp examples
add_library(imgui)
add_library(imgui::imgui ALIAS imgui)
target_sources(imgui PRIVATE
        "imgui/imgui.cpp"
        "imgui/imgui_draw.cpp"
        "imgui/imgui_impl_glfw.cpp"
        "imgui/imgui_impl_opengl3.cpp"
        "imgui/imgui_tables.cpp"
        "imgui/imgui_widgets.cpp"
        "imgui/imgui_demo.cpp"
)
target_link_libraries(imgui PRIVATE glfw)
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

add_library(bvh)
add_library(bvh::bvh ALIAS bvh)
target_sources(bvh PRIVATE
        "bvh/BVH.cpp"
        "bvh/BVH.hpp"
)
target_link_libraries(bvh PRIVATE threepp)
target_include_directories(bvh PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/bvh")

#[[
add_library(opencv SHARED IMPORTED )
add_library(opencv::opencv ALIAS opencv)

set_target_properties(opencv PROPERTIES
        IMPORTED_IMPLIB_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/openCV/opencv_world4120.lib"
        IMPORTED_LOCATION_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/openCV/opencv_world4120.dll"

        IMPORTED_IMPLIB_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/openCV/opencv_world4120d.lib"
        IMPORTED_LOCATION_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/openCV/opencv_world4120d.dll"

        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/opencv/include"
)
]]
