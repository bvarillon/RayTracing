#include <iostream>
#include <cmath>
#include <memory>
#include <future>

#include "Color.hpp"
#include "Point3.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "utils.hpp"
#include "Material.hpp"
#include "Renderer.hpp"

HittableList random_scene()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(Color(.5,.5,.5));
    world.add(std::make_shared<Sphere>(Point3(0,-1000,0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b<11; b++)
        {
            auto choose_mat = random_double();
            Point3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if((center-Point3(4,0.2,0)).length() > 0.9)
            {
                shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    auto albedo = Color::random() * Color::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                } else if (choose_mat < 0.95 ) {
                    auto albedo = Color::random(0.5,1);
                    auto rought = random_double(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, rought);
                } else {
                    sphere_material = std::make_shared<Dielectric>(1.5);
                }
                world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
            }
        }
        
    }
    auto material1 =  std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0,1,0),1.0, material1));

    auto material2 =  std::make_shared<Lambertian>(Color(0.4,0.2,0.1));
    world.add(std::make_shared<Sphere>(Point3(-4,1,0),1.0, material2));

    auto material3 =  std::make_shared<Metal>(Color(0.7,0.6,0.5),0.0);
    world.add(std::make_shared<Sphere>(Point3(4,1,0),1.0, material3));

    return world;
}

int main()
{
    // Img
    const auto aspect_ratio = 4.0/3.0;
    const int img_width = 800;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int samples = 50;
    const int max_depth = 5;


    // // World
    // auto earth_mat = std::make_shared<Lambertian>(Color(0,0.8,0.1));
    // auto center_mat = std::make_shared<Lambertian>(Color(0.2,0.2,1));
    // auto right_mat = std::make_shared<Metal>(Color(0.7,0.7,0.7),0.4);
    // auto left_mat = std::make_shared<Dielectric>(1.5);
    // auto mat = std::make_shared<Lambertian>(Color(0.8,0.2,0.5));

    // HittableList world;
    // world.add(std::make_shared<Sphere>(Point3(0,0,-1), 0.5, center_mat));
    // world.add(std::make_shared<Sphere>(Point3(0,-100.5,-1), 100, earth_mat));
    // world.add(std::make_shared<Sphere>(Point3(1,0,-1),0.5,right_mat));
    // world.add(std::make_shared<Sphere>(Point3(-1,0,-1),0.5,left_mat));
    // world.add(std::make_shared<Sphere>(Point3(0,0,0.5),0.5,mat));

    auto world = random_scene();

    // Camera
    Point3 look_from = Point3(10,5,3);
    Point3 look_at = Point3(0,0,0);
    Vec3 vup = Vec3(0,1,0);
    auto dist_to_focus = (look_from - look_at).length();
    // auto dist_to_focus = 10;
    auto aperture = 1;

    Camera cam(look_from, look_at, vup, 15, aspect_ratio, aperture, dist_to_focus);


    Renderer renderer(cam,world);
    auto render = renderer.run(aspect_ratio, img_width, samples, max_depth, std::thread::hardware_concurrency()-1);

    auto img = render;

    // write_image(std::cout, img, img_width, img_height);
    std::cout << "Saving file...";
    write_image_to_file(img, img_width, img_height,"test_e.jpg");
    std::cout << " Done !" << std::endl;

    delete img;
}