#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	init(&app.currentState);
	atexit(cleanup);

	timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib
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
		input(&app.currentState);					//! input

		// update loop
		while(accumulator >= app.dt)
		{
			app.previousState = app.currentState;
			update(&app.currentState, app.t, app.dt);				//! update
			app.t += app.dt;
			accumulator -= app.dt;
			printf("updates\n");
		}

		// accumulator / dt is in the range 0 to 1
		const f64 alpha = accumulator / app.dt;
		printf("alpha: %.2f\n", alpha);

		// state blending
		State state = (app.currentState * alpha) + (app.previousState * (1.0 - alpha));

		// render the state
		render(&state);								//! render
		
		app.Dev.frameCounter++;
		printf("Frame Rendered: %d\n", app.Dev.frameCounter);

		Sleep(1);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
