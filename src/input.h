#pragma once
#include "common.h"
#include "utils.h"

void do_key_up(SDL_KeyboardEvent *event);
void do_key_down(SDL_KeyboardEvent *event);
void input(void);
void check_keys(void);
int get_keystate(int keybind);
bool is_pressed(int keybind);
bool was_pressed(int keybind);

void quit_app(void);
Vec2 move_up(void);
Vec2 move_down(void);
Vec2 move_left(void);
Vec2 move_right(void);
Vec2 move_stop(void);

enum KeypressState
{
	KEY_NOTPRESSED,
	KEY_PRESSED,
	KEY_RELEASED,
	KEY_HELD
};


extern App app;
