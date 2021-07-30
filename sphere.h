#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "material.h"

class sphere : public hittable{

    public:

        point3 centre;
        double radius;
        shared_ptr<material> mat_ptr;

        sphere() {}
        sphere(point3 c,double r,shared_ptr<material> m) : centre(c), radius(r), mat_ptr(m) {}

        virtual bool hit(const ray& r,double t_min,double t_max,hit_record& rec) const override;

};

bool sphere::hit(const ray& r,double t_min,double t_max,hit_record& rec) const {
    vec3 A = r.orig - centre;
    auto a = dot(r.dir,r.dir);
    auto b = dot(r.dir,A);
    auto c = dot(A,A) - radius*radius;
    auto dis = b*b - a*c;

    if(dis<0){
        return false;
    }else{
        auto t_low = (-b - sqrt(dis))/a;
        auto t_high = (-b + sqrt(dis)/a);
        auto root = t_low;
        if(root < t_min || root > t_max){
            root = t_high;
            if(root<t_min || root>t_max){
                return false;
            }
        }
        rec.t = root;
        rec.p = r.locate(root);

        //Using division by radius instead of finding unit vector has to do with the application of negative radii to create bubbles
        vec3 outward_normal = (rec.p-centre)/radius;            
        
        
        rec.set_face_normal(r,outward_normal);
        rec.mat_ptr = mat_ptr;
        return true;
    }
}

#endif 