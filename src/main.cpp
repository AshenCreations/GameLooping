#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	init();
	atexit(cleanup);

	//! not needed if we don't use Sleep()
	// timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib

	LARGE_INTEGER newTime, currentTime;
    app.t = 0.0;
    app.dt = 0.01 * app.dtMulti;	// dt * multiplier based on refresh rate
	f64 updateTimeFrame;

	QueryPerformanceCounter(&currentTime);
	f64 accumulator = 0.0;

	app.Dev.frameCounter = 0;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while (true)
	{
		QueryPerformanceCounter(&newTime);
 		updateTimeFrame = (newTime.QuadPart / 1000.0) - (currentTime.QuadPart / 1000.0);
		currentTime = newTime;

		if(updateTimeFrame > 0.25)
			updateTimeFrame = 0.25;
		accumulator += updateTimeFrame;

		// handle input
		input();					//* input
		
		// update loop
		while(accumulator >= app.dt)
		{
			update();				//* update
			app.t += app.dt;
			accumulator -= app.dt;
		}

		// accumulator / dt is in the range 0 to 1
		const f64 alpha = accumulator / app.dt;
		printf("alpha: %.2f\n", alpha);

		// render offset frame
		render(alpha);								//* render

		app.Dev.frameCounter++;
		printf("Frame Rendered: %u\n", app.Dev.frameCounter);

		//! is this needed if we use Vsync??
		// Sleep(1);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
