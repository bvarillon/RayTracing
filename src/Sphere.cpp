#include "Sphere.hpp"

#include <cmath>

bool Sphere::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    Vec3 oc = r.origin() - center;
    auto a = r.direction().length_squarred();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squarred() - radius*radius;

    auto delta = (half_b*half_b) - (a*c);
    if(delta < 0) return false;

    auto sqrtd = std::sqrt(delta);
    auto root = (-half_b-sqrtd) / a;
    if(root < t_min || root > t_max)
    {
        root = (-half_b+sqrtd) / a;
        if(root < t_min || root > t_max)
        {
            return false;
        }
    }

    rec.t = root;
    rec.p = r.at(root);
    rec.set_face_normal(r, (rec.p - center) / radius);
    rec.mat_ptr = mat_ptr;

    return true;
}