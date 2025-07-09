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
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.0;

            int ir = int(255.999 *  r);
            int ig = int(255.999 *  g);
            int ib = int(255.999 *  b);

            out << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    out.close();
    std::clog << "\rDone.                   \n";
    return 0;
}
