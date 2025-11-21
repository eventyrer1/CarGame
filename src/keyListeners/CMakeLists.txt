

set(keyListener_include_dir "${CMAKE_SOURCE_DIR}/include/keyListeners")

set(keyListener_files
        "${keyListener_include_dir}/CarKeyListener.hpp" "CarKeyListener.cpp"
        "${keyListener_include_dir}/InterfaceCarKeyListener.hpp"

)
add_library(keyListeners ${keyListener_files})

find_package(OpenCV REQUIRED)

target_link_libraries(keyListeners PUBLIC
        threepp::threepp
        ${OpenCV_LIBS})
target_include_directories(keyListeners PUBLIC ${keyListener_include_dir})