#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

#include <iostream>

// XXX change to using proper types - templates?
/*class Color: public Vec3 { 
    using Vec3::Vec3;

    public:
        Color(Vec3 vec) : Vec3(vec.x(), vec.y(), vec.z()) {
        }
};*/

//inline Color operator+(const Color &u, const Color &v) {
//    return Color(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
//}

using Color = Vec3;

void write_color(std::ostream &out, Color pixel_color, int samples_per_pixel) {
    double r = pixel_color.x();
    double g = pixel_color.y();
    double b = pixel_color.z();

    // Divide the color by the number of samples.
    double scale = 1.0 / samples_per_pixel;
     // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

#endif
