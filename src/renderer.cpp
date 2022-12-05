#include "renderer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void render(f64 lag);
void prepare_scene(void);
void present_scene(void);
GPU_Image *load_image(char *filename);
void do_screenshot(void);
GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color color);
void draw_atomic_test(void);
void draw_ui_molecule_radio(GPU_Rect rect, bool state);
void draw_enemy(GPU_Image *image, f64 lag);
void draw_enemy_count(char* text);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


void render(f64 lag)
{
	prepare_scene();

	// do_menu();
	draw_enemy(app.smiley, lag);

    sprintf(app.enemyCountText, "Enemies: %d", app.enemyCount);
	draw_enemy_count(app.enemyCountText);

	present_scene();
}

// Clears the window to RGB
void prepare_scene(void)
{
	GPU_ClearRGB(app.renderTarget, 35, 0, 35);
}

// show the window
void present_scene(void)
{
	GPU_Flip(app.renderTarget);
}

// load texture
GPU_Image* load_image(char *filename)
{
	// SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	GPU_Image *image = GPU_LoadImage(filename);
	if (!image)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Failed to load %s. Check path. Exiting app", filename);
		exit(1);
	}

	return image;
}

// use F1 to take a screenshot
void do_screenshot(void)
{
	GPU_Image *screenshot = GPU_CopyImageFromTarget(app.renderTarget);
	bool success = GPU_SaveImage(screenshot, "screeny.png", GPU_FILE_PNG);

	if(!success)
		GPU_LogError("screenshot not saved\n");
	else
		printf("Screenshot saved\n");

	GPU_FreeImage(screenshot);
}

// Creates texture from TTF font text
GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color color)
{
	TTF_SetFontStyle(font, style);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	GPU_Image *image = GPU_CopyImageFromSurface(surface);
	SDL_FreeSurface(surface);
	if(image == NULL)
		{
			printf("surface not copied to image, exiting\n");
			exit(2);
		}

	return image;
}

void draw_atomic_test(void)
{
	GPU_Rect rect;
	bool state;

	rect.x = SCREEN_WIDTH / 2;
	rect.y = (SCREEN_HEIGHT / 2);
	rect.w = rect.h = 20;
	
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL_ADD_ALPHA);
	draw_ui_molecule_radio(rect, state = 0);
	rect.y += 40;
	draw_ui_molecule_radio(rect, state = 1);
	GPU_SetShapeBlendMode(GPU_BLEND_NORMAL);
}

void draw_ui_molecule_radio(GPU_Rect rect, bool state)
{
	SDL_Color color = COLOR_RADIO_GREY;

	if(state)
		color = COLOR_RADIO_BLUE;
	
	GPU_RectangleFilled2(app.renderTarget, rect, color);

	f32 radius = rect.h / 2;
	rect.y += radius;
	GPU_CircleFilled(app.renderTarget, rect.x, rect.y, radius, color);
	rect.x += rect.w;
	GPU_CircleFilled(app.renderTarget, rect.x, rect.y, radius, color);

	radius -= 2;
	if(state)
	{
		color = COLOR_RADIO_BLUE2;
	}
	else
	{
		rect.x -= rect.w;		
		color = COLOR_RADIO_GREY2;
	}
	GPU_CircleFilled(app.renderTarget, rect.x, rect.y, radius, color);
}

void draw_enemy(GPU_Image *image, f64 lag)
{
	for(int i = 0; i < app.enemyCount; i++)
	{
		if(app.enemy[i].alive)
		{
			app.enemy[i].pos.x += app.enemy[i].dPos.x * lag;	// change pos by dPos * lag
			GPU_Blit(image, NULL, app.renderTarget, app.enemy[i].pos.x, app.enemy[i].pos.y);
		}
	}
}

void draw_enemy_count(char* text)
{
	app.enemyCounter = texture_from_font(app.font, text, TTF_STYLE_NORMAL, COLOR_WHITE);
	GPU_SetAnchor(app.enemyCounter, 0.0f, 0.0f);
	GPU_SetImageFilter(app.enemyCounter, GPU_FILTER_NEAREST);
	GPU_Blit(app.enemyCounter, NULL, app.renderTarget, 200, 500);
}
