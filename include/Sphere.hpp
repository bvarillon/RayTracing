#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point3.hpp"
#include "Hittable.hpp"
#include "Vec3.hpp"

class Sphere : public Hittable
{
    public:
        Sphere(Point3 cen, double r)
        : center(cen), radius(r)
        {}

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    private:
        Point3 center;
        double radius;
};

#endif