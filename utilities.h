#ifndef UTILITY_H
#define UTILITY_H

//Headers
#include "ray.h"
#include "vec3.h"
using namespace std;

//Constants
const double pi = 3.1415926535897932385;
const double inf = numeric_limits<double>::infinity();

//Utility Functions
inline double deg_to_rad(double degrees){
    return degrees * pi / 180.0;
}

inline double random_double(){
    return rand() / (RAND_MAX + 1.0);   // 0.0 <= r < 1.0
}

inline double random_double(double min,double max){
    return min + (max-min)*(random_double());
}

inline vec3 random_vec(){
    return vec3(random_double(),random_double(),random_double());
}

inline vec3 random_vec(double min,double max){
    return vec3(random_double(min,max),random_double(min,max),random_double(min,max));
}

inline vec3 random_unit_ray(){
    while(true){
        auto p = random_vec(-1,1);
        if(p.length()<1){
            return p;
        }
    }
}

inline vec3 random_unit_vector(){
    return unit_vec(random_vec());
}

inline vec3 random_in_hemisphere(const vec3& normal){
    vec3 in_unit_sphere = random_unit_ray();
    if(dot(in_unit_sphere,normal)>0.0){
        return in_unit_sphere;
    }else{
        return -in_unit_sphere;
    }
}

inline vec3 random_in_unit_disk(){
    while(true){
        auto p = vec3(random_double(-1,1),random_double(-1,1),0);
        if(p.length()<1){
            return p;
        }
    }
}

inline double clamp(double x,double min, double max){
    if(x<min){
        return min;
    }else if(x>max){
        return max;
    }else{
        return x;
    }
}

#endif