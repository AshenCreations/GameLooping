#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	init();
	atexit(cleanup);

	//! only needed if use Sleep()
	// timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib

	LARGE_INTEGER newTime, currentTime, countFrequency;
    app.t = 0.0;
    app.dt = 0.01 * app.dtMulti;	// dt * multiplier based on refresh rate
	f64 timeFrame;

	QueryPerformanceCounter(&currentTime);
	f64 accumulator = 0.0;

	app.Dev.frameCounter = 0;
	bool running = true;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while (running)
	{
		QueryPerformanceCounter(&newTime);
		
		// get timeFrame in milliseconds
		// divide by 10k since value of QueryPerformanceFrequency is 10,000,000
		// when doing very small amounts of work the timeFrame = vsynced frame length
		timeFrame = (newTime.QuadPart - currentTime.QuadPart) / 10000.0;
		currentTime = newTime;

		// set update loop length
		if(timeFrame > 0.25)
			timeFrame = 0.25;
		accumulator += timeFrame;

		// handle input
		input();					//* input
		
		// update loop
		while(accumulator >= app.dt)
		{
			update();				//* update
			app.t += app.dt;
			accumulator -= app.dt;
			printf("updates\n");
		}

		// accumulator / dt is in the range 0 to 1
		const f64 alpha = accumulator / app.dt;
		printf("alpha: %.2f\n", alpha);

		// render offset frame
		render(alpha);								//* render

		app.Dev.frameCounter++;
		printf("Frame Rendered: %u\n", app.Dev.frameCounter);

		//! not needed if use Vsync
		// Sleep(1);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
