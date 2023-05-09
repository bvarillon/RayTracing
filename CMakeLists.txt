cmake_minimum_required(VERSION 3.1.0)
project(RayTracing VERSION 0.1.0)


add_subdirectory(third_party)

include_directories(include)
add_executable(RayTracing src/main.cpp
                          src/vec3.cpp
                          src/Sphere.cpp
                          src/HittableList.cpp
                          src/Camera.cpp
                          src/utils.cpp
                          src/Color.cpp
                          src/Material.cpp
                          src/Renderer.cpp)
if(UNIX)
target_link_libraries(RayTracing pthread)
endif(UNIX)

# target_link_libraries(RayTracing ThirdParty)
target_link_libraries(RayTracing StbImageWrite)

install(TARGETS RayTracing
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
