#ifndef RAY_HPP
#define RAY_HPP

#include "Point3.hpp"
#include "Vec3.hpp"

class Ray {
    public:
        Ray(){}
        Ray(const Point3& origine, const Vec3& direction)
        : orig(origine), dir(direction)
        {}

        Point3 origin() const { return orig; }
        Vec3 direction() const { return dir; }

        Point3 at(double t) const { return orig + t*dir; }

    private:
        Point3 orig;
        Vec3 dir;
};

#endif