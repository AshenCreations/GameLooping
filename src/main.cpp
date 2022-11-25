#include "main.h"

clock_t clockStart, clockEnd;
double timeTaken;
//GPU_Image *background;
GPU_Image *smiley;

int WinMain(int argc, char **argv)
{
	SDL_memset(&app, 0, sizeof(App));

	init();
	atexit(cleanup);

	//background = load_image(IMAGEPATH_background);
	//GPU_SetAnchor(background, 0.0f, 0.0f);				// change the image anchor point to top left (bottom right is 1, 1)
	smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(smiley, GPU_FILTER_NEAREST);		// set the image to nearest filtering
	

	// mainloop
	while (1)
	{
		clockStart = clock();

		prepare_scene();

		do_input();

//	    blit(background, 0, 0);

//		do_menu();
//		draw_atomic_test();



		if((app.enemyCount < app.eSpawn.maxSpawns) && (app.eSpawn.cooldown == 0))
		{
			spawn_enemy();
			app.eSpawn.cooldown = 75;
		}
		app.eSpawn.cooldown -= 1;

		update_enemy();
		for(int i = 0; i < app.enemyCount; i++)
		{
			if(app.enemy[i].alive)
			{
				GPU_Blit(smiley, NULL, app.renderTarget, (f32)app.enemy[i].pos.x, (f32)app.enemy[i].pos.y);
			}
		}



		present_scene();

		// check if keys are pressed
		if(check_keypress(app.keybind.escape))
			do_event(EVENT_QUIT);

		if(check_keypress(app.keybind.printscreen))
			do_event(EVENT_KEYPRESSED_SCREENSHOT);

		// calc time taken to get here from start of mainloop
		clockEnd = clock();
		timeTaken = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;
		printf("Time taken before sleep is: %.3f seconds\n", timeTaken);

		_sleep(10);
	}
}
