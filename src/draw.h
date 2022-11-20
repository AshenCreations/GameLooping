#include "common.h"

void prepare_scene(void);
void present_scene(void);
GPU_Image *load_texture(char *filename);
void do_screenshot(void);
void blit(GPU_Image *image, f32 x, f32 y);
void draw_circle_filled(f32 x, f32 y, f32 radius, SDL_Color color);
GPU_Image* textureFromFont(TTF_Font *font, char *text, s32 style, SDL_Color color);
void draw_atomic_test(void);
void draw_ui_component_rectangleF(GPU_Rect rect, SDL_Color color);
void draw_ui_component_rectangle(GPU_Rect rect, SDL_Color color);
void draw_ui_component_circle(f32 x, f32 y, f32 radius, SDL_Color color);
void draw_ui_molecule_radio(GPU_Rect rect, bool state);

extern void do_event(s32 event);

extern App app;
