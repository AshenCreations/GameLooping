#include "common.h"

void do_menu(void);
bool do_button(s32 index, GPU_Rect rect, u8 borderSize);
bool do_button_logic(s32 index, GPU_Rect mouseRect);
void do_button_border(GPU_Rect rect, u8 borderSize, SDL_Color color);
void draw_menu(GPU_Rect menuRect);

extern bool get_mouse_zone(GPU_Rect rect);
extern void do_event(u8 event);

extern App app;
