# Ray tracer

## Major TO-DOs:
- Add GUI<br>
- Output to PNG or similar format instead of PPM<br>

## Disclaimer
This project was made using the help of the [Ray Tracing in One Weekend Book Series](https://github.com/RayTracing/raytracing.github.io/). While all of the code is provided in the afore-linked github repository, I typed everything by hand and have implemented some features of my own, as is hopefully demonstrated by the commit history.

## Code
### vec3.h
Defines class for storing 3D vectors. Can be used for locations, colours, directions, offsets, etc.<br>
Describes relevant operators for operations between both scalars and other vector operands.e.g. +=, *=, +, -, etc.<br>
Stores each value as a double<br>
Has alias point3

### color.h
Takes a pixel and writes its rgb values in PPM format, converting from linear to gamma 2.

### ray.h
Defines ray class that stores information about the ray and has an at(t) function to give the position along that ray at a given time/offset.<br>
#### Stores the following information about a ray:
- Origin<br>
- Direction<br>

#### at(t) function explained
Position along the ray at a given time/offset can be given as:<br>
`Position(time) = origin + (time * direction)`<br>
Where origin is a 3D vector representing position, direction is a 3D unit vector, and time is a real value.

### camera.h
Defines a class that contains information about the camera all the functionality of the camera.<br>
It should be constructed with no arguments, then the owning code will modify the camera's public variables through simple assignment, then the owning code should call the render function, passing in a world.<br>
This pattern is chosen instead of the owner calling a constructor with a ton of parameters or by defining and calling a bunch of setter methods. Instead, the owning code only needs to set what it explicitly cares about.<br>

#### Stores the following information about a camera:
##### public:
- Aspect ratio<br>
- Image width<br>
- Samples per pixel
##### private:
- Image height<br>
- Color scale factor for a sum of pixels (pixel_samples_scale - To facilitate multiple samples, we add the full color from each sample, and then divide by the number of samples)<br>
- Camera center<br>
- Location of pixel (0, 0)<br>
- Offset to pixel to the right (delta u)<br>
- Offset to pixel below (delta v)<br>

#### Has the following procedures:
##### public:
- Render
##### private:
- Initialize (run at the beginning of every render)<br>
- Ray color

### hittable.h
#### hittable abstract class
Defines abstract class for all objects which should be hittable to inherit from.
#### hit_record class
#### Stores the following information about a hit:
- Point<br>
- Normal<br>
- t (time/offset at which ray intersects object)<br>
- Front face<br>

### hittable_list.h
Stores a list of hittable objects.
Uses shared_ptr to allow for instances and easier memory management.

### sphere.h
Defines sphere class that inherets from hittable.h

### interval.h
Defines interval class that stores information about a real-valued interval and has procedures to get information about that data.<br>
#### Stores the following information about an interval:
- min<br>
- max<br>

#### Has the following public procedures:
- size<br>
- contains<br>
- surrounds<br>