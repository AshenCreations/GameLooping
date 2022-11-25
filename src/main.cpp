#include "main.h"

clock_t clockStart, clockEnd;
double timeTaken;
//GPU_Image *background;
GPU_Image *smiley;

int WinMain(int argc, char *argv[])
{
	SDL_memset(&app, 0, sizeof(App));

	init();

	//background = load_image(IMAGEPATH_background);
	//GPU_SetAnchor(background, 0.0f, 0.0f);				// change the image anchor point to top left (bottom right is 1, 1)
	smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(smiley, GPU_FILTER_NEAREST);		// set the image to nearest filtering
	
	atexit(cleanup);

	f32 rotation = 0.0f;


	// main gameloop
	while (1)
	{
		clockStart = clock();

		prepare_scene();

		do_input();

//	    blit(background, 0, 0);

		do_menu();

		draw_atomic_test();

//		blit(smiley, (f32)app.mouse.pos.x, (f32)app.mouse.pos.y);		// blit image after menu so is on top
		GPU_BlitRotate(smiley, NULL, app.renderTarget, (f32)app.mouse.pos.x, (f32)app.mouse.pos.y, rotation);
		rotation++;
		if(rotation > 359)
			rotation = 0.0f;
		
		present_scene();

		if(check_keypress(ACTION_KEY_ESCAPE, app.keybind.escape))
			do_event(EVENT_QUIT);

		if(check_keypress(ACTION_SCREENSHOT, app.keybind.printscreen))
			do_event(EVENT_KEYPRESSED_SCREENSHOT);

		clockEnd = clock();
		timeTaken = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;
		printf("Time taken before sleep is: %.3f seconds\n", timeTaken);

		_sleep(10);
	}
}
