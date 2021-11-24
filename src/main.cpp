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
#include "Material.hpp"

Color ray_color(const Ray &r, const Hittable& world, int depth){
    hit_record rec;

    if(depth <= 0)
        return Color(0,0,0);
    if(world.hit(r,0.001,INFINITY,rec)){
        Ray scattered;
        Color attenuation;
        if(rec.mat_ptr->scatter(r, rec, attenuation, scattered))
        {
            return attenuation * ray_color(scattered, world, depth-1);
        }
        return Color(0,0,0);
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
    const int samples = 500;
    const int max_depth = 10;

    // World
    auto earth_mat = std::make_shared<Lanbertian>(Color(0,0.8,0.1));
    auto center_mat = std::make_shared<Lanbertian>(Color(0.2,0.2,1));
    auto right_mat = std::make_shared<Metal>(Color(0.7,0.7,0.7),0.4);
    auto left_mat = std::make_shared<Dielectric>(1.5);

    HittableList world;
    world.add(std::make_shared<Sphere>(Point3(0,0,-1), 0.5, center_mat));
    world.add(std::make_shared<Sphere>(Point3(0,-100.5,-1), 100, earth_mat));
    world.add(std::make_shared<Sphere>(Point3(1,0,-1),0.5,right_mat));
    world.add(std::make_shared<Sphere>(Point3(-1,0,-1),0.5,left_mat));

    // Camera
    Point3 look_from = Point3(-2,2,1);
    Point3 look_at = Point3(0,0,-1);
    Vec3 vup = Vec3(0,1,0);
    auto dist_to_focus = (look_from - look_at).length();

    Camera cam(look_from, look_at, vup, 90, aspect_ratio,dist_to_focus,2.0);

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