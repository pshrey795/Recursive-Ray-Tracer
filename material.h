#ifndef MATERIAL_H
#define MATERIAL_H

#include<bits/stdc++.h>
#include "utilities.h"
#include "hittable.h"

using namespace std;

class material{

    public:

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& scattered) const = 0;

};

class lambertian : public material {

    public:
        color albedo;

        lambertian(const color& c) : albedo(c) {}

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& scattered) const override{
            auto scatter_dir = rec.norm + random_unit_ray();

            if(scatter_dir.near_zero()){
                scatter_dir = rec.norm;
            }

            scattered = ray(rec.p,scatter_dir);
            attenuation = albedo;
            return true;
        }

};

class metal : public material {

    public:
        color albedo;
        double fuzz;

        metal(const color& a,double f) : albedo(a), fuzz(f<1?f:1) {}

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& scattered) const override {
            vec3 reflected_dir = reflect(rec.norm,unit_vec(ray_in.dir));
            scattered = ray(rec.p,reflected_dir + fuzz*random_unit_ray());
            attenuation = albedo;
            return (dot(scattered.dir,rec.norm)>0);
        }

};

class dielectric : public material {

    public:
        double refractive_index;

        dielectric(double ir) : refractive_index(ir) {}

        virtual bool scatter(const ray& ray_in,const hit_record& rec,color& attenuation,ray& scattered) const override{
            attenuation = color(1,1,1);
            double relative_refractive_index = rec.front_face ? (1.0/refractive_index) : refractive_index;

            vec3 incident = unit_vec(ray_in.dir);
            double cosine = fmin(dot(-incident,rec.norm),1.0);
            double sine = sqrt(1.0-cosine*cosine);

            bool TIR = relative_refractive_index * sine > 1.0;
            vec3 dir;

            if(TIR || reflectance(cosine,relative_refractive_index) > random_double()){
                dir = reflect(rec.norm,incident);
            }else{
                dir = refract(rec.norm,incident,relative_refractive_index);
            }

            scattered = ray(rec.p,dir);
            return true;
        }

    private:

        //Schlick approximation for angular dependance of reflectance
        static double reflectance(double cosine,double ref_idx){
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1-cosine),5);
        }

};

#endif