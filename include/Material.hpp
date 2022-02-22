#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <cmath>

#include "Ray.hpp"
#include "Hittable.hpp"
#include "Color.hpp"
#include "Vec3.hpp"
#include "utils.hpp"

class Material
{
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const = 0;

};

Vec3 reflect(const Vec3& u, const Vec3& n);
double reflectance(double cos, double ratio);
Vec3 refract(const Vec3& u, const Vec3& n, double ratio);

class Lambertian : public Material
{
    public:
        Lambertian(const Color& a): albedo(a){}

        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override
        {
            auto scatter_direction = rec.normal + Vec3::random_unit_vector();
            // auto scatter_direction = rec.normal + Vec3::random_in_unit_sphere();
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
            Vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
            scattered = Ray(rec.p,reflected + rough * Vec3::random_in_unit_sphere());
            attenuation = albedo;
            // return true;
            return dot(scattered.direction(), rec.normal)>0;
        }

    private:
        Color albedo;
        double rough;
};

class Dielectric : public Material
{
    public:
        Dielectric(double refraction_index) : ir(refraction_index){}

        virtual bool scatter(const Ray& r_in, const hit_record& rec, Color& attenuation, Ray& scattered) const override
        {
            attenuation = Color(1,1,1);
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

            auto unit_dir = unit_vector(r_in.direction());
            double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vec3 direction;
            if(cannot_refract || reflectance(cos_theta, refraction_ratio)>random_double())
                direction = reflect(unit_dir, rec.normal);
            else
                direction = refract(unit_dir, rec.normal, refraction_ratio);

            scattered = Ray(rec.p, direction);
            return true;
        }

    private:
        double ir;
};

#endif