#pragma once

#include "camera.hh"
#include "color.hh"
#include "disk.hh"
#include "hittable_list.hh"
#include "material.hh"
#include "mesh.hh"
#include "plane.hh"
#include "raytracer.hh"
#include "sphere.hh"
#include "triangle.hh"

class scene
{
public:
    scene(camera _cam, hittable_list _world)
        : cam(_cam)
        , world(_world)
    {}

    void load()
    {
        cam.render(world);
    }

    static scene create_first_test_scene()
    {
        hittable_list world;

        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto material_center = make_shared<lambertian>(color(0.7, 0.3, 0.3));
        auto material_left = make_shared<metal>(color(0.8, 0.8, 0.8), 0.15);
        auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.9);
        auto material_miror = make_shared<metal>(color(0.7, 0.7, 0.7), 0.05);

        world.add(make_shared<plane>(point3(0.0, -0.5, 0.0),
                                     vec3(0.0, 1.0, 0.0), material_ground));
        world.add(
            make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(
            make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(
            make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));
        world.add(make_shared<disk>(point3(0.0, -0.3, -1.0),
                                    unit_vector(vec3(0.0, 1.0, 0.0)), 0.6,
                                    material_miror));
        world.add(make_shared<triangle>(
            point3(0.0, 0.0, -0.5), point3(0.25, 0.0, -0.3),
            point3(0.0, 0.5, -0.5), material_center));
        world.add(make_shared<triangle>(
            point3(0.0, 0.0, -0.5), point3(-0.25, 0.0, -0.3),
            point3(0.0, 0.5, -0.5), material_miror));

        camera cam;

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;

        return scene(cam, world);
    }

    static scene create_simple_square_mesh_scene()
    {
        hittable_list world;

        auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
        auto square_mat = make_shared<lambertian>(color(1.0, 0.5, 0.5));

        world.add(make_shared<plane>(point3(0.0, -0.5, 0.0),
                                     vec3(0.0, 1.0, 0.0), material_ground));
        world.add(make_shared<mesh>("./assets/simple_square.obj",
                                    point3(-0.5, -0.5, -1), vec3(1, 1, 1),
                                    square_mat));

        camera cam;

        cam.aspect_ratio = 16.0 / 9.0;
        cam.image_width = 400;
        cam.samples_per_pixel = 100;
        cam.max_depth = 50;

        return scene(cam, world);
    }

private:
    camera cam;
    hittable_list world;
};