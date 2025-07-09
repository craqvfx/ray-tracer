# Ray tracer

## Code
### vec3.h
3D vector class for storing geometric vectors. Can be used for locations, colours, directions, offsets, etc.
Describes relevant operators for operations between both scalars and other vector operands.e.g. +=, *=, +, -, etc.
Stores each value as a double
Has alias point3

### color.h
Has one function write_color which takes a pixel and writes its rgb values in PPM format