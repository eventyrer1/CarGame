

set(keyListener_include_dir "${CMAKE_SOURCE_DIR}/include/keyListeners")

set(keyListener_files
        "${keyListener_include_dir}/CarKeyListener.hpp" "CarKeyListener.cpp"
        "${keyListener_include_dir}/InterfaceCarKeyListener.hpp"

)
add_library(keyListeners ${keyListener_files})

target_link_libraries(keyListeners PUBLIC
        threepp::threepp
        opencv::opencv)
target_include_directories(keyListeners PUBLIC ${keyListener_include_dir})