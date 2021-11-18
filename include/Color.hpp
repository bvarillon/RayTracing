#ifndef COLOR_HPP
#define COLOR_HPP

#include <iostream>

#include "Vec3.hpp"

using Color = Vec3;

void write_color(std::ostream &out, const Color& color, int samples);

#endif