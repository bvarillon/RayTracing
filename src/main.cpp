#include <iostream>
#include <cmath>
#include <memory>

#include "Color.hpp"
#include "Point3.hpp"
#include "Ray.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "utils.hpp"

Color ray_color(const Ray &r, const Hittable& world, int depth){
    hit_record rec;

    if(depth <= 0)
        return Color(0,0,0);
    if(world.hit(r,0.001,INFINITY,rec)){
        Point3 target = rec.p+rec.normal + Vec3::random_in_unit_vector();
        return 0.5 * ray_color(Ray(rec.p,target-rec.p), world, depth-1);
    }//
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y()+ 1.0); // t \in [0.,1.] decrivant la hauteur du rayon
    return (1-t)*Color(1.0,1.0,1.0) + t*Color(0.5,0.7,1.0);
}

int main()
{
    // Img
    const auto aspect_ratio = 16.0/9.0;
    const int img_width = 400;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int samples = 100;
    const int max_depth = 50;

    // World
    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Point3(0,-100.5,-1),100));

    // Camera
    Camera cam(aspect_ratio);

    //Header of the PPM format
    std::cout << "P3" << std::endl
              << img_width << ' ' << img_height << std::endl
              << "255" << std::endl;

    //Rendering the image
    for (int i=img_height-1; i>=0; i--)
    {
        std::cerr << "\rScanlines remaining:" << i << ' ' << std::flush;
        for(int j=0; j<img_width; j++)
        {
            Color pixel(0,0,0);
            for(int s=0;s<samples;s++)
            {
                auto u = double(j+random_double()) / (img_width-1);
                auto v = double(i+random_double()) / (img_height-1);

                Ray r = cam.get_ray(u,v);
                pixel += ray_color(r,world, max_depth);
            }
            write_color(std::cout,pixel,samples);

        }
    }
    std::cerr << std::endl << "Done !" << std::endl;
}