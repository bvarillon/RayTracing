#include "Camera.hpp"

Ray Camera::get_ray(double u, double v) const
{
    return Ray(origin, lower_left_corner + u*horizontal + v*vertical - origin);
}