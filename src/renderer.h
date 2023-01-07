#include "common.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
extern bool queue_is_empty(Queue* queue);
extern GPU_Image* texture_from_font_wrapped(TTF_Font *font, char *text, SDL_Color color, u32 wrapLength);
extern GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color);

extern App app;
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^