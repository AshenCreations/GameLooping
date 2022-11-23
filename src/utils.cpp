#include "utils.h"

// checks if the mouse is inside rect
bool get_mouse_zone(GPU_Rect rect)
{
	f32 x1 = rect.x;
    f32 x2 = x1 + rect.w;
    f32 y1 = rect.y;
    f32 y2 = y1 + rect.h;
    f32 mx = (f32)app.mouse.pos.x;
    f32 my = (f32)app.mouse.pos.y;

    return ((mx >= x1 && mx < x2) && (my >= y1 && my < y2)) ? true:false;
}

s32 round_float2Int(float inNum)
{
    return (s32)(inNum + 0.5f);
}
