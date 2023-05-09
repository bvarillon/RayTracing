#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "Vec3.hpp"

using Color = Vec3;

void write_color(std::ostream &out, const Color& color);
void write_image(std::ostream &out, const Color[], int width, int height);
void write_image_to_file(Color const img[] , int const width, int const height, char const file_name[]);

#endif