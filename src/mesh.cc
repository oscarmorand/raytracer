#include "mesh.hh"

#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

void mesh::load(const std::string path)
{
    if (!(fs::exists(path) && fs::is_regular_file(path)))
    {
        throw std::runtime_error(
            "File does not exist or is not a regular file: " + path);
    }

    std::string extension = fs::path(path).extension().string();

    if (extension == ".obj")
    {
        mesh::load_obj(path);
    }
    else
    {
        throw std::runtime_error("Unsupported file extension: " + extension);
    }
}

void mesh::load_obj(const std::string path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file: " + path);
    }

    std::vector<vec3> vertices;

    std::string line;
    while (std::getline(file, line))
    {
        if (line[0] == 'v')
        {
            if (line[1] == ' ')
            {
                double x, y, z;
                sscanf(line.c_str(), "v %lf %lf %lf", &x, &y, &z);
                vertices.push_back(vec3(x, y, z) * scale + pos);
            }
        }
        else if (line[0] == 'f')
        {
            int v0, v1, v2;
            sscanf(line.c_str(), "f %d %d %d", &v0, &v1, &v2);
            add(std::make_shared<triangle>(
                vertices[v0 - 1], vertices[v1 - 1], vertices[v2 - 1], mat));
        }
    }
}