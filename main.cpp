#include "color.h"
#include "sphere.h"
#include "camera.h"
#include "hittable_list.h"
#include "material.h"
using namespace std;

light l(0,0,0);

color ray_color(const ray& r,const hittable_list& world,int maxDepth){
    hit_record rec;

    if(maxDepth<0){
        return color(0,0,0);
    }

    if(world.hit(r,0.001,inf,rec)){
        ray scattered;
        color attenuation;
        if(rec.mat_ptr->scatter(r,rec,attenuation,scattered)){
            return attenuation * ray_color(scattered,world,maxDepth-1);
        }else{
            return color(0,0,0);
        }
    }else{
        vec3 unit_dir = unit_vec(r.dir);
        auto t = 0.5*(unit_dir.y()+1.0);
        return (1-t)*color(1,1,1) + t*color(0.5,0.7,1);
    }
}

hittable_list random_scene(){
    hittable_list world;

    auto ground_material = make_shared<lambertian>(color(0.5,0.5,0.5));
    world.add(make_shared<sphere>(point3(0,-1000,0),1000,ground_material));

    for(int a = -11; a<11; a++){
        for(int b = -11; b<11; b++){
            auto choose_mat = random_double();
            point3 center(a+ 0.9*random_double(),0.2, b + 0.9*random_double());

            if((center-point3(4,0.2,0)).length()>0.9 && (center-point3(-4,0.2,0)).length()>0.9 && (center-point3(0,0.2,0)).length()>0.9){
                shared_ptr<material> sphere_mat;

                if(choose_mat < 0.8){
                    //diffuse
                    auto albedo = (color)(random_vec() * random_vec());
                    sphere_mat = make_shared<lambertian>(albedo);
                }else if(choose_mat < 0.95){
                    //metal
                    auto albedo = (color)(random_vec(0.5,1));
                    auto fuzz = random_double(0,0.5);
                    sphere_mat = make_shared<metal>(albedo,fuzz);
                }else{
                    //glass
                    sphere_mat = make_shared<dielectric>(1.5);
                }
                world.add(make_shared<sphere>(center,0.2,sphere_mat));

            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    auto material2 = make_shared<lambertian>(color(0.4,0.2,0.1));
    auto material3 = make_shared<metal>(color(0.7,0.6,0.5),0.0);
    world.add(make_shared<sphere>(point3(0,1,0),1.0,material1));
    world.add(make_shared<sphere>(point3(-4,1,0),1.0,material2));
    world.add(make_shared<sphere>(point3(4,1,0),1.0,material3));
    
    return world;
}

int main(){

    //Image Dimensions
    const auto aspect_ratio = 3.0/2.0;
    const int image_width = 1200;
    const int image_height = 800;
    const int samples_per_pixel = 10;
    const int max_ray_depth = 50;
    const auto v_fov = 20;
    auto aperture = 0.1;
    point3 lookfrom(13,2,3);
    point3 lookat(0,0,0);
    cout<<"P3\n"<<image_width<<" "<<image_height<<"\n255\n";

    //Scene/World
    hittable_list world = random_scene();

    //Camera
    camera cam(v_fov,aspect_ratio,aperture,10,lookfrom,lookat,vec3(0,1,0));

    //Rendering Image
    for(int j=image_height-1;j>=0;j--){
        cerr<<"\rScanlines remaining: "<<j<<" "<<std::flush;
        for(int i=0;i<image_width;i++){
            color pixel_color(0,0,0);
            for(int k=0;k<samples_per_pixel;k++){
                auto v = double(j + random_double())/(image_height-1);
                auto u = double(i + random_double())/(image_width-1);       
                ray r = cam.get_ray(u,v);
                pixel_color += ray_color(r,world,max_ray_depth);
            }
            write_color(cout,pixel_color,samples_per_pixel);
        }
    }

    cerr<<"\nDone.\n";
}