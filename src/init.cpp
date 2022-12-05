#include "init.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void init_SDL(void);
void init_SDLttf(void);
void cleanup(void);
void init_fonts(void);
void init_buttons(void);
void init_keybinds(void);
void init_spawner(void);
void init_player(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void init(void)
{
	// SDL inits
	init_SDL();
	init_SDLttf();

	// App inits
	SDL_ShowCursor(SDL_DISABLE);		// disable cursor

  	app.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if(app.font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());

	init_buttons();
	init_keybinds();
	init_spawner();
	init_player();

	app.enemyCounter = NULL;
	app.smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.smiley, GPU_FILTER_NEAREST);
}

// inits SDL via SDL_gpu
void init_SDL(void)
{
	app.renderTarget = GPU_Init((u16)SCREEN_WIDTH, (u16)SCREEN_HEIGHT, GPU_DEFAULT_INIT_FLAGS);
	if(!app.renderTarget)
	{
		printf("Failed to create renderer with SDL_gpu: %s\n", SDL_GetError());
		exit(1);
	}
}

void init_SDLttf(void)
{
	if(TTF_Init() == -1)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
}

// do this when app exits
void cleanup(void)
{
	GPU_FreeTarget(app.renderTarget);

	TTF_Quit();
	GPU_Quit();
	SDL_Quit();
}

// button data
void init_buttons(void)
{
	app.button[0].index = UI_BUTTON_QUITAPP;
	app.button[0].image = texture_from_font(app.font, "Quit", TTF_STYLE_NORMAL, COLOR_WHITE);
	// GPU_SaveImage(app.button[0].image, "ui_text_quit.png", GPU_FILE_PNG);
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
	app.eSpawn.pos = SPAWN_1;
	app.eSpawn.cooldown = 600;
	app.eSpawn.maxSpawns = 5000;
	app.eSpawn.numberSpawned = 0;
}

void init_player(void)
{
	app.player.pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
	app.player.dPos = {0, 0};
}
