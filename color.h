#ifndef COLOR_H
#define COLOR_H

#include "ray_tracer.h"

#include "interval.h"
#include "vec3.h"

using color = vec3;

void write_color(std::ostream& out, const color& pixel_color) // Writes a single pixels colour (for PPM file format)
{
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Translate the [0,1] compponent values to the byte range [0,255].
    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    // Write out the pixel color componenets.
    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

#endif