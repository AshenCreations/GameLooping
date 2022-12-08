#include "common.h"
#include <Windows.h>

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Operators ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// -ve of a vector
Vec2 operator-(Vec2 A)
{
	Vec2 result;

	result.x = -A.x;
	result.y = -A.y;

	return result;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Operators^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern void init(void);
extern void cleanup(void);
extern GPU_Image *load_image(char *filename);
extern void input(void);
extern void update(f64 t, f64 dt);
extern void render(f64 alpha);
extern f32 get_vector_length(Vec2 A);
extern f32 get_vector_length(Vec2 A, Vec2 B);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


App app;
