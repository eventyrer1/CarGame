
set(CMAKE_DEBUG_POSTFIX "")  #have to add this beacuse if not then visual studio adds a d at the end of the lib name


set(KEYLISTENERS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(KEYLISTENERS_INC_DIR "${CMAKE_SOURCE_DIR}/include/keyListeners")

set(keyListener_files
        "${KEYLISTENERS_SRC_DIR}/CarKeyListener.cpp"

        "${KEYLISTENERS_INC_DIR}/CarKeyListener.hpp"
        "${KEYLISTENERS_INC_DIR}/InterfaceCarKeyListener.hpp"
)

add_library(keyListeners ${keyListener_files})

find_package(OpenCV REQUIRED)

target_link_libraries(keyListeners PUBLIC
        threepp::threepp
        ${OpenCV_LIBS}
)

target_include_directories(keyListeners PUBLIC
        ${KEYLISTENERS_INC_DIR}
)
