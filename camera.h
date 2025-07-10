#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"

#include <fstream>

class camera
{
    public:
        // Defaults, to be set on creation of camera object using camera.aspect_ratio = ...
        double aspect_ratio = 1.0;
        int image_width = 100;
    
        void render(const hittable& world)
        {
            initialize();
            
            std::ofstream out("image.ppm");

            out << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            for (int j = 0; j < image_height; j++)
            {
                std::clog << "\rScanlines remaining: " << (image_height - j) <<  ' ' << std::flush;

                for (int i = 0; i < image_width; i++) 
                {
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - center;
                    ray r(center, ray_direction);

                    color pixel_color = ray_color(r, world);
                    write_color(out, pixel_color);
                }
            }

            out.close();
            std::clog << "\rDone.                   \n";
        }

    private:
        int    image_height;   // Rendered image height
        point3 center;         // Camera center
        point3 pixel00_loc;    // Location of pixel 0, 0
        vec3   pixel_delta_u;  // Offset to pixel to the right
        vec3   pixel_delta_v;  // Offset to pixel below

        void initialize()
        {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            center = point3(0, 0, 0);

            // Determine viewport dimensions.
            auto focal_length = 1.0;
            auto viewport_height = 2.0;
            auto viewport_width = viewport_height * (double(image_width) / image_height);

            // Calculate the vectors across the horizontal and down the vertical viewport edges.
            auto viewport_u = vec3(viewport_width, 0, 0);
            auto viewport_v = vec3(0, -viewport_height, 0);

            // Calculate the horizontal and vertical delta vectors from pixel to pixel.
            pixel_delta_u = viewport_u / image_width;
            pixel_delta_v = viewport_v / image_height;

            // Calculate the location of the upper left pixel.
            auto viewport_upper_left = center
                                    - vec3(0, 0, focal_length)   // Move forward to the image plane.
                                    - viewport_u / 2             // Move left to the left edge.
                                    - viewport_v / 2;            // Move up to the top edge.
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v); // Move to center of top left pixel (half a pixel down and half a pixel left). Doesn't move it along z axis at all as pixel_delta_... both have 0 as their z value.
        }
         
        color ray_color(const ray &r, const hittable& world)
        {
            hit_record rec;
            if (world.hit(r, interval(0, INFINITY), rec))
            {
                return 0.5 * (rec.normal + color(1,1,1));
            }

            // Blue sky gradient.
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif