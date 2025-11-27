
set(CMAKE_DEBUG_POSTFIX "")  #have to add this beacuse if not then visual studio adds a d at the end of the lib name

set(MODELS_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MODELS_INC_DIR "${CMAKE_SOURCE_DIR}/include/models")
set(SETUPS_INC_DIR "${CMAKE_SOURCE_DIR}/include/setups")

set(models_src_files
        "${MODELS_SRC_DIR}/Car.cpp"
        "${MODELS_SRC_DIR}/Tree.cpp"
        "${MODELS_SRC_DIR}/SpawnableObject.cpp"
        "${MODELS_SRC_DIR}/Human.cpp"
        "${MODELS_SRC_DIR}/Stone.cpp"

        "${MODELS_INC_DIR}/Stone.hpp"
        "${MODELS_INC_DIR}/Car.hpp"
        "${MODELS_INC_DIR}/Tree.hpp"
        "${MODELS_INC_DIR}/SpawnableObject.hpp"
        "${MODELS_INC_DIR}/Human.hpp"
)

add_library(models ${models_src_files})

find_package(OpenCV REQUIRED)

target_link_libraries(models PUBLIC
        threepp::threepp
        assimp::assimp
        collision
        ${OpenCV_LIBS}
)

target_include_directories(models PUBLIC
        ${MODELS_INC_DIR}
        ${SETUPS_INC_DIR}
)
