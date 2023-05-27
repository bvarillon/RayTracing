#include "Arguments.hpp"

#include <iostream>
#include <fstream>

#include "Version.hpp"

#include "nlohmann/json.hpp"
#include "cxxopts.hpp"

using json = nlohmann::json;

Arguments pars_args(int argc, char* argv[])
{
    cxxopts::Options option("Raytracing", "Render image using raytracing");
    option.add_options()
    ("version", "Print the version", cxxopts::value<bool>())
    ("h,help", "Print usage", cxxopts::value<bool>())
    ("v,verbose", "Active verbose output", cxxopts::value<bool>()->default_value("false"))
    ("filename", "Name of the file to store the image", cxxopts::value<std::string>()->default_value("out.jpg"))
    ("s,size", "Size of the generique scene to render", cxxopts::value<int>()->default_value("11"))
    ;
    option.parse_positional({"filename"});

    auto result = option.parse(argc,argv);

    if (result.count("version"))
    {
        std::cout << "RayTracing - v" << VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }
    if (result.count("help"))
    {
        std::cout << option.help() << std::endl;
        exit(EXIT_SUCCESS);
    }

    Arguments params;

    params.verbose = result["verbose"].as<bool>();

    if(params.verbose && result.count("filename")==0)
    {
        std::cout << "No file name given, using default value : out.jpg" << std::endl;
    }

    params.filename = result["filename"].as<std::string>();
    params.size = result["size"].as<int>();

    std::ifstream confFile("conf.json");
    json conf;
    confFile >> conf;
    
    params.img_width = conf.value("width",800);
    params.img_height = conf.value("height",600);
    params.samples = conf.value("samples",50);
    params.max_depth = conf.value("depth",5);

    params.aspect_ratio = static_cast<double>(params.img_width)/static_cast<double>(params.img_height);

    if (params.verbose)
    {
        std::cout << "img : " << params.img_width << "x" << params.img_height << "(" << params.aspect_ratio << ")" << std::endl;
        std::cout << "samples : " << params.samples << " - depth" << params.max_depth << " - size " << params.size << std::endl;
    }
    return params;
}