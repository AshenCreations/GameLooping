#include "main.h"

// windows entry point: since SDL is platform agnostic most tutorials don't show this,
// then people have problems running the .exe from icon or even trying to include <windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	init();
	atexit(cleanup);			

	timeBeginPeriod(1);			// set system sleep granularity to 1ms: winmm.lib
	LARGE_INTEGER newTime, currentTime;
    f64 t = 0.0;
    f64 dt = 0.01;
	f64 frameTime;

	QueryPerformanceCounter(&currentTime);
	f64 tempTime = currentTime.QuadPart / (1000.0 * 1000.0);
	f64 accumulator = 0.0;

    // State previous;
    // State current;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while (1)
	{
		QueryPerformanceCounter(&newTime);
 		frameTime = (f64)((newTime.QuadPart  / 1000) - (currentTime.QuadPart / 1000));
		currentTime = newTime;

		if(frameTime > 0.25)
			frameTime = 0.25;

		accumulator += frameTime;

		input();

		while(accumulator >= dt)
		{
			// previousState = currentState;
			update(t, dt);
			// update(currentState, t, dt);
			t += dt;
			accumulator -= dt;
			printf("loop:\n");
		}

		const f64 alpha = accumulator / dt;
		printf("alpha: %.2f\n", alpha);

		// State state = currentState * alpha + 
		// previousState * ( 1.0 - alpha );

		render(alpha);	//! not using alpha, just testing
		// render(state);
		printf("Frame Rendered\n");

		Sleep(1);		// and breathe
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
