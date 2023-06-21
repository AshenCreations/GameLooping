#include "init.h"
#include "textures.h"
#include "sound.h"
#include "utils.h"

void init(void)
{
	// SDL inits
	init_SDL();

	// App inits
	init_screen();
	init_keybinds();
	init_sound();
	init_renderlayers();

	// SDL_ShowCursor(SDL_DISABLE);
}

void init2(void)
{
	init_player();
	init_enemies();
	init_waypoints();
	init_spawner();
}

void cleanup(void)
{
	Mix_FreeChunk(app.sounds.nope);
	Mix_FreeChunk(app.sounds.bruh);
	Mix_CloseAudio();

	FC_FreeFont(app.fcfont);

	GPU_FreeImage(app.screen.BG);
	GPU_FreeImage(app.screen.MG);
	GPU_FreeImage(app.screen.FG);

	Mix_Quit();
	TTF_Quit();
	GPU_Quit();
	SDL_Quit();
}

void init_SDL(void)
{
	// SDL init
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("Couldn't initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// window by SDL
	u32 windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS;
	SDL_Window *window = SDL_CreateWindow(WINDOW_TITLE,
										SDL_WINDOWPOS_UNDEFINED,
										SDL_WINDOWPOS_UNDEFINED,
										SCREEN_WIDTH, SCREEN_HEIGHT,
										windowFlags);
	if(!window)
	{
		printf("Failed to create window with SDL: %s\n", SDL_GetError());
		exit(1);
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	// init SDL_gpu
	u32 windowID = SDL_GetWindowID(window);
	GPU_SetInitWindow(windowID);
	GPU_WindowFlagEnum renderFlags = GPU_DEFAULT_INIT_FLAGS;
	// renderer by SDL_gpu
	app.screen.renderOutput = GPU_Init((u16)SCREEN_WIDTH, (u16)SCREEN_HEIGHT, renderFlags);
	if(!app.screen.renderOutput)
	{
		printf("Failed to create renderer with SDL_gpu: %s\n", SDL_GetError());
		exit(1);
	}

	//init SDL_ttf
	if(TTF_Init() < 0)
	{
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}
	// open font using SDL_fontcache
	app.fcfont = FC_CreateFont();
	FC_LoadFont(app.fcfont, FONT_PATH, FONT_SIZE, COLOR_WHITE, TTF_STYLE_NORMAL);

	// init SDL_mixer
	if(Mix_Init(MIX_INIT_MP3) == 0)
	{
		printf("SDL_mixer could not be initialized! SDL_mixer Error: %s\n", Mix_GetError());
		exit(2);
	}
	// open default audio device
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MAX_AUDIO_CHANNELS, 2048) < 0)
	{
		printf("SDL_mixer could not initialize the default audio device! SDL_mixer Error: %s\n", Mix_GetError());
		exit(2);
	}
}

void init_screen(void)
{
	// Checks current refresh rate & calculates the deltatime multiplier
	SDL_DisplayMode modeBuffer = {};
	SDL_GetCurrentDisplayMode(0, &modeBuffer);
	app.appHz = modeBuffer.refresh_rate;
	app.dtMulti = modeBuffer.refresh_rate / 60.0f;	// this line works in this project but not for opengl project

	// deltatime multiplier needed to modify speeds & other things... ???
	app.player.speed = PLAYER_MAX_SPEED / app.dtMulti;
	app.eSpawn.spawnedSpeed = ENEMY_BASE_SPEED / app.dtMulti;
	// more things ...
}

// load sounds & set volumes
// TODO: 1 channel for music, 6 channels for sfx, 1 channel for UI.
void init_sound(void)
{
	app.sounds.nope = load_sound(SOUNDPATH_NOPE);
	app.sounds.bruh = load_sound(SOUNDPATH_BRUH);
	Mix_Volume(-1, 50);
}

// default keybind values
void init_keybinds(void)
{
	app.keybind.escape = SDL_SCANCODE_ESCAPE;
	app.keybind.up = SDL_SCANCODE_W;
	app.keybind.down = SDL_SCANCODE_S;
	app.keybind.left = SDL_SCANCODE_A;
	app.keybind.right = SDL_SCANCODE_D;
	app.keybind.ctrl = SDL_SCANCODE_LCTRL;
	app.keybind.BGLayer = SDL_SCANCODE_1;
	app.keybind.MGLayer = SDL_SCANCODE_2;
	app.keybind.FGLayer = SDL_SCANCODE_3;
}

void init_player(void)
{
	app.playerSprite = load_image(IMAGEPATH_player);
	GPU_SetImageFilter(app.playerSprite, GPU_FILTER_NEAREST);
	app.player.collider = {{app.player.pos.x, app.player.pos.y,}, (float)app.playerSprite->w / 2};

	app.player.pos = {SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
	app.player.maxSpeed = PLAYER_MAX_SPEED;

	app.player.facing = true;
	app.player.hasTarget = false;
	app.player.minDistance = PLAYER_WAYPOINT_MIN_DISTANCE;
	app.player.damage = 51;
	app.player.damageCd = app.oneSecond / 2.0f;

	app.player.moveQueue.front = app.player.moveQueue.size = 0;
	app.player.moveQueue.rear = app.player.moveQueue.capacity - 1;
}

void init_enemies(void)
{
	app.enemySprite = load_image(IMAGEPATH_smiley);
	GPU_SetImageFilter(app.enemySprite, GPU_FILTER_NEAREST);
}
void init_waypoints(void)
{
	app.waypoint[0].pos = {100, 100};
	app.waypoint[1].pos = {SCREEN_WIDTH - 100, 100};
	app.waypoint[2].pos = {SCREEN_WIDTH - 100, SCREEN_HEIGHT - 100};
	app.waypoint[3].pos = {100, SCREEN_HEIGHT - 100};

	app.waypoint[0].name = "WP 0";
	app.waypoint[1].name = "WP 1";
	app.waypoint[2].name = "WP 2";
	app.waypoint[3].name = "WP 3";
}

// this should probably take param(s)
void init_spawner(void)
{
	app.eSpawn.pos = {400, 300};
    app.eSpawn.cooldown = app.oneSecond;
	app.eSpawn.maxSpawns = MAX_ENEMIES;
	app.eSpawn.targetWaypoint = app.waypoint[WAYPOINT_0].pos;
}

void init_renderlayers(void)
{
	app.screen.BG = GPU_CreateImage(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_FORMAT_RGBA);
	app.screen.MG = GPU_CreateImage(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_FORMAT_RGBA);
	app.screen.FG = GPU_CreateImage(SCREEN_WIDTH, SCREEN_HEIGHT, GPU_FORMAT_RGBA);

	app.grass = load_image(IMAGEPATH_grass);
}
