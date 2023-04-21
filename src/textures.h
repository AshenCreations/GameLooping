#pragma once
#include "common.h"

GPU_Image* load_image(char *filename);
// GPU_Image* texture_from_font_wrapped(TTF_Font *font, char *text, SDL_Color color, u32 wrapLength);
// GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color);
// GPU_Image* texture_glyph(TTF_Font *font, char ch, SDL_Color color);

extern App app;
