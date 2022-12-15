#include "common.h"
#include <Windows.h>


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern void init(State *state);
extern void cleanup(void);
extern GPU_Image *load_image(char *filename);
extern void input(State *state);
extern void update(State *state, f64 t, f64 dt);
extern void render(State *state);
extern f32 get_vector_length(Vec2 A);
extern f32 get_vector_length(Vec2 A, Vec2 B);
extern Vec2 lerp_Vec2(Vec2 start, Vec2 end, f64 t);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


App app;
