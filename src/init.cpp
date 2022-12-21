#include "init.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void init_SDL(void);
void init_screen(void);
void cleanup(void);
void init_keybinds(void);
void init_spawner(void);
void init_sound(void);
void init_player(void);
void init_enemies(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void init(void)
{
	// SDL inits
	init_SDL();

	// App inits
	init_screen();
	init_keybinds();
	init_sound();

	init_player();
	init_enemies();
	init_spawner();

	app.waypoint[0].pos = WAYPOINT_0;
	app.waypoint[1].pos = WAYPOINT_1;
	app.waypoint[2].pos = WAYPOINT_2;
	app.waypoint[3].pos = WAYPOINT_3;
	
	
	// SDL_ShowCursor(SDL_DISABLE);
}

// init SDL
void init_SDL(void)
{
	// SDL init
	if(SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// window
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

	// init SDL_gpu
	u32 windowID = SDL_GetWindowID(window);
	GPU_SetInitWindow(windowID);
	GPU_WindowFlagEnum renderFlags = GPU_DEFAULT_INIT_FLAGS;
	// renderer
	app.renderTarget = GPU_Init((u16)SCREEN_WIDTH, (u16)SCREEN_HEIGHT, renderFlags);
	if(!app.renderTarget)
	{
		printf("Failed to create renderer with SDL_gpu: %s\n", SDL_GetError());
		exit(1);
	}

	// simple init for SDL_ttf
	if(TTF_Init() < 0)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	// open the font
	app.font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if(app.font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
	TTF_SetFontStyle(app.font, TTF_STYLE_NORMAL);

	// init SDL_mixer
	if(Mix_Init(MIX_INIT_MP3) == 0)
	{
		printf("SDL_mixer could not be initialized! SDL_mixer Error: %s\n", Mix_GetError());
		exit(2);
	}
	// open default audio device
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize the default audio device! SDL_mixer Error: %s\n", Mix_GetError());
		exit(2);
	}
}

// refresh rate stuff
void init_screen(void)
{
	// find refresh rate from desktop settings & modify dt & speed 
	// fuzzy refresh rate evaluation compensates for different monitor manufacturer implementation of refresh rates
	// 
	// TODO: this is not robust. It only checks for 5 common refresh rates on displayIndex 0 (main monitor)
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

	app.player.speed = PLAYER_SPEED / app.dtMulti;
	app.eSpawn.spawnedSpeed = ENEMY_SPEED / app.dtMulti;
	// more things ...
}

// do this when app exits
void cleanup(void)
{
	Mix_FreeChunk(app.sounds.nope);
	Mix_FreeChunk(app.sounds.bruh);
	Mix_CloseAudio();
	TTF_CloseFont(app.font);
	GPU_FreeTarget(app.renderTarget);

	Mix_Quit();
	TTF_Quit();
	GPU_Quit();
	SDL_Quit();
}

// default keybind values
void init_keybinds(void)
{
	// app.keybind.printscreen = SDL_SCANCODE_F1;
	app.keybind.escape = SDL_SCANCODE_ESCAPE;
	app.keybind.up = SDL_SCANCODE_W;
	app.keybind.down = SDL_SCANCODE_S;
	app.keybind.left = SDL_SCANCODE_A;
	app.keybind.right = SDL_SCANCODE_D;
	app.keybind.space = SDL_SCANCODE_SPACE;
}

// this should probably take param(s)
void init_spawner(void)
{
	app.eSpawn.pos = SPAWN_POINT;
	app.eSpawn.cooldown = 150;
	app.eSpawn.maxSpawns = 30;
	app.eSpawn.numberSpawned = 0;
}

// load sounds & set volumes
void init_sound(void)
{
    app.sounds.nope = load_sound(SOUNDPATH_NOPE);
	app.sounds.bruh = load_sound(SOUNDPATH_BRUH);
	Mix_Volume(-1, 20);
}

void init_player(void)
{
	app.playerSprite = load_image(IMAGEPATH_player);
	GPU_SetImageFilter(app.playerSprite, GPU_FILTER_NEAREST);
	
	app.player.pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};

	app.player.facing = true;
}

void init_enemies(void)
{
	app.enemySprite = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.enemySprite, GPU_FILTER_NEAREST);
}
