#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <future>

#include "Camera.hpp"
#include "HittableList.hpp"
#include "Color.hpp"

class Renderer
{
private:
    Camera cam_;
    HittableList scene_;
public:
    Renderer(Camera cam, HittableList scene ): cam_(cam), scene_(scene)
    {}

    Color* run(double aspect_ratio, int img_width, int samples, int max_depth, int nb_thread=0, std::ostream &log=std::cout);

};

#endif // RENDERER_HPP