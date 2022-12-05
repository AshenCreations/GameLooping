#include "input.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void do_key_up(SDL_KeyboardEvent *event);
void do_key_down(SDL_KeyboardEvent *event);
void do_input(void);
bool is_pressed(u8 keybind);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


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

// Get keyboard & mouse input via SDL Events
void do_input(void)
{
	SDL_Event event;
	
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				exit(0);
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
	app.mouse.buttons = SDL_GetMouseState(&app.mouse.pos.x, &app.mouse.pos.y);	// get mouse button pos & button state

	//TODO checking keys here ok for now ??
	if(is_pressed(app.keybind.escape))
		exit(0);

	if(is_pressed(app.keybind.printscreen))
		do_screenshot();;

	if(is_pressed(app.keybind.up))
		app.command.execute = move_up;
	if(is_pressed(app.keybind.down))
		app.command.execute = move_down;
	if(is_pressed(app.keybind.left))
		app.command.execute = move_left;
	if(is_pressed(app.keybind.right))
		app.command.execute = move_right;
}

// Checks if keybind has been pressed
bool is_pressed(u8 keybind)
{
	return (app.keyboard[keybind]) ? true:false;
}
