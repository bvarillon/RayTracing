#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Ray.hpp"
#include "Hittable.hpp"
#include "Color.hpp"
#include "Vec3.hpp"

class Material
{
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const = 0;

};

class Lanbertian : public Material
{
    public:
        Lanbertian(const Color& a): albedo(a){}

        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override
        {
            auto scatter_direction = rec.normal + Vec3::random_in_unit_vector();
            if(scatter_direction.near_zero())
                scatter_direction = rec.normal;
            scattered = Ray(rec.p, scatter_direction);
            attenuation = albedo;
            return true;
        }

    private:
        Color albedo;
};

class Metal : public Material
{
    public:
        Metal(const Color& a, double roughtness) : albedo(a), rough(roughtness) {}

        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override
        {
            Vec3 reflected = r_in.direction() - 2 * dot(r_in.direction(),rec.normal) * rec.normal;
            scattered = Ray(rec.p,reflected + rough * Vec3::random_in_unit_sphere());
            attenuation = albedo;
            // return true;
            return dot(reflected, rec.normal)>0;
        }

    private:
        Color albedo;
        double rough;
};

#endif