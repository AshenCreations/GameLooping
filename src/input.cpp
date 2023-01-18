#include "input.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void do_key_up(SDL_KeyboardEvent *event);
void do_key_down(SDL_KeyboardEvent *event);
void input(void);
void check_keys(void);
bool is_pressed(u16 keybind);

Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
Vec2 move_stop(void);

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
void input(void)
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
	app.mouse.wasButtons = app.mouse.buttons;
	app.mouse.buttons = SDL_GetMouseState(&app.mouse.pos.x, &app.mouse.pos.y);	// get mouse button pos & button state

	check_keys();
}

// checks player input
void check_keys(void)
{
	Vec2 mousePos = {(f32)app.mouse.pos.x, (f32)app.mouse.pos.y};
	
	// zero player velocity for when no keys pressed
	app.player.vel = {0.0f, 0.0f};

	// Escape exits
	if(is_pressed(app.keybind.escape))
	{
		exit(0);
	}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^ mouse clicks ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// set target pos to mouse pos by leftclick
	if(app.mouse.buttons == SDL_BUTTON_LEFT && !is_pressed(app.keybind.ctrl))
	{
		app.player.targetPos = mousePos;
		app.player.hasTarget = true;
		// let a single move order empty the movement queue
		app.player.moveQueue.reset_queue();
	}

	// ctrl + leftclick to add waypoint to player move queue
	if(is_pressed(app.keybind.ctrl) && app.mouse.buttons == SDL_BUTTON_LEFT && app.mouse.wasButtons == 0)
	{
		app.player.moveQueue.enqueue(mousePos);
		// set targetPos to front of queue
		app.player.targetPos = app.player.moveQueue.queue_front();
		app.player.hasTarget = true;
	}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^ Movement Keys ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	if(is_pressed(app.keybind.right))
	{
		app.player.vel += move_right();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}
	if(is_pressed(app.keybind.left))
	{
		app.player.vel += move_left();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}
	if(is_pressed(app.keybind.up))
	{
		app.player.vel += move_up();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}
	if(is_pressed(app.keybind.down))
	{
		app.player.vel += move_down();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}
	
	//diagonal player movement
	if(app.player.vel.x != 0 && app.player.vel.y != 0)
	{
		app.player.vel = app.player.vel * INVERSE_ROOT_2;
	}
}

// Checks if keybind has been pressed
bool is_pressed(u16 keybind)
{
	return (app.keyboard[keybind]) ? true:false;
}

//^^^^^^^^^^^^^^^^^ basic move instructions ^^^^^^^^^^^^^^^^^^^^^^^^^

Vec2 move_up(void)
{
    return {0, -1};
}

Vec2 move_down(void)
{
    return {0, 1};
}

Vec2 move_left(void)
{
    return {-1, 0};
}

Vec2 move_right(void)
{
    return {1, 0};
}

Vec2 move_stop(void)
{
    return {0, 0};
}
