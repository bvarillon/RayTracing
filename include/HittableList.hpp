#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include "Hittable.hpp"

#include <memory>
#include <vector>

using std::shared_ptr;

class HittableList : public Hittable
{
    public:
        HittableList(){}

        void clear() { objects.clear(); }
        void add(shared_ptr<Hittable> obj) { objects.push_back(obj); }

        virtual bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const override;
    
    private:
        std::vector<shared_ptr<Hittable>> objects;
};
#endif