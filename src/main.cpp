#include "main.h"
#include <Windows.h>


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Main START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SDL_memset(&app, 0, sizeof(App));

	// Init before mainloop starts, may need to write some inits in such a way so they can be called later as "default" setting
	init();
	atexit(cleanup);

	// TODO move this to ... later
	GPU_Image *smiley;
	smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(smiley, GPU_FILTER_NEAREST);

	timeBeginPeriod(1);		// set system sleep granularity to 1ms
	LARGE_INTEGER previous, current;
	f64 elapsed;
	f64 lag = 0.0;
	QueryPerformanceCounter(&previous);

	// mainloop
	while (1)
	{
		QueryPerformanceCounter(&current);						// in microseconds
		elapsed = (f64)(current.QuadPart - previous.QuadPart);
		previous = current;
		lag += elapsed / 1000.0;			// divide by 1000 to convert to ms
		printf("lag before input %.3f\n", lag);

		// input();
		do_input();

		// update();
		while(lag >= MS_PER_UPDATE)
		{
			update();
			lag -= MS_PER_UPDATE;
		}
		printf("lag after update %.3f\n", lag);

		// render();
		render(smiley, lag / MS_PER_UPDATE);	// divide by MS_PER_UPDATE to normalize to 0 - 1

		// try changing this after introducing the use of delta time
		Sleep(1);
	}
}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Main END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
