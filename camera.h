#ifndef CAMERA_H
#define CAMERA_H

#include "hittable.h"
#include "material.h"

#include <fstream>

class camera
{
    public:
        // Defaults, to be set on creation of camera object using camera.aspect_ratio = ...
        double aspect_ratio      = 1.0;  // Ratio of image width over height
        int    image_width       = 100;  // Rendered image width in pixel count
        int    samples_per_pixel = 10;   // Count of random samples for each pixel
        int    max_depth         = 10;   // Maximum number of ray bounces into scene

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
                    color pixel_color(0,0,0);

                    for (int sample = 0; sample < samples_per_pixel; sample++)
                    {
                        ray r = get_ray(i, j);
                        pixel_color += ray_color(r, max_depth, world);
                    }
                    
                    write_color(out, pixel_samples_scale * pixel_color);
                }
            }

            out.close();
            std::clog << "\rDone.                   \n";
        }

    private:
        int    image_height;        // Rendered image height
        double pixel_samples_scale; // Color scale factor for a sum of pixels
        point3 center;              // Camera center
        point3 pixel00_loc;         // Location of pixel 0, 0
        vec3   pixel_delta_u;       // Offset to pixel to the right
        vec3   pixel_delta_v;       // Offset to pixel below

        void initialize()
        {
            image_height = int(image_width / aspect_ratio);
            image_height = (image_height < 1) ? 1 : image_height;

            pixel_samples_scale = 1.0 / samples_per_pixel;

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
        
        ray get_ray(int i, int j) const
        {
            //Construct a camera ray originating from the origin and directed at randomly sampled point around the pixel location i, j.

            auto offset = sample_square();
            auto pixel_sample = pixel00_loc
                            + ((i + offset.x()) * pixel_delta_u)
                            + ((j + offset.y()) * pixel_delta_v);

            auto ray_origin = center;
            auto ray_direction = pixel_sample - ray_origin;

            return ray(ray_origin, ray_direction);
        }

        vec3 sample_square() const
        {
            //Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
            return vec3(random_double() - 0.5, random_double() - 0.5, 0);
        }

        color ray_color(const ray &r, int depth, const hittable& world)
        {
            if (depth <= 0)
                return color(0,0,0);
            
            hit_record rec;
            if (world.hit(r, interval(0.001, INFINITY), rec))
            {
                ray scattered;
                color attenuation;
                if (rec.mat->scatter(r, rec, attenuation, scattered))
                    return attenuation * ray_color(scattered, depth - 1, world);
                return color(0,0,0);
            }

            // Blue sky gradient.
            vec3 unit_direction = unit_vector(r.direction());
            auto a = 0.5*(unit_direction.y() + 1.0);
            return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
        }
};

#endif