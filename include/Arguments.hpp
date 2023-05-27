#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <string>

struct Arguments
{
    bool verbose;
    std::string filename;

    int img_width;
    int img_height;
    int samples;
    int max_depth;
    double aspect_ratio;
    int size;
};

Arguments pars_args(int argc, char* argv[]);

#endif