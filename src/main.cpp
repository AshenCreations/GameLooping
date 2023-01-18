#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	// inits for SDL setup, refresh rate
	init();
	atexit(cleanup);

	//! only needed if use Sleep()
	timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib

	LARGE_INTEGER newTime, currentTime;
    app.t = 0.0;
    app.dt = 0.01f * app.dtMulti;	// dt * multiplier based on refresh rate
	app.oneSecond = app.appHz / (4 * app.dt); // (Hz * timeFrame) / dt
	f32 timeFrame;

	// other app inits inc. those which require app.dt
	init2();

	QueryPerformanceCounter(&currentTime);
	f32 accumulator = 0.0;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while(1)
	{
		QueryPerformanceCounter(&newTime);

		// get timeFrame in milliseconds
		// divide by 10k since value of QueryPerformanceFrequency is 10,000,000 //! is that just on my machine ?????
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

		// after each update cycle there will be a part frame we need to deal with
		// we will use a frame offset (alpha) which is normalised to the range 0 -> 1
		const f64 alpha = accumulator / app.dt;

		//! state blending as per "Fix Your Timestep" not being done right now

		// pass in alpha to deal with frame offset
		render(alpha);

		//! not needed if use Vsync
		Sleep(1);	// but still stops CPU working overtime
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
