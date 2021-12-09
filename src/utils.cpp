#include "utils.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <random>

double degrees_to_radians(double degrees)
{
    return degrees * M_PI / 180.0;
}

double random_double()
{
    static std::random_device rd;
    static std::mt19937  gen(rd());
    static std::uniform_real_distribution<> dis(0.0,1.0);

    return dis(gen);
}
double random_double(double min, double max)
{
    static std::random_device rd;
    static std::mt19937  gen(rd());
    static std::uniform_real_distribution<> dis(min, max);

    return dis(gen);
}

double clamp(double x, double min, double max)
{
    if(x<min){return min;}
    else if (x>max){return max;}
    return x;
}