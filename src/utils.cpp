#include "utils.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

s32 round_float2Int(f32 fNum);
f32 square(f32 num);
f32 check_distance(Vec2 a, Vec2 b);
f32 get_vector_length(Vec2 vec);

// f32 lerp(f32 v0, f32 v1, f64 t);
// f32 inverse_lerp(f32 a, f32 b, f32 v);
// Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t);

Vec2 make_Vec2(f32 x, f32 y);
f32 dot_product(Vec2 a, Vec2 b);
Vec2 unit_Vec2(Vec2 a);
bool circle_in_circle(Circle a, Circle b);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// round a f32 to nearest s32
s32 round_float2Int(f32 fNum)
{
    f32 offset = 0.5f;
    if(fNum < 0)
        offset = -0.5f;
    return (s32)(fNum + offset);
}

// return the square of float
f32 square(f32 num)
{
    return num * num;
}

// returns the distance between Vec2 positions
f32 check_distance(Vec2 a, Vec2 b)
{
    return sqrtf(square(b.x - a.x) + square(b.y - a.y));
}

// returns vector magnitude from Vec2 input
f32 get_vector_length(Vec2 vec)
{
    return sqrtf(square(vec.x) + square(vec.y));
}

//^^^^^^^^^^^^^^^^^^^^^ lerps ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// lerp returns a blend between a and b, based on a fraction t
// inverse lerp returns a fraction t, based on a value between a and b

// // float lerp
// f32 lerp(f32 v0, f32 v1, f32 t)
// {
//     return ((1 - t) * v0) + (t * v1);
// }

// // inverse lerp
// f32 inverse_lerp(f32 a, f32 b, f32 v)
// {
//     return (v - a) - (b - a);
// }

// // vector lerp
// Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t)
// {
//     return (start * (1 - (f32)t)) + (end * (f32)t);    
// }

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// make 2 floats into a Vec2
Vec2 make_Vec2(f32 x, f32 y)
{
    return {x, y};
}

// return inner product of 2 Vec2's
f32 dot_product(Vec2 a, Vec2 b)
{
    return (a.x * b.x) + (a.y * b.y);
}

// returns a Vec2 input as a unit vector
Vec2 unit_Vec2(Vec2 a)
{
    return (a / get_vector_length(a));
}

// return if 2 circles collide
bool circle_in_circle(Circle a, Circle b)
{
    Vec2 dist = a.pos - b.pos;
    f32 dist2 = dot_product(dist, dist);
    f32 radiusSum = a.radius + b.radius;
    return dist2 <= square(radiusSum);
}

// void ring_to_linear_array()
// {
//     for (int i = 0; i < app.player.moveQueue.size; i++)
//     {
//         app.player.lArray[i] = app.player.moveQueue.array[(app.player.moveQueue.front + i) % app.player.moveQueue.capacity];
//     }
// }
