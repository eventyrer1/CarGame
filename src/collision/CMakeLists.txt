set(collision_include_dir "${CMAKE_SOURCE_DIR}/include/collision")

set(collision_files
        "${collision_include_dir}/Collidable.hpp"
        "${collision_include_dir}/CollisionManager.hpp" "CollisionManager.cpp"
)

add_library(collision ${collision_files})

target_link_libraries(collision PUBLIC threepp::threepp)
target_include_directories(collision PUBLIC ${collision_include_dir})
