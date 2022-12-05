#include "main.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	memset(&app, 0, sizeof(App));

	// Init before mainloop starts, some inits are default settings
	init();
	atexit(cleanup);

	timeBeginPeriod(1);		// set system sleep granularity to 1ms
	LARGE_INTEGER previous, current;
	f64 elapsed, lag = 0.0, totalLag = 0.0;
	QueryPerformanceCounter(&previous);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop START ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	while (1)
	{
		QueryPerformanceCounter(&current);		// in microseconds
		elapsed = (f64)(current.QuadPart - previous.QuadPart);
		previous = current;
		lag += elapsed / 1000.0;	// divide by 1000 to convert to ms

		do_input();

		// this loop reduces lag by MS_PER_UPDATE each iteration & leaves it < MS_PER_UPDATE
		// so that it may be normalised later when divided by MS_PER_UPDATE
		printf("lag before update %.4f\n", lag);

		int count = 0;
		while(lag >= MS_PER_UPDATE)			// loop until lag < MS_PER_UPDATE
		{
			update();
			lag -= MS_PER_UPDATE;
			count++;
			printf("count is %d, lag = %.4f\n",count, lag);	// printed to visualise the interative value reduction
		}

		lag /= MS_PER_UPDATE;						// here lag is less then MS_PER_UPDATE
													//so we can divide by MS_PER_UPDATE to normalize (0->1)
		printf("normalised lag is %.4f\n", lag);
		render(lag);
		printf("Frame Rendered\n");		// printed so we can see how many updateframes there are between renderframes

		Sleep(1);		// and breathe
	}
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Gameloop END ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
}
