#pragma once

#include "hittable.hh"

class triangle : public hittable
{
public:
    triangle()
    {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {}

private:
};