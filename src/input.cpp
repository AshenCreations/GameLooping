#include "input.h"

// Store old keypress then set keyboard.keys[scancode] to 1 or 0
void do_key_down(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0 && event->keysym.scancode < MAX_KEYBOARD_KEYS)
	{
		app.keys[event->keysym.scancode].wasPressed = app.keys[event->keysym.scancode].keyPressed;
		app.keys[event->keysym.scancode].keyPressed = true;
	}
}
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

	check_input();
}

//handle player input
void check_input(void)
{
	Vec2 mousePos = {(float)app.mouse.pos.x, (float)app.mouse.pos.y};
	Vec2 accel = app.player.accel;
	app.player.vel = {0.0f, 0.0f};

	if(get_keystate(app.keybind.escape) == KEY_PRESSED)
	{
		quit_app();
	}

	// set all 3 layers to SHOW
	app.screenState = STATE_BGLAYER | STATE_MGLAYER | STATE_FGLAYER;

	// HIDE layer if key held
	if(get_keystate(app.keybind.BGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 1);
	if(get_keystate(app.keybind.MGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 2);
	if(get_keystate(app.keybind.FGLayer) == KEY_PRESSED)
		app.screenState = clearBit(app.screenState, 3);

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
		Vec2 tempPos = app.player.moveQueue.queue_rear();
		Vec2 tempMPos = {(float)app.mouse.pos.x, (float)app.mouse.pos.y};
		if(!point_in_circle(tempMPos, {tempPos, 40.0f}))
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
		accel = move_right();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.left);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_left();
		accel = move_left();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.up);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_up();
		accel = move_up();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	key = get_keystate(app.keybind.down);
	if(key == KEY_PRESSED || key == KEY_HELD)
	{
		app.player.vel += move_down();
		accel = move_down();
		app.player.hasTarget = false;
		app.player.moveQueue.reset_queue();
	}

	// app.player.accel += accel;

	//diagonal player movement
	if(app.player.vel.x != 0 && app.player.vel.y != 0)
		app.player.vel = app.player.vel * INVERSE_ROOT_2;
	
	// cap player velocity
	// app.player.vel.x = __min(app.player.vel.x, app.player.maxSpeed);
	// app.player.vel.y = __min(app.player.vel.y, app.player.maxSpeed);
}

// check keystate from is_pressed and was_pressed
int get_keystate(int keybind)
{
	if(!was_pressed(keybind) && !is_pressed(keybind))
		return KEY_NOTPRESSED;
	if(!was_pressed(keybind) && is_pressed(keybind))
		return KEY_PRESSED;
	if(was_pressed(keybind) && is_pressed(keybind))
		return KEY_HELD;
	if(was_pressed(keybind) && !is_pressed(keybind))
		return KEY_RELEASED;
}
bool is_pressed(int keybind)
{
	return (app.keys[keybind].keyPressed) ? true:false;
}
bool was_pressed(int keybind)
{
	return (app.keys[keybind].wasPressed) ? true:false;
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
