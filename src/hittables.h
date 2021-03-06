#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class Hittables : public Hittable {
    public:
        Hittables() {}
        Hittables(shared_ptr<Hittable> object) { add(object); }

        void clear() { objects.clear(); }
        void add(shared_ptr<Hittable> object) { objects.push_back(object); }

        bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
            hit_record temp_rec;
            bool hit_anything = false;
            double closest_so_far = t_max;

            for (const shared_ptr<Hittable>& object : objects) {
                if (object->hit(r, t_min, closest_so_far, temp_rec)) {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }


    public:
        std::vector<shared_ptr<Hittable>> objects;
};

#endif
