#include "Color.hpp"

#include <cmath>

void write_color(std::ostream &out, const Color& color, int samples)
{
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();

    r = std::sqrt(r / samples);
    g = std::sqrt(g / samples);
    b = std::sqrt(b / samples);

    out << static_cast<int>(255.999*r) << ' '
        << static_cast<int>(255.999*g) << ' '
        << static_cast<int>(255.999*b) << ' '
        << std::endl;
}