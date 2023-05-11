cmake_minimum_required(VERSION 3.1.0)
project(Nlohmann VERSION 0.1.0)

add_library(Nlohmann INTERFACE)
target_include_directories(StbImageWrite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)