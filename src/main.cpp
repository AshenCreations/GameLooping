#include "main.h"
#include <Windows.h>

App app;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(app));

	atexit(cleanup);
	init();		// inits for SDL setup, refresh rate

	//! only needed if use Sleep()
	timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib

    app.time = 0.0;		// 1 second of t is 10 million QueryPerformanceCounter ticks
    //! use deltatime multiplier to set deltatime for the app
	app.dt = 0.01f * app.dtMulti;
	// definition one 1 second based on update/refresh rate
	app.oneSecond = app.appHz / app.dt * APP_BASE_TIMEFRAME;

	init2();	// other app inits inc. those which require app.dt

	float accumulator = 0.0;
	float timeFrame;
	LARGE_INTEGER newTime, currentTime, frequency;
	QueryPerformanceFrequency(&frequency);
	frequency.QuadPart /= 1000;			// divide by 1000 to convert microseconds to milliseconds
	QueryPerformanceCounter(&currentTime);
	QueryPerformanceCounter(&newTime);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while(1)
	{
		// get timeFrame in milliseconds then update time
		timeFrame = (newTime.QuadPart - currentTime.QuadPart) / (float)frequency.QuadPart;
		currentTime = newTime;
		app.time += timeFrame;

		// set update loop length
		//! timeFrame will need to be managed as render time increases
		//! Initially using a low value for a low number of updates
		if(timeFrame > APP_BASE_TIMEFRAME)
			timeFrame = APP_BASE_TIMEFRAME;
		accumulator += timeFrame;

		// handle input
		input();

		// update loop
		app.updatesPerFrame = 0;
		while(accumulator >= app.dt)
		{
			update();
			accumulator -= app.dt;
		}

		// after each update cycle there will be a part-frame we need to deal with
		// we will use a part-frame value(alpha) which is normalised to the range 0 -> 1
		const float alpha = accumulator / app.dt;
		render(alpha);

		//! Sleep not needed if use Vsync
		Sleep(1);	// but still stops CPU working overtime
		QueryPerformanceCounter(&newTime);
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
