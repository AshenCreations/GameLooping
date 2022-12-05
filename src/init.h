#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern GPU_Image *load_image(char *filename);
extern GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color colour);

extern App app;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^