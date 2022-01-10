#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class Sphere : public Hittable {
    public:
        Sphere() {}
        Sphere(Point3 cen, double r, shared_ptr<Material> m) : center(cen), radius(r), mat_ptr(m) {};

        bool hit(const Ray& r, double t_min, double t_max, hit_record& rec) const {
            Vec3 oc = r.origin() - center;
            double a = r.direction().length_squared();
            double half_b = dot(oc, r.direction());
            double c = oc.length_squared() - radius*radius;

            double discriminant = half_b*half_b - a*c;
            if (discriminant < 0) return false;
            double sqrtd = sqrt(discriminant);

            // Find the nearest root that lies in the acceptable range.
            double root = (-half_b - sqrtd) / a;
            if (root < t_min || t_max < root) {
                root = (-half_b + sqrtd) / a;
                if (root < t_min || t_max < root)
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;

            Vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat_ptr = mat_ptr;

            return true;
        }

    private:
        Point3 center;
        double radius;
        shared_ptr<Material> mat_ptr;
};

#endif
