#include "Vec3.hpp"

#include <cmath>
#include <iostream>

#include "utils.hpp"

Vec3 Vec3::operator-() const 
{   
    return Vec3(-e[0], -e[1],-e[2]);
}

Vec3& Vec3::operator+=(const Vec3 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];

    return *this;
}

Vec3& Vec3::operator*=(const double t)
{
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;

    return *this;
}

Vec3& Vec3::operator/=(const double t)
{
    return *this *= 1/t;
}

double Vec3::length() const
{
    return std::sqrt(length_squarred());
}

double Vec3::length_squarred() const
{
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
}


std::ostream& operator<<(std::ostream &out, const Vec3 &v)
{
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

Vec3 operator+(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x()+v.x(), u.y()+v.y(), u.z()+v.z());
}
Vec3 operator-(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x()-v.x(), u.y()-v.y(), u.z()-v.z());
}
Vec3 operator*(const Vec3& u, const Vec3& v)
{
    return Vec3(u.x()*v.x(), u.y()*v.y(), u.z()*v.z());
}
Vec3 operator*(const Vec3& u, double t)
{
    return Vec3(t*u.x(), t*u.y(), t*u.z());
}
Vec3 operator*(double t, const Vec3& u)
{
    return u*t;
}
Vec3 operator/(const Vec3& u, double t)
{
    return u*(1/t);
}

double dot(const Vec3& u, const Vec3& v)
{
    return u.x()*v.x() + u.y()*v.y() + u.z()*v.z();
}
Vec3 cross(const Vec3& u, const Vec3& v)
{
    return Vec3(u.y()*v.z() - u.z()*v.y(),
                u.z()*v.x() - u.x()*v.z(),
                u.x()*v.y() - u.y()*v.x());
}
Vec3 unit_vector(Vec3 v)
{
    return v/v.length();
}

//----------------------------------------------------------------------
// Static functions 

Vec3 Vec3::random()
{
    return Vec3(random_double(), random_double(), random_double());
}
Vec3 Vec3::random(double min, double max)
{
    return Vec3(random_double(min,max),random_double(min,max),random_double(min,max));
}
Vec3 Vec3::random_in_unit_sphere()
{
    while(true)
    {
        auto p = Vec3::random(-1,1);
        if(p.length() >= 1) continue;
        return p;
    }
}
Vec3 Vec3::random_in_unit_vector()
{
    return unit_vector(random_in_unit_sphere());
}