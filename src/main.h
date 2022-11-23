#include "common.h"

extern GPU_Image* init(void);
extern void cleanup(void);
extern void prepare_scene(void);
extern void present_scene(void);
extern void do_input(void);
extern void do_menu(void);
extern bool check_keypress(u8 action, u8 keybind);
extern void do_event(u8 input);
extern void blit(GPU_Image *texture, f32 x, f32 y);
extern void draw_atomic_test(void);
extern GPU_Image *load_texture(char *filename);


App app;
