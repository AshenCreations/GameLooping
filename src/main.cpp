#include "main.h"

clock_t clockStart, clockEnd;
double timeTaken;


int WinMain(int argc, char *argv[])
{
	SDL_memset(&app, 0, sizeof(App));

	GPU_Image *background = init();

	atexit(cleanup);

	// main gameloop
	while (1)
	{
		clockStart = clock();

		prepare_scene();

		do_input();

	    blit(background, 0, 0);

		draw_atomic_test();

		do_menu();

		present_scene();

		clockEnd = clock();
		timeTaken = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;
		printf("Time taken before sleep is: %.3f seconds\n", timeTaken);

		if(check_keypress(ACTION_KEY_ESCAPE, app.keybind.escape))
			do_event(EVENT_QUIT);

		if(check_keypress(ACTION_SCREENSHOT, app.keybind.printscreen))
			do_event(EVENT_KEYPRESSED_SCREENSHOT);

		_sleep(10);
	}
}
