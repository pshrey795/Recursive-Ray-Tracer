#ifndef HIT_H
#define HIT_H

#include "ray.h"
#include "utilities.h"

class material;

struct hit_record{
    point3 p;
    vec3 norm;
    double t;
    bool front_face;
    shared_ptr<material> mat_ptr;
    int idx;

    inline void set_face_normal(const ray& r,const vec3& outward_normal){
        front_face = dot(r.dir,outward_normal) < 0;
        norm = front_face ? outward_normal : -outward_normal;
    }
};

class hittable{

    public:
        virtual bool hit(const ray& r,double t_min,double t_max, hit_record& rec) const = 0;

};

#endif