#include "common.h"

extern void init(void);
extern void cleanup(void);
extern void prepare_scene(void);
extern void present_scene(void);
extern void do_input(void);
extern void do_menu(void);
extern bool check_keypress(u8 keybind);
extern void do_event(u8 input);
extern void draw_atomic_test(void);
extern GPU_Image *load_image(char *filename);
extern void update_enemy(void);
extern void spawn_enemy(void);

App app;
