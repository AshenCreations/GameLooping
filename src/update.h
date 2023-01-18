#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern Vec2 unit_Vec2(Vec2 a);
extern f32 dot_product(Vec2 a, Vec2 b);
extern void play_sound(Mix_Chunk *sound, bool flag);
extern f32 square(f32 num);
extern bool circle_in_circle(Circle a, Circle b);

extern Vec2 move_stop(void);


extern App app;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
