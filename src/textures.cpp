#include "textures.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

GPU_Image* load_image(char *filename);
GPU_Image* texture_from_font_wrapped(TTF_Font *font, char *text, SDL_Color color, u32 wrapLength);
GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// load texture
GPU_Image* load_image(char *filename)
{
	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	GPU_Image *image = GPU_LoadImage(filename);
	if (!image)
	{
		SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Failed to load %s. Check path. Exiting app", filename);
		exit(1);
	}

	return image;
}

// Creates texture from TTF font text
GPU_Image* texture_from_font_wrapped(TTF_Font *font, char *text, SDL_Color color, u32 wrapLength)
{
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, color, wrapLength);
	GPU_Image *temp = GPU_CopyImageFromSurface(surface);
	SDL_FreeSurface(surface);
	return temp;
}

GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	GPU_Image *temp = GPU_CopyImageFromSurface(surface);
	SDL_FreeSurface(surface);
	return temp;
}
