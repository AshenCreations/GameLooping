#include "utils.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
bool mouse_in_rect(GPU_Rect rect);
s32 round_float2Int(f32 fNum);
f32 get_vector_length(Vec2 vec);
f32 lerp(f32 v0, f32 v1, f64 t);
Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t);
Vec2 make_Vec2(f32 x, f32 y);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// checks if the mouse is inside rect
bool mouse_in_rect(GPU_Rect rect)
{
	f32 x1 = rect.x;
    f32 x2 = x1 + rect.w;
    f32 y1 = rect.y;
    f32 y2 = y1 + rect.h;
    f32 mx = (f32)app.mouse.pos.x;
    f32 my = (f32)app.mouse.pos.y;

    return ((mx >= x1 && mx < x2) && (my >= y1 && my < y2)) ? true:false;
}

// round a f32 to nearest s32
s32 round_float2Int(f32 fNum)
{
    f32 deez = 0.5f;

    if(fNum < 0)
        deez = -0.5f;

    return (s32)(fNum + deez);
}

// returns vector magnitude from Vec2 input
f32 get_vector_length(Vec2 vec)
{
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

f32 lerp(f32 v0, f32 v1, f64 t)
{
    return ((1 - t) * v0) + (t * v1);
}

Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t)
{
    return (start * (1 - t)) + (end * t);    
}

Vec2 make_Vec2(f32 x, f32 y)
{
    return {x, y};
}
