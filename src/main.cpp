#include <iostream>
#include <cmath>
#include <memory>
#include <future>

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
    }
    Vec3 unit_direction = unit_vector(r.direction());
    auto t = 0.5*(unit_direction.y()+ 1.0); // t \in [0.,1.] decrivant la hauteur du rayon
    return (1-t)*Color(1.0,1.0,1.0) + t*Color(0.5,0.7,1.0);
}

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
    const int img_width = 500;
    const int img_height = static_cast<int>(img_width / aspect_ratio);
    const int samples = 100;
    const int max_depth = 50;

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
    auto aperture = 0.1;

    Camera cam(look_from, look_at, vup, 15, aspect_ratio, aperture, dist_to_focus);

    auto nb_threads = std::thread::hardware_concurrency();
    // auto nb_threads = 1;
    
    std::cerr << "compute " << samples << " samples in " << nb_threads << " threads" << std::endl;

    //Header of the PPM format
    // std::cout << "P3" << std::endl
    //           << img_width << ' ' << img_height << std::endl
    //           << "255" << std::endl;
    //Rendering the image
    Color* img = new Color[img_height*img_width];
    std::atomic<int> k(0);

    auto fn = [&](const int THREAD){
        for (int i=img_height-1-THREAD; i>=0; i -=  nb_threads)
        {
            k++;
            std::cerr << "\rWorking:" << (int) (float(k)/img_height*100) << std::flush;
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

                img[(img_height-1-i)*img_width+j] = pixel;
                // write_color(std::cout,pixel,samples);
            }
        }
    };

    std::vector<std::future<void>> threads(nb_threads);
    for (int k=0; k<nb_threads ; k++){
        // std::cerr << "thread " << k << " : " << sample_per_thread << " samples" << std::endl;
        threads[k] = std::async(fn, k);
    }
    for(auto& th : threads)
    {
        th.get();
    }
    std::cerr << std::endl;
    write_image(std::cout, img, img_width, img_height, samples);
    std::cerr << std::endl << "Done !" << std::endl;
}