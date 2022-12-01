#include "main.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Operators START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// scalar * vector
Vec2 operator*(f32 A, Vec2 B)
{
	Vec2 result;

	result.x = A * B.x;
	result.y = A * B.y;

	return result;
}

// *= for vectors
Vec2 &Vec2::operator*=(f32 A)
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

// += for vectors
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

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Operators END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


clock_t clockStart, clockEnd;
double timeTaken;
GPU_Image *smiley;


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Main START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int WinMain(int argc, char **argv)
{
	SDL_memset(&app, 0, sizeof(App));

	// Init before mainloop starts, may need to write some inits in such a way so they can be called later as "default" setting
	init();
	atexit(cleanup);

	smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(smiley, GPU_FILTER_NEAREST);		// set the image to nearest filtering
	
	// mainloop
	while (1)
	{
		clockStart = clock();

		// input();
		do_input();

		// update();
		update();

		// render();
		render(smiley);

		// calc time taken to get here from start of mainloop
		clockEnd = clock();
		timeTaken = clockEnd - clockStart;
		printf("Time taken before sleep is: %d ms\n", round_float2Int(timeTaken));

		// TODO fixed update timestep with variable rendering
		_sleep(10);
	}
}
