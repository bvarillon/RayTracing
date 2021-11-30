cmake_minimum_required(VERSION 3.0.0)
project(RayTracing VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(include)
add_executable(RayTracing src/main.cpp
                          src/vec3.cpp
                          src/Sphere.cpp
                          src/HittableList.cpp
                          src/Camera.cpp
                          src/utils.cpp
                          src/Color.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)