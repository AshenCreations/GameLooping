#include "utils.h"

bool get_mouse_zone(GPU_Rect rect);
s32 round_float2Int(float fNum);
f32 get_vector_length(Vec2 vec);
void sprite_anim_to_frames();
void build_filename(char *name, int frame);



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

// round a f32 to nearest s32
s32 round_float2Int(f32 fNum)
{
    if(fNum >= 0)
        return (s32)(fNum + 0.5f);
    else
        return (s32)(fNum - 0.5f);
}

// returns vector magnitude from Vec2 input
f32 get_vector_length(Vec2 vec)
{
    return sqrtf((vec.x * vec.x) + (vec.y * vec.y));
}

// test to split .png sprite animsheet into individual frames
void sprite_anim_to_frames()
{
    GPU_Rect rect = {0, 0, 250, 250};

    app.spriteImages[0] = load_image("img/Run.png");
    SDL_Surface *base = GPU_CopySurfaceFromImage(app.spriteImages[0]);

    for(int i = 1; i < 9; i++)
    {
        char buffer[100] = "Run_frame";
        rect.x = (i - 1) * 250.0f;

        app.spriteImages[i] = GPU_CopyImageFromSurfaceRect(base, &rect);
        build_filename(buffer, i);
        GPU_SaveImage(app.spriteImages[i], buffer, GPU_FILE_PNG);
    }
}

// generate a filename for .png frames
void build_filename(char *name, int frame)
{
    sprintf(name, "%s_%d.png", name, frame);
}
