#pragma once

#include "hittable.hh"

class plane : public hittable
{
public:
    plane(point3 _p0, vec3 _n, shared_ptr<material> _mat)
        : p0(_p0)
        , n(_n)
        , mat(_mat)
    {}

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        float denom = dot(n, r.direction());
        if (denom > -1e-6) {
            return false;
        }
        vec3 p0l0 = p0 - r.origin();
        double t = dot(p0l0, n) / denom;
        if (!ray_t.surrounds(t))
        {
            return false;
        }

        rec.t = t;
        rec.p = r.at(rec.t);
        vec3 outward_normal = n;
        rec.set_face_normal(r, n);
        rec.mat = mat;

        return true;
    }

private:
    point3 p0;
    vec3 n;
    shared_ptr<material> mat;
};