
set(CMAKE_DEBUG_POSTFIX "")  #have to add this beacuse if not then visual studio adds a d at the end of the lib name

set(COLLISION_SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(COLLISION_INC_DIR "${CMAKE_SOURCE_DIR}/include/collision")

set(collision_files
        "${COLLISION_SRC_DIR}/CollisionManager.cpp"

        "${COLLISION_INC_DIR}/Collidable.hpp"
        "${COLLISION_INC_DIR}/CollisionManager.hpp"
)

add_library(collision ${collision_files})

target_link_libraries(collision PUBLIC
        threepp::threepp
)

target_include_directories(collision PUBLIC
        ${COLLISION_INC_DIR}
)
