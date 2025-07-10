# Ray tracer

Major TO-DOs:
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
Has one function write_color which takes a pixel and writes its rgb values in PPM format

### ray.h
Defines ray class that stores information about the ray and has an at(t) function to give the position along that ray at a given time/offset.<br>
Stores the following information about a ray:
- Origin<br>
- Direction<br>

#### at(t) function explained
Position along the ray at a given time/offset can be given as:<br>
`Position(time) = origin + (time * direction)`<br>
Where origin is a 3D vector representing position, direction is a 3D unit vector, and time is a real value.

### hittable.h
#### hittable abstract class
Defines abstract class for all objects which should be hittable to inherit from
#### hit_record class
Stores the following information about a hit:
- Point<br>
- Normal<br>
- t (time/offset at which ray intersects object)<br>
- Front face<br>

### sphere.h
Defines sphere class that inherets from hittable.h