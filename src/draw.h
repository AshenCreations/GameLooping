#include "common.h"

void prepare_scene(void);
void present_scene(void);
GPU_Image *load_image(char *filename);
void do_screenshot(void);
GPU_Image* textureFromFont(TTF_Font *font, char *text, u8 style, SDL_Color color);
void draw_atomic_test(void);
void draw_ui_molecule_radio(GPU_Rect rect, bool state);

extern void do_event(s32 event);

extern App app;
