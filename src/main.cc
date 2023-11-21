#include "raytracer.hh"
#include "scene.hh"

int main()
{
    scene first_test_scene = scene::create_first_test_scene();
    first_test_scene.load();
}