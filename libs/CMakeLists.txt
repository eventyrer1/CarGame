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