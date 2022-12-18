#include "init.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void init_SDL(void);
void init_screen(void);
void cleanup(void);
void init_keybinds(void);
void init_spawner(void);
void init_sound(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void init(void)
{
	// SDL inits
	init_SDL();

	// App inits
	init_screen();
	init_keybinds();
	init_sound();

	// TODO: clean this up
	app.waypoint[0] = {100, 100};
	app.waypoint[1] = {SCREEN_WIDTH - 100, 100};
	app.waypoint[2] = {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100};
	app.waypoint[3] = {100, SCREEN_HEIGHT - 100};
	init_spawner();

	// SDL_ShowCursor(SDL_DISABLE);
	app.smiley = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.smiley, GPU_FILTER_NEAREST);
	
	app.playerSprite = load_image(IMAGEPATH_player);
	GPU_SetImageFilter(app.playerSprite, GPU_FILTER_NEAREST);
	app.player.pos = {SCREEN_WIDTH / 2.0f , SCREEN_HEIGHT / 2.0f};

}

// init SDL
void init_SDL(void)
{
	// SDL window
	if(SDL_Init(SDL_INIT_VIDEO||SDL_INIT_AUDIO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	
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

	// simple init for SDL_ttf
	if(TTF_Init() < 0)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

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

	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize the default audio device! SDL_mixer Error: %s\n", Mix_GetError());
		exit(2);
	}
}

void init_screen(void)
{
	// find refresh rate from desktop settings & modify dt & speed 
	// fuzzy refresh rate evaluation compensates for different monitor manufacturer implementation of refresh rates
	// 
	// TODO: this is not robust. It only checks for 5 common refresh rates on the main monitor (monitor 0)
	
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
	// more things like enemy speed ...
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
	app.keybind.printscreen = SDL_SCANCODE_F1;
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
	app.eSpawn.pos = app.waypoint[0].pos;
	app.eSpawn.cooldown = 150;
	app.eSpawn.maxSpawns = 30;
	app.eSpawn.numberSpawned = 0;
	app.eSpawn.spawnedSpeed = ENEMY_SPEED / app.dtMulti;
}

void init_sound(void)
{
    app.sounds.nope = load_sound(SOUNDPATH_NOPE);
	app.sounds.bruh = load_sound(SOUNDPATH_BRUH);
	Mix_Volume(-1, 15);
}
