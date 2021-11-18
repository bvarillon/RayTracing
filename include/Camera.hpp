#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

class Camera {
    public:
        Camera(double aspect_ratio)
        {
            auto viewport_heigth = 2.0;
            auto viewport_width = viewport_heigth * aspect_ratio;
            auto focal_length = 1.0;

            origin = Point3(0,0,0);
            horizontal = Vec3(viewport_width,0,0);
            vertical = Vec3(0,viewport_heigth,0);
            lower_left_corner = origin - horizontal/2 - vertical/2 - Vec3(0, 0, focal_length);
        }

        Ray get_ray(double u, double v) const;
    
    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
};

#endif