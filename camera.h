#ifndef CAMERA_H
#define CAMERA_H

#include<bits/stdc++.h>
#include "utilities.h"
using namespace std;

class camera{

    public:

        point3 origin;
        point3 lower_left_corner;
        vec3 horizontal,vertical;
        vec3 u,v,w;
        double lens_radius;

        camera(double v_fov,double input_aspect_ratio,double aperture, double focal_length,point3 lookfrom,point3 lookat,vec3 upward_dir){
            auto aspect_ratio = input_aspect_ratio;
            auto v_fov_rad = deg_to_rad(v_fov);
            auto screen_height = 2.0 * focal_length * tan(v_fov_rad/2);
            auto screen_width = aspect_ratio * screen_height;

            auto w = unit_vec(lookfrom - lookat);
            auto u = unit_vec(cross(upward_dir,w));
            auto v = cross(w,u);

            origin = lookfrom;
            horizontal = screen_width * u;
            vertical = screen_height * v;
            lower_left_corner = origin - focal_length * w - vertical/2 - horizontal/2;
            lens_radius = aperture/2;
        }

        ray get_ray(double s,double t) const{
            vec3 rd = lens_radius * random_in_unit_disk();
            vec3 offset = u*rd.x() + v*rd.y();
            return ray(origin+offset,lower_left_corner + s*horizontal + t*vertical - origin - offset);
        }

};

#endif