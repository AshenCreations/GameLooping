#include "input.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void do_key_up(SDL_KeyboardEvent *event);
void do_key_down(SDL_KeyboardEvent *event);
void input(State *state);
void check_keys(State *state);
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
void input(State *state)
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

	check_keys(state);
}

void check_keys(State *state)
{
	if(is_pressed(app.keybind.escape))
		exit(0);

	// player movement
	app.currentState.player.vel = {0.0f, 0.0f};
	
	if(is_pressed(app.keybind.right))
		state->player.vel = state->player.vel + move_right();
	if(is_pressed(app.keybind.left))
		state->player.vel = state->player.vel + move_left();
	if(is_pressed(app.keybind.up))
		state->player.vel = state->player.vel + move_up();
	if(is_pressed(app.keybind.down))
		state->player.vel = state->player.vel + move_down();
	
	//diagonal player movement
	if(state->player.vel.x != 0 && state->player.vel.y != 0)
		state->player.vel = state->player.vel * INVERSE_ROOT_2;
}

// Checks if keybind has been pressed
bool is_pressed(u8 keybind)
{
	return (app.keyboard[keybind]) ? true:false;
}
