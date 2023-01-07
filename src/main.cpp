#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	init();
	atexit(cleanup);

	//! only needed if use Sleep()
	timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib

	LARGE_INTEGER newTime, currentTime;
    app.t = 0.0;
    app.dt = 0.01f * app.dtMulti;	// dt * multiplier based on refresh rate
	f32 timeFrame;

	init2();

	QueryPerformanceCounter(&currentTime);
	f32 accumulator = 0.0;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while(1)
	{
		QueryPerformanceCounter(&newTime);

		// get timeFrame in milliseconds
		// divide by 10k since value of QueryPerformanceFrequency is 10,000,000 //! is that just on my machine ?????
		// when doing very small amounts of work the timeFrame(+1ms sleep) = vsynced frame length
		timeFrame = (newTime.QuadPart - currentTime.QuadPart) / 10000.0f;
		currentTime = newTime;

		// set update loop length
		if(timeFrame > 0.25)
			timeFrame = 0.25f;
		accumulator += timeFrame;

		// handle input
		input();

		// update loop
		while(accumulator >= app.dt)
		{
			update();
			app.t += app.dt;
			accumulator -= app.dt;
		}

		// accumulator / dt is in the range 0 to 1
		const f64 alpha = accumulator / app.dt;

		//! state blending as per "Fix Your Timestep" not being done right now

		// use alpha as param
		render(alpha);

		//! not needed if use Vsync
		Sleep(1);	// but still stops CPU working overtime
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
