#include "Material.hpp"

#include <cmath>

Vec3 reflect(const Vec3& u, const Vec3& n)
{
    return u - 2* dot(u,n) * n;
}

double reflectance(double cos, double ratio)
{
    auto r0 = (1-ratio) / (1+ratio);
    r0 = r0*r0;
    return r0 + (1-r0)*pow(1-cos,5);
}
Vec3 refract(const Vec3& u, const Vec3& n, double ratio)
{
    auto cos_theta = fmin(dot(-u,n),1.0);

    auto r_out_perp = ratio * (u + cos_theta * n);
    auto r_out_par = - std::sqrt(fabs(1-r_out_perp.length_squarred())) * n;

    return r_out_par + r_out_perp;
}