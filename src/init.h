#include "common.h"

void init_SDL(void);
void init_SDLttf(void);
void cleanup(void);
void init_fonts(void);
void init_buttons(TTF_Font *font);
void init_keybinds(void);

extern GPU_Image *load_image(char *filename);
extern GPU_Image* textureFromFont(TTF_Font *font, char *text, u8 style, SDL_Color colour);

extern App app;
