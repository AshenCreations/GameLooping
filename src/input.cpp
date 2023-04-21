#include "input.h"
#include "sound.h"

// Set app.keyboard[scancode] to 1
void do_key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keys[event->keysym.scancode].wasPressed = app.keys[event->keysym.scancode].keyPressed;
		app.keys[event->keysym.scancode].keyPressed = true;
	}
}

// Set app.keyboard[scancode] to 0
void do_key_up(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keys[event->keysym.scancode].wasPressed = app.keys[event->keysym.scancode].keyPressed;
		app.keys[event->keysym.scancode].keyPressed = false;
	}
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
	Vec2 mousePos = {(float)app.mouse.pos.x, (float)app.mouse.pos.y};

	// zero player velocity for when no keys pressed
	app.player.vel = {0.0f, 0.0f};

	// Escape exits
	if(get_keystate(app.keybind.escape) == KEY_PRESSED)
	{
		quit_app();
	}

	// changed to turn off layers by keypresses
	app.screenState = STATE_BGLAYER | STATE_MGLAYER | STATE_FGLAYER;

	if(get_keystate(app.keybind.BGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 1);
	if(get_keystate(app.keybind.MGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 2);
	if(get_keystate(app.keybind.FGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 3);


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
	if(is_pressed(app.keybind.ctrl) && (app.mouse.buttons == SDL_BUTTON_LEFT && !app.mouse.wasButtons))
	{
		Vec2 tPos = app.player.moveQueue.queue_rear();
		Vec2 tMPos = {(float)app.mouse.pos.x, (float)app.mouse.pos.y};
		if(!point_in_circle(tMPos, {tPos, 40.0f}))
		{
			app.player.moveQueue.enqueue(mousePos);
			// set targetPos to front of queue
			app.player.targetPos = app.player.moveQueue.queue_front();
			app.player.hasTarget = true;
		}
	}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^ Movement Keys ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	int key = get_keystate(app.keybind.right);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_right();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.left);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_left();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.up);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_up();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.down);
	if(key == KEY_PRESSED || key == KEY_HELD)
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
bool is_pressed(int keybind)
{
	return (app.keys[keybind].keyPressed) ? true:false;
}

bool was_pressed(int keybind)
{
	return (app.keys[keybind].wasPressed) ? true:false;
}

int get_keystate(int keybind)
{
	if(!was_pressed(keybind) && is_pressed(keybind))
		return KEY_PRESSED;
	if(was_pressed(keybind) && !is_pressed(keybind))
		return KEY_RELEASED;
	if(was_pressed(keybind) && is_pressed(keybind))
		return KEY_HELD;

	return KEY_NOTPRESSED;
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

void quit_app(void)
{
	exit(0);
}
