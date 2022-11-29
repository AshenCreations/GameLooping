#include "common.h"

extern void init(void);
extern void cleanup(void);
extern GPU_Image *load_image(char *filename);
extern void do_input(void);
extern void update(void);
extern void render(GPU_Image *image);
extern s32 round_float2Int(float fNum);


App app;
