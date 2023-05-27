#include "Renderer.hpp"

#include "Color.hpp"
#include "Point3.hpp"
#include "Ray.hpp"
#include "Hittable.hpp"
#include "HittableList.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "utils.hpp"
#include "Material.hpp"

using namespace std::chrono_literals;

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
    return (1.-t)*Color(1.0,1.0,1.0) + t*Color(0.5,0.7,1.0);
}

Color* Renderer::run(int img_height, int img_width, int samples, int max_depth, int nb_threads, std::ostream &log)
{
    if(nb_threads <= 0)
    {
        nb_threads = std::thread::hardware_concurrency();
    }

    log << "compute " << samples << " samples in " << nb_threads << " threads" << std::endl;


    Color* img = new Color[img_height*img_width];
    std::atomic<int> k(0);

    auto fn = [&](const int THREAD){
        for (int i=img_height-1-THREAD; i>=0; i -=  nb_threads)
        {
            for(int j=0; j<img_width; j++)
            {
                    Color pixel(0,0,0);
                    for(int s=0;s<samples;s++)
                    {
                        auto u = double(j+random_double()) / (img_width-1);
                        auto v = double(i+random_double()) / (img_height-1);

                        Ray r = cam_.get_ray(u,v);
                        pixel += ray_color(r,scene_, max_depth);
                    }

                img[(img_height-1-i)*img_width+j] = pixel/samples;
            }
            k++;
        }
    };

    std::vector<std::future<void>> threads(nb_threads);
    for (int n=0; n<nb_threads ; n++){
        // log << "thread " << k << " : " << sample_per_thread << " samples" << std::endl;
        threads[n] = std::async(fn, n);
    }

    while (k < img_height)
    {
        log << "\rWorking:" << (int) (float(k)/img_height*100) << std::flush;
        std::this_thread::sleep_for(500ms);
    }
    log << "\rWorking:" << (int) (float(k)/img_height*100) << std::flush;

    for(auto& th : threads)
    {
        th.get();
    }  
    log << std::endl << " Done !" << std::endl;

    return img;
}