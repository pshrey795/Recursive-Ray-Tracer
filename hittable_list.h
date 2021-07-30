#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include<bits/stdc++.h>
using namespace std;

class hittable_list : public hittable{

    public:
        vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<hittable> object) { objects.push_back(object); }

        virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

};

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for(int i=0;i<objects.size();i++){
        if(objects[i]->hit(r,t_min,closest_so_far,temp_rec)){
            temp_rec.idx = i;
            rec = temp_rec;
            hit_anything = true;
            closest_so_far = temp_rec.t;
        }
    }
    return hit_anything;
}

#endif