#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <cmath>

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"
#include "utils.hpp"

class Camera {
    public:
        Camera(Point3 lookfrom, Point3 lookat, Vec3 vup,
               double vfov, double aspect_ratio,
               double aperture, double focus_dist)
        {
            auto theta = degrees_to_radians(vfov);
            auto h = tan(theta/2);
            auto viewport_heigth = 2.0 * h;
            auto viewport_width = viewport_heigth * aspect_ratio;

            w = unit_vector(lookfrom-lookat);
            u = unit_vector(cross(vup,w));
            v = cross(w,u);

            origin = lookfrom;
            horizontal = focus_dist * viewport_width * u;
            vertical = focus_dist * viewport_heigth * v;
            lower_left_corner = origin - horizontal/2 - vertical/2 - focus_dist*w;

            lens_radius = aperture /2;
        }

        Ray get_ray(double s, double t) const;
    
    private:
        Point3 origin;
        Point3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u,v,w;
        double lens_radius;
};

#endif