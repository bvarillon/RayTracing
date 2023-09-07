cmake_minimum_required(VERSION 3.1.0)
project(RayTracing VERSION 0.0.1)


add_subdirectory(third_party/stb_image_write)
add_subdirectory(third_party/nlohmann)
add_subdirectory(third_party/cxxopts)

configure_file(include/Version.hpp.in Version.hpp)

include_directories(include "${PROJECT_BINARY_DIR}")
add_executable(RayTracing src/main.cpp
                          src/vec3.cpp
                          src/Sphere.cpp
                          src/HittableList.cpp
                          src/Camera.cpp
                          src/utils.cpp
                          src/Color.cpp
                          src/Material.cpp
                          src/Renderer.cpp
                          src/Arguments.cpp)
if(UNIX)
target_link_libraries(RayTracing pthread)
endif(UNIX)

target_link_libraries(RayTracing StbImageWrite Nlohmann cxxopts)

set_target_properties(RayTracing PROPERTIES DEBUG_POSTFIX d)

install(TARGETS RayTracing
        DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)
