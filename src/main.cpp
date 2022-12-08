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
    f64 dt = 0.02;
	f64 frameTime;

	QueryPerformanceCounter(&currentTime);
	f64 accumulator = 0.0;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while (1)
	{
		QueryPerformanceCounter(&newTime);
 		frameTime = (f64)((newTime.QuadPart  / 1000) - (currentTime.QuadPart / 1000));
		currentTime = newTime;

		if(frameTime > 0.35)
			frameTime = 0.35;

		accumulator += frameTime;

		input();

		while(accumulator >= dt)
		{
			app.previousState = app.currentState;
			// update(t, dt);
			update(app.currentState, t, dt);
			t += dt;
			accumulator -= dt;
			printf("loop:\n");
		}

		const f64 alpha = accumulator / dt;
		printf("alpha: %.2f\n", alpha);

/*		
		app.previousState.position = {1.0f, 6.3f};
		app.previousState.velocity = 3.0f;
		app.currentState.position = {14.0, 8.7f};
		app.currentState.velocity = 0.14f;

		// testing operators for state + state, & state * scalar
		State temp = app.previousState + app.currentState;
		printf("pos: {%.3f, %.3f}\n", temp.position.x, temp.position.y);
		printf("vel: %.3f\n", temp.velocity);
		temp = temp * alpha;
		printf("pos: {%.3f, %.3f}\n", temp.position.x, temp.position.y);
		printf("vel: %.3f\n", temp.velocity);
*/
		State state = (app.currentState * alpha) + (app.previousState * ( 1.0 - alpha ));

		render(state);
		printf("Frame Rendered\n");

		Sleep(1);		// and breathe
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
