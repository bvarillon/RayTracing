#include "HittableList.hpp"

bool HittableList::hit(const Ray& r, double t_min, double t_max, hit_record& rec) const
{
    bool hit_anything = false;
    auto closest_so_far= t_max;
    hit_record temp_rec;

    for(const auto& object : objects){
        if(object->hit(r, t_min,closest_so_far, temp_rec)){
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }
    return hit_anything;
}