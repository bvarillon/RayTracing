#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

class Vec3 {
    public:
        Vec3(): e{0,0,0}{}
        Vec3(double e0, double e1, double e2): e{e0,e1,e2}{}

        double x() const {return e[0];}
        double y() const {return e[1];}
        double z() const {return e[2];}

        double operator[](int i) const {return e[i];}
        double& operator[](int i) {return e[i];}

        Vec3 operator-() const;
        Vec3& operator+=(const Vec3 &v);
        Vec3& operator*=(const double t);
        Vec3& operator/=(const double t);

        bool near_zero() const;

        double length() const;
        double length_squarred() const;

    //----------------------------------------------------------------------

        Vec3 static random();
        Vec3 static random(double min, double max);
        Vec3 static random_in_unit_sphere();
        Vec3 static random_unit_vector();
        Vec3 static random_in_unit_disk();

    private:
        double e[3];

};

std::ostream& operator<<(std::ostream &out, const Vec3 &v);
Vec3 operator+(const Vec3& u, const Vec3& v);
Vec3 operator-(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, const Vec3& v);
Vec3 operator*(const Vec3& u, double t);
Vec3 operator*(double t, const Vec3& u);
Vec3 operator/(const Vec3& u, double t);

double dot(const Vec3& u, const Vec3& v);
Vec3 cross(const Vec3& u, const Vec3& v);
Vec3 unit_vector(Vec3 v);


#endif