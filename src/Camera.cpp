#include "Camera.hpp"

Ray Camera::get_ray(double s, double t) const
{
    Vec3 rd = lens_radius * Vec3::random_in_unit_disk();
    auto offset = u*rd.x() + v*rd.y();

    return Ray(origin+offset, lower_left_corner + s*horizontal + t*vertical - origin - offset);
}