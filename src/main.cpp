#include "main.h"

// windows entry point: since SDL is platform agnostic most tutorials don't show this,
// then people have problems running the .exe from icon or even trying to include <windows.h>
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	// Init before mainloop starts, some inits are default settings
	init();						// init() could call the platform layer(if i had one) 
	atexit(cleanup);			

	timeBeginPeriod(1);					// set system sleep granularity to 1ms: winmm.lib
	LARGE_INTEGER previous, current;
	f64 elapsed, lag = 0.0;
	QueryPerformanceCounter(&previous);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// while loop just calls in order input, update, render. Uses QueryPerformanceCounter to time the loop in microseconds,
	// which we convert to milliseconds when we want to use it. It has some printf logging for timing visualisation.
	
	// As the amount of work done & thus the time taken grows in update(), the value of MS_PER_UPDATE will need to be tweaked.
	// At all times MS_PER_UPDATE must be greater than the time spent in update(), on the slowest machine you are targetting

	while (1)
	{
		QueryPerformanceCounter(&current);		// in microseconds
		elapsed = (f64)(current.QuadPart - previous.QuadPart);
		previous = current;
		lag += elapsed / 1000.0;		// divide by 1000 to convert to ms

		input();

		// this loop reduces lag by MS_PER_UPDATE each iteration & leaves it < MS_PER_UPDATE
		// so that it may be normalised later when divided by MS_PER_UPDATE
		printf("lag before update %.4f\n", lag);

		int count = 0;					// counts the number of updates in each iteration of the gameloop
		while(lag >= MS_PER_UPDATE)		// loop until lag < MS_PER_UPDATE
		{
			update();
			lag -= MS_PER_UPDATE;
			count++;
			printf("count is %d, lag = %.4f\n",count, lag);	// shows effect of the iterative value reduction
		}
		
		// here lag is less then MS_PER_UPDATE, so we can divide by MS_PER_UPDATE to normalize (0 to 1)
		lag /= MS_PER_UPDATE;
		printf("normalised lag is %.4f\n", lag);
		render(lag);
		printf("Frame Rendered\n");		// shows how many updateframes there are between renderframes

		Sleep(1);		// and breathe
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
