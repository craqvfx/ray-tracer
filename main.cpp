#include "vec3.h"
#include "color.h"

#include <iostream>
#include <fstream>

int main()
{
    // Image
    
    const int image_width = 256;
    const int image_height = 256;

    // Open file for output
    std::ofstream out("image.ppm");

    // Render ppm image

    out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int i = 0; i < image_height; i++)
    {
        std::clog << "\rScanlines remaining: " << (image_height - i) <<  ' ' << std::flush;

        for (int j = 0; j < image_width; j++) 
        {
            auto pixel_color = color(double(i)/(image_width-1), double(j)/(image_width-1), 0);
            write_color(out, pixel_color);
        }
    }

    out.close();
    std::clog << "\rDone.                   \n";
    return 0;
}
