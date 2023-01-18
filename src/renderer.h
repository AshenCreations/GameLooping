#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern GPU_Image* texture_from_font_wrapped(TTF_Font *font, char *text, SDL_Color color, u32 wrapLength);
extern GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color);
extern f32 check_distance(Vec2 a, Vec2 b);


extern App app;

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^