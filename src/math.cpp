#include "math.h"

f32 vector_length(Vec2 vector);

f32 vector_length(Vec2 vector)
{
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}
