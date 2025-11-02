

set(keylistener_include_dir "${CMAKE_SOURCE_DIR}/include/keylisteners")

set(keylistener_files
        "${keylistener_include_dir}/CarKeyListener.hpp" "CarKeylistener.cpp"
        "${keylistener_include_dir}/WorldKeyListener.hpp" "WorldKeylistener.cpp"
        "${keylistener_include_dir}/InterfaceCarKeyListener.hpp"
        "${keylistener_include_dir}/CarActions.hpp"
)
add_library(keylisteners ${keylistener_files})

target_link_libraries(keylisteners PUBLIC threepp::threepp)
target_include_directories(keylisteners PUBLIC ${keylistener_include_dir})