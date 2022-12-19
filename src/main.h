#include "common.h"
#include <Windows.h>


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

extern void init(void);
extern void cleanup(void);
extern GPU_Image *load_image(char *filename);
extern void input(void);
extern void update(void);
extern void render(f64 alpha);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END EXTERNAL Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


App app;
