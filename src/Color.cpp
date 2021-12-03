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

void write_image(std::ostream &out, const Color img[] , int width, int height, int samples)
{
    std::cerr << "Writing img" << std::endl;
    out << "P3" << std::endl
        << width << ' ' << height << std::endl
        << "255" << std::endl;
        for(int i=0; i<width*height; i++)
        {
            write_color(out, img[i], samples);
        }
}