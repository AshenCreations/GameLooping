#include "draw.h"

// Clears the window to RGB
void prepare_scene(void)
{
	GPU_ClearRGB(app.renderTarget, 0, 0, 0);
}

// show the window
void present_scene(void)
{
	GPU_Flip(app.renderTarget);
}

// load texture
GPU_Image *load_texture(char *filename)
{
	//SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	GPU_Image *texture = GPU_LoadImage(filename);
	if (!texture)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Failed to load %s. Check path. Exiting app", filename);
		exit(1);
	}

	return texture;
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

// place image at x, y
void blit(GPU_Image *image, f32 x, f32 y)
{
	GPU_Blit(image, NULL, app.renderTarget, x, y);
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

	rect.x = 1400.0;
	rect.y = 200.0;
	rect.w = rect.h = 20;
	
	draw_ui_molecule_radio(rect, state = 0);
	rect.y += 50;
	draw_ui_molecule_radio(rect, state = 1);
}

void draw_ui_component_rectangleF(GPU_Rect rect, SDL_Color color)
{
	GPU_RectangleFilled2(app.renderTarget, rect, color);
}

void draw_ui_component_rectangle(GPU_Rect rect, SDL_Color color)
{
	GPU_Rectangle2(app.renderTarget, rect, color);
}

void draw_ui_component_circle(GPU_Rect rect, SDL_Color color)
{
	f32 radius = rect.h / 2;
	GPU_CircleFilled(app.renderTarget, rect.x, rect.y, radius, color);
}

void draw_ui_molecule_radio(GPU_Rect rect, bool state)
{
	SDL_Color color = COLOR_RADIO_GREY;

	if(state)
		color = COLOR_RADIO_BLUE;
	
	draw_ui_component_rectangleF(rect, color);

	rect.y += rect.h / 2;
	draw_ui_component_circle(rect, color);
	rect.x += rect.w;
	draw_ui_component_circle(rect, color);

	rect.h -= 4;
	if(state)
	{
		color = COLOR_RADIO_BLUE2;
	}
	else
	{
		rect.x -= rect.w;		
		color = COLOR_RADIO_GREY2;
	}
	draw_ui_component_circle(rect, color);
}
