#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "Point3.hpp"
#include "Hittable.hpp"
#include "Vec3.hpp"

class Material;

class Sphere : public Hittable
{
    public:
        Sphere(Point3 cen, double r, std::shared_ptr<Material> material)
        : center(cen), radius(r), mat_ptr(material)
        {}

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;

    private:
        Point3 center;
        double radius;
        std::shared_ptr<Material> mat_ptr;
};

#endif