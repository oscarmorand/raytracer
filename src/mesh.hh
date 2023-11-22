#pragma once

#include <memory>
#include <vector>

#include "hittable.hh"
#include "material.hh"
#include "triangle.hh"

class mesh : public hittable
{
public:
    mesh(const std::string path, point3 _pos = { 0, 0, 0 },
         vec3 _scale = { 1, 1, 1 },
         shared_ptr<material> _mat = make_shared<lambertian>(default_mat))
        : pos(_pos)
        , scale(_scale)
        , mat(_mat)
    {
        load(path);
    }

    void load(const std::string path);

    void load_obj(const std::string path);

    void clear()
    {
        triangles.clear();
    }

    void add(shared_ptr<triangle> triangle)
    {
        triangles.push_back(triangle);
    }

    void set_material(shared_ptr<material> _mat)
    {
        mat = _mat;
        for (const auto &triangle : triangles)
        {
            triangle->set_material(_mat);
        }
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        hit_record temp_rec;
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto &triangle : triangles)
        {
            if (triangle->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
            {
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec;
            }
        }

        return hit_anything;
    }

private:
    std::vector<shared_ptr<triangle>> triangles;
    point3 pos;
    vec3 scale;
    shared_ptr<material> mat;
};