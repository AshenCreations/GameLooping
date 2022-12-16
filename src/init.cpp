#include "init.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void init_SDL(void);
void init_SDL_ttf(void);
void cleanup(void);
void init_keybinds(void);
void init_spawner(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void init(State *state)
{
	// SDL inits
	init_SDL();
	init_SDL_ttf();

	// App inits
	// SDL_ShowCursor(SDL_DISABLE);

	init_keybinds();

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Refresh Rate ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// find refresh rate from desktop settings & modify dt & speed 
	// fuzzy refresh rate evaluation compensates for different monitor manufacturer implementation of refresh rates
	// 
	// TODO: this is not robust. It only checks for 3 common refresh rates on the main monitor (monitor 0)
	
	SDL_DisplayMode modeBuffer = {};
	SDL_GetDesktopDisplayMode(0, &modeBuffer);
	app.appHz = modeBuffer.refresh_rate;

	if(modeBuffer.refresh_rate >= 59 && modeBuffer.refresh_rate <= 61)
	{
		app.dtMulti = 1.0f;
	}
	
	if(modeBuffer.refresh_rate >= 74 && modeBuffer.refresh_rate <= 76)
	{
		app.dtMulti = 1.25f;
	}

	if(modeBuffer.refresh_rate >= 119 && modeBuffer.refresh_rate <= 121)
	{
		app.dtMulti = 2.0f;
	}

	if(modeBuffer.refresh_rate >= 143 && modeBuffer.refresh_rate <= 145)
	{
		app.dtMulti = 2.4f;
	}

	if(modeBuffer.refresh_rate >= 164 && modeBuffer.refresh_rate <= 166)
	{
		app.dtMulti = 2.75f;
	}

	state->player.speed = PLAYER_SPEED / app.dtMulti;
	// more things like enemy speed ...

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Refresh Rate ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

	// TODO: clean this up
	app.smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.smiley, GPU_FILTER_NEAREST);
	
	app.playerSprite = load_image(IMAGEPATH_player);
	GPU_SetImageFilter(app.playerSprite, GPU_FILTER_NEAREST);
	state->player.pos = {SCREEN_WIDTH / 2.0f , SCREEN_HEIGHT / 2.0f};

	app.waypoint[0] = {100, 100};
	app.waypoint[1] = {SCREEN_WIDTH - 100, 100};
	app.waypoint[2] = {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100};
	app.waypoint[3] = {100, SCREEN_HEIGHT - 100};
	
	init_spawner();
}

// init SDL using SDL_GPU
void init_SDL(void)
{
	// SDL window
	u32 windowFlags = SDL_WINDOW_OPENGL;
	SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										1600, 900,
										windowFlags);
	if(!window)
	{
		printf("Failed to create window with SDL: %s\n", SDL_GetError());
		exit(1);
	}

	// SDL_gpu renderer
	u32 windowID = SDL_GetWindowID(window);
	GPU_SetInitWindow(windowID);
	// GPU_WindowFlagEnum renderFlags = GPU_INIT_DISABLE_VSYNC;
	GPU_WindowFlagEnum renderFlags = GPU_DEFAULT_INIT_FLAGS;
	app.renderTarget = GPU_Init((u16)SCREEN_WIDTH, (u16)SCREEN_HEIGHT, renderFlags);
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
	
  	// open the font: will close at exit
	app.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if(app.font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	TTF_SetFontStyle(app.font, TTF_STYLE_NORMAL);
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
	app.eSpawn.pos = app.waypoint[0].pos;
	app.eSpawn.cooldown = 150;
	app.eSpawn.maxSpawns = 1;
	app.eSpawn.numberSpawned = 0;
}
