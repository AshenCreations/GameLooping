#include "input.h"

// Set app.keyboard[scancode] to 1
void do_key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
		app.keyboard[event->keysym.scancode] = 1;
}

// Set app.keyboard[scancode] to 0
void do_key_up(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
		app.keyboard[event->keysym.scancode] = 0;
}

// Get keyboard & mouse input
void do_input(void)
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				do_event(EVENT_QUIT);
				break;
				
			case SDL_KEYDOWN:
				do_key_down(&event.key);
				break;
				
			case SDL_KEYUP:
				do_key_up(&event.key);
				break;

			default:
				break;
		}
	}
	app.mouse.buttons = SDL_GetMouseState(&app.mouse.pos.x, &app.mouse.pos.y);	// get mouse button state, x & y
}

// Returns if action carried out or not
bool check_keypress(u8 keybind)
{
	return (app.keyboard[keybind]) ? true:false;
}
