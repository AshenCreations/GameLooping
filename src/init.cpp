#include "init.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void init_SDL(void);
void init_SDL_ttf(void);
void cleanup(void);
void init_keybinds(void);
void init_spawner(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void init(void)
{
	// SDL inits
	init_SDL();
	init_SDL_ttf();

  	// open the font: will close at exit
	app.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if(app.font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	TTF_SetFontStyle(app.font, TTF_STYLE_NORMAL);

	// App inits
	SDL_ShowCursor(SDL_DISABLE);		// disable cursor

	init_keybinds();
	init_spawner();

	app.keypressCooldown = KEYPRESS_COOLDOWN;
	app.statsImage = NULL;
	app.smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.smiley, GPU_FILTER_NEAREST);
}

// inits SDL via SDL_gpu. much simpler than the normal window & renderer init using SDL
//TODO may need to use GPU_SetInitWindow & GPU_SetPreInitFlags
void init_SDL(void)
{
	app.renderTarget = GPU_Init((u16)SCREEN_WIDTH, (u16)SCREEN_HEIGHT, GPU_DEFAULT_INIT_FLAGS);
	if(!app.renderTarget)
	{
		printf("Failed to create renderer with SDL_gpu: %s\n", SDL_GetError());
		exit(1);
	}
}

// simple init for SDL_ttf
void init_SDL_ttf(void)
{
	if(TTF_Init() < 0)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
}

// do this when app exits
void cleanup(void)
{
	GPU_FreeTarget(app.renderTarget);
	TTF_CloseFont(app.font);

	TTF_Quit();
	GPU_Quit();
	SDL_Quit();
}

// default keybind values
void init_keybinds(void)
{
	app.keybind.printscreen = SDL_SCANCODE_F1;
	app.keybind.escape = SDL_SCANCODE_ESCAPE;
	app.keybind.up = SDL_SCANCODE_W;
	app.keybind.down = SDL_SCANCODE_S;
	app.keybind.left = SDL_SCANCODE_A;
	app.keybind.right = SDL_SCANCODE_D;
}

// this should probably take param(s)
void init_spawner(void)
{
	app.eSpawn.pos = WAYPOINT_1;
	app.eSpawn.cooldown = 150;
	app.eSpawn.maxSpawns = 1;
	app.eSpawn.numberSpawned = 0;
}
