#include "common.h"

void do_menu(void);
bool do_button(s32 index, GPU_Rect rect, s32 bsize);
bool do_button_logic(s32 index, GPU_Rect mouseRect);
void do_button_border(GPU_Rect rect, s32 size, SDL_Color color);
void draw_menu(GPU_Rect menuRect);

extern bool get_mouse_zone(GPU_Rect rect);
extern void blit(GPU_Image *texture, f32 x, f32 y);
extern void do_event(s32 event);
extern void draw_ui_component_rectangleF(GPU_Rect rect, SDL_Color color);
extern void draw_ui_component_rectangle(GPU_Rect rect, SDL_Color color);

extern App app;
