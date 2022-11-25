#include "common.h"

void do_menu(void);
bool do_button(s32 index, GPU_Rect rect, u8 bsize);
bool do_button_logic(s32 index, GPU_Rect mouseRect);
void do_button_border(GPU_Rect rect, u8 size, SDL_Color color);
void draw_menu(GPU_Rect menuRect);

extern bool get_mouse_zone(GPU_Rect rect);
extern void blit(GPU_Image *texture, f32 x, f32 y);
extern void do_event(u8 event);


extern App app;
