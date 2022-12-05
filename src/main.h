#include "common.h"
#include <Windows.h>

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Operators ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// scalar * vector
Vec2 operator*(f64 A, Vec2 B)
{
	Vec2 result;

	result.x = A * B.x;
	result.y = A * B.y;

	return result;
}

// scalar vector using *=
Vec2 &Vec2::operator*=(f64 A)
{
	*this = A * *this;
	return *this;
}

// -ve vector
Vec2 operator-(Vec2 A)
{
	Vec2 result;

	result.x = -A.x;
	result.y = -A.y;

	return result;
}

// add vectors
Vec2 operator+(Vec2 A, Vec2 B)
{
    Vec2 result;

    result.x = A.x + B.x;
    result.y = A.y + B.y;

    return result;
}

// add vector using +=
Vec2 &Vec2::operator+=(Vec2 A)
{
	*this = *this + A;
	return *this;
}

// subtract vectors
Vec2 operator-(Vec2 A, Vec2 B)
{
    Vec2 result;

    result.x = A.x - B.x;
    result.y = A.y - B.y;

    return result;
}

// subtract vector using -=
Vec2 &Vec2::operator-=(Vec2 A)
{
	*this = *this - A;
	return *this;
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Operators^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern void init(void);
extern void cleanup(void);
extern GPU_Image *load_image(char *filename);
extern void do_input(void);
extern void update(void);
extern void render(f64 lag);
extern s32 round_float2Int(float fNum);
extern f32 get_vector_length(Vec2 A);
extern f32 get_vector_length(Vec2 A, Vec2 B);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


App app;
