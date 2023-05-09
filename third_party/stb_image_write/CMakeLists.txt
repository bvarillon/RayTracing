cmake_minimum_required(VERSION 3.1.0)
project(StbImageWrite VERSION 0.1.0)

set(SRC stb_image_write.cpp)
set(HDR stb_image_write.hpp)

add_library(StbImageWrite ${SRC})
target_include_directories(StbImageWrite PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})