#include "init.h"

GPU_Image* init(void)
{
	// SDL inits
	init_SDL();
	init_SDLttf();

	// App inits
	GPU_Image *image = init_screen();

  	TTF_Font *font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
	if(font == NULL)
		printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());

	
	init_buttons(font);
	init_keybinds();

	printf("Init success...\n");

	return image;
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

// load background & set anchor to top left
GPU_Image* init_screen(void)
{
	GPU_Image *image = load_texture("img/startbg.png");
	GPU_SetAnchor(image, 0.0f, 0.0f);
	return image;
}

// button data
void init_buttons(TTF_Font *font)
{
	app.button[0].index = BUTTON_QUITAPP;
	app.button[0].texture = textureFromFont(font, "Quit", TTF_STYLE_NORMAL, COLOR_WHITE);
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
