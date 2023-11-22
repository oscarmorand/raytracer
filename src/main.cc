#include "raytracer.hh"
#include "scene.hh"

int main()
{
    scene scene = scene::create_simple_square_mesh_scene();
    scene.load();
}