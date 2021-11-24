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

Vec3 reflect(const Vec3& u, const Vec3& n)
{
    return u - 2* dot(u,n) * n;
}

double reflectance(double cos, double ratio)
{
    auto r0 = (1-ratio) / (1+ratio);
    r0 *= r0;
    return r0 + (1-r0)*pow(1-cos,5);
}
Vec3 refract(const Vec3& u, const Vec3& n, double ratio)
{
    auto cos_theta = fmin(dot(-u,n),1.0);
    auto sin_theta = std::sqrt(1.0- cos_theta*cos_theta);

    if (ratio * sin_theta > 1.0 || reflectance(cos_theta, ratio) > random_double())
        return reflect(u,n);

    auto r_out_perp = ratio * (u + cos_theta * n);
    auto r_out_par = - std::sqrt(fabs(1-r_out_perp.length_squarred())) * n;

    return r_out_par + r_out_perp;
}

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
            Vec3 reflected = reflect(r_in.direction(),rec.normal);
            scattered = Ray(rec.p,reflected + rough * Vec3::random_in_unit_sphere());
            attenuation = albedo;
            // return true;
            return dot(reflected, rec.normal)>0;
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
            auto refracted = refract(unit_dir, rec.normal, refraction_ratio);

            scattered = Ray(rec.p, refracted);
            return true;
        }

    private:
        double ir;
};

#endif