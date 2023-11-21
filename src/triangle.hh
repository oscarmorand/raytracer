#pragma once

#include "hittable.hh"

class triangle : public hittable
{
public:
    triangle(point3 _v0, point3 _v1, point3 _v2, shared_ptr<material> _mat)
        : v0(_v0)
        , v1(_v1)
        , v2(_v2)
        , mat(_mat)
    {
        vec3 v0v1 = v1 - v0;
        vec3 v0v2 = v2 - v0;
        n = unit_vector(cross(v0v1, v0v2));
    }

    void set_material(shared_ptr<material> _mat)
    {
        mat = _mat;
    }

    bool hit(const ray &r, interval ray_t, hit_record &rec) const override
    {
        // check if the ray and triangle plane are parallel
        double nDotRayDir = dot(n, r.direction());
        if (kEpsilonInterval.surrounds(nDotRayDir))
        {
            // Ray perpendicular to the plane
            return false;
        }

        double d = -dot(n, v0);
        double t = -(dot(n, r.origin()) + d) / nDotRayDir;
        if (!ray_t.surrounds(t))
        {
            // The triangle is behind or the triangle isn't the closest hittable
            return false;
        }

        vec3 p = r.at(t);

        // Inside-outside test
        vec3 c;

        // Edge 0
        vec3 edge0 = v1 - v0;
        vec3 vp0 = p - v0;
        c = cross(edge0, vp0);
        if (dot(n, c) < 0)
        {
            // p is on the right side of the edge 0
            return false;
        }

        // Edge1
        vec3 edge1 = v2 - v1;
        vec3 vp1 = p - v1;
        c = cross(edge1, vp1);
        if (dot(n, c) < 0)
        {
            // p is on the right side of the edge 1
            return false;
        }

        // Edge2
        vec3 edge2 = v0 - v2;
        vec3 vp2 = p - v2;
        c = cross(edge2, vp2);
        if (dot(n, c) < 0)
        {
            // p is on the right side of the edge 2
            return false;
        }

        rec.t = t;
        rec.p = p;
        vec3 outward_normal = n;
        rec.set_face_normal(r, n);
        rec.mat = mat;

        return true;
    }

private:
    point3 v0;
    point3 v1;
    point3 v2;
    vec3 n;
    shared_ptr<material> mat;
};