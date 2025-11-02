

set(keyListener_incLude_dir "${CMAKE_SOURCE_DIR}/include/keyListeners")

set(keyListener_files
        "${keyListener_include_dir}/CarKeyListener.hpp" "CarKeyListener.cpp"
        "${keyListener_include_dir}/WorldKeyListener.hpp" "WorldKeyListener.cpp"
        "${keyListener_include_dir}/InterfaceCarKeyListener.hpp"
        "${keyListener_include_dir}/CarActions.hpp"
)
add_library(keyListeners ${keyListener_files})

target_link_libraries(keyListeners PUBLIC threepp::threepp)
target_include_directories(keyListeners PUBLIC ${keyListener_include_dir})