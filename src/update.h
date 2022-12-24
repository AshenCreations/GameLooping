#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern Vec2 unit_Vec2(Vec2 a);
extern f32 dot_product(Vec2 a, Vec2 b);
extern void play_sound(Mix_Chunk *sound);
extern f32 check_distance(Vec2 a, Vec2 b);
extern Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t);
extern f32 square(f32 num);

extern App app;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
