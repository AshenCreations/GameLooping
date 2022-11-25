#include "draw.h"

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
GPU_Image *load_image(char *filename)
{
	//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

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
GPU_Image* textureFromFont(TTF_Font *font, char *text, u8 style, SDL_Color color)
{
	TTF_SetFontStyle(font, style);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	GPU_Image *image = GPU_CopyImageFromSurface(surface);
	SDL_FreeSurface(surface);

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
