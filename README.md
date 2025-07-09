# Ray tracer

Major TO-DOs:
Add GUI
Output to PNG or similar format instead of PPM

## Disclaimer
This project was made using the help of the [Ray Tracing in One Weekend Book Series](https://github.com/RayTracing/raytracing.github.io/). While all of the code is provided in the afore-linked github repository, I typed everything by hand and have implemented some features of my own, as is hopefully demonstrated by the commit history.

## Code
### vec3.h
3D vector class for storing geometric vectors. Can be used for locations, colours, directions, offsets, etc.
Describes relevant operators for operations between both scalars and other vector operands.e.g. +=, *=, +, -, etc.
Stores each value as a double
Has alias point3

### color.h
Has one function write_color which takes a pixel and writes its rgb values in PPM format

### ray.h
Represents actual ray used for tracing

#### at(t) function explained
Position along the ray at a given time can be given as:
'Position(time) = origin + (time * direction)'
Where origin and direction are inherent properties of the ray, and time is a real value.