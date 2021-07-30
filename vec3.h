#ifndef VEC3_H
#define VEC3_H

#include <bits/stdc++.h>
using namespace std;

class vec3{

    public:
        double vec[3];
        double x() const {return vec[0];}
        double y() const {return vec[1];}
        double z() const {return vec[2];}

        vec3() : vec{0,0,0} {}
        vec3(double v0,double v1,double v2) : vec{v0,v1,v2} {}

        vec3 operator-() const { return vec3(-vec[0],-vec[1],-vec[2]); }
        double operator[](int i) const { return vec[i]; }
        double& operator[](int i) { return vec[i]; } 

        vec3& operator+=(const vec3 &v){
            vec[0] += v[0];
            vec[1] += v[1];
            vec[2] += v[2];
            return *this;
        }

        vec3& operator*=(const double t){
            vec[0] *= t;
            vec[1] *= t;
            vec[2] *= t;
            return *this;
        }

        vec3& operator/=(const double t){
            return *this *= (1/t);
        }

        double length() const {
            return sqrt(vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]);
        }

        bool near_zero() const {
            const auto s = 1e-8;
            return (fabs(vec[0])<s) && (fabs(vec[1])<s) && (fabs(vec[2])<s);
        }

};

//Aliasing
using point3 = vec3;
using color = vec3;
using light = vec3;

//Inline utility functions for increasing execution speed
inline ostream& operator<<(ostream& out,const vec3 &v){
    return out << v[0] << " " << v[1] << " " << v[2];  
}

inline vec3 operator+(const vec3 &u,const vec3 &v){
    return vec3(u[0]+v[0],u[1]+v[1],u[2]+v[2]);
}

inline vec3 operator-(const vec3 &u,const vec3 &v){
    return vec3(u[0]-v[0],u[1]-v[1],u[2]-v[2]);
}

inline vec3 operator*(const vec3 &u,const vec3 &v){
    return vec3(u[0]*v[0],u[1]*v[1],u[2]*v[2]);
}

inline vec3 operator*(double t,const vec3 &v){
    return vec3(t*v[0],t*v[1],t*v[2]);
}

inline vec3 operator*(const vec3 &u,double t){
    return t * u;
}

inline vec3 operator/(const vec3 &u,double t){
    return (1/t) * u;
}

inline double dot(const vec3 &u, const vec3 &v){
    return u[0]*v[0]+u[1]*v[1]+u[2]*v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v){
    return vec3(u[1] * v[2] - u[2] * v[1],
                u[2] * v[0] - u[0] * v[2],
                u[0] * v[1] - u[1] * v[0]);
}

inline vec3 unit_vec(vec3 v){
    return v / v.length();
}

inline vec3 reflect(const vec3& norm, const vec3& incident){
    return incident + 2*(-dot(norm,incident))*norm;
}

inline vec3 refract(const vec3& norm, const vec3& incident, double relative_refractive_index){
    auto cosine = fmin(dot(-incident,norm),1.0);
    vec3 r_perp = relative_refractive_index * (incident + cosine * norm);
    vec3 r_par  = -sqrt(1 - r_perp.length() * r_perp.length()) * norm;
    return r_perp + r_par;
}

#endif