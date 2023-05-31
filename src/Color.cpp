#include "Color.hpp"

#include <cmath>
#include <string>

#include "utils.hpp"
#include "stb_image_write.hpp"

void write_color(std::ostream &out, const Color& color)
{
    auto r = color.x();
    auto g = color.y();
    auto b = color.z();

    r = std::sqrt(r);
    g = std::sqrt(g);
    b = std::sqrt(b);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << ' '
        << std::endl;

}

void write_image(std::ostream &out, const Color img[] , int width, int height)
{
    std::cerr << "Writing img" << std::endl;
    out << "P3" << std::endl
        << width << ' ' << height << std::endl
        << "255" << std::endl;
        for(int i=0; i<width*height; i++)
        {
            write_color(out, img[i]);
        }

}

/** Convert a Color to an array on three byte [R,G,B]
 * 
 * @param[in] pixel Color to convert
 * @param[out] tab pointer to the first byte to store the result.
*/
void color2char(Color const &pixel, char* tab)
{
    auto r = pixel.x();
    auto g = pixel.y();
    auto b = pixel.z();

    r = std::sqrt(r);
    g = std::sqrt(g);
    b = std::sqrt(b);

    char R = static_cast<int>(256 * clamp(r, 0.0, 0.999));
    char G = static_cast<int>(256 * clamp(g, 0.0, 0.999));
    char B = static_cast<int>(256 * clamp(b, 0.0, 0.999));

    tab[0] = R;
    tab[1] = G;
    tab[2] = B;
}
/** Write an image to a file.
 * 
 * @param img image to store as an array of Color, img[0] is the upper left pixel.
 * @param width width of the image.
 * @param height height of the image.
 * @param file_name name of the file to store the image
*/
void write_image_to_file(Color const img[] , int const width, int const height, const std::string file_name)
{
    size_t const length = width * height * 3;

    char* image = new char[length];

    for(size_t i=0; i<width*height; i++)
    {
        color2char(img[i], &image[i*3]);
    }
    stbi_write_jpg(file_name.c_str(),width, height, 3, image, 100);
}