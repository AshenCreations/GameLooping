#include "common.h"

void do_key_up(SDL_KeyboardEvent *event);
void do_key_down(SDL_KeyboardEvent *event);
void do_input(void);
bool check_keypress(u8 keybind);

extern void do_event(u8 input);

extern App app;
