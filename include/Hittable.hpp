#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "Point3.hpp"
#include "Vec3.hpp"
#include "Ray.hpp"

struct hit_record{
    Point3 p;
    Vec3 normal;
    double t;
    bool front_face;

    inline void set_face_normal(const Ray& r, const Vec3& outward_normal)
    {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
    public:
        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};


#endif