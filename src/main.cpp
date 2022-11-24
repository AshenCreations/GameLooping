#include "main.h"

clock_t clockStart, clockEnd;
double timeTaken;
GPU_Image *background;
GPU_Image *smiley;

int WinMain(int argc, char *argv[])
{
	SDL_memset(&app, 0, sizeof(App));

	init();

	background = load_image("img/startbg.png");
	GPU_SetAnchor(background, 0.0f, 0.0f);
	smiley = load_image("img/smiley.png");
	GPU_SetImageFilter(smiley, GPU_FILTER_NEAREST);		//set the image to nearest filtering
	SDL_ShowCursor(SDL_DISABLE);
	
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
		blit(smiley, (f32)app.mouse.pos.x, (f32)app.mouse.pos.y);		// blit image after menu so is on top

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
