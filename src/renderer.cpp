#include "renderer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void render(f64 alpha);
void prepare_scene(void);
void present_scene(void);
GPU_Image *load_image(char *filename);
GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color color);
void draw_enemy(f64 alpha);
void draw_stats(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

//! Takes normalised frameLag value which needs added to drawing
//! operations involving entities which update position in update()
// so does render() need knowledge of gameobjects and thier velocities ???
void render(f64 alpha)
{
	prepare_scene();

	draw_enemy(alpha);

	snprintf(app.statsText, sizeof(app.statsText), "Enemies: %u / 10000", app.enemyCount);
	draw_stats();

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

// Creates texture from TTF font text, free the image returned before generating another
GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(app.font, text, color, 600);
	if(surface == NULL)
	{
		printf("surface not created, exiting\n");
		exit(2);		
	}
	GPU_Image *temp = GPU_CopyImageFromSurface(surface);

	if(temp == NULL)
	{
		printf("surface not copied to image, exiting\n");
		exit(2);
	}
	SDL_FreeSurface(surface);
	return temp;
}

// blit enemies
void draw_enemy(f64 alpha)
{
	for(int i = 0; i < app.enemyCount; i++)
	{
		if(app.enemy[i].alive)
		{
			GPU_Blit(app.smiley, NULL, app.renderTarget,
					app.enemy[i].pos.x,
					app.enemy[i].pos.y);
		}
	}
}

// onscreen text counter for enemyCount
void draw_stats(void)
{
	app.statsImage = texture_from_font(app.font, app.statsText, TTF_STYLE_NORMAL, COLOR_WHITE);
	GPU_SetAnchor(app.statsImage, 0.0f, 0.0f);
	GPU_SetImageFilter(app.statsImage, GPU_FILTER_NEAREST);
	GPU_Blit(app.statsImage, NULL, app.renderTarget, 200, 500);
	GPU_FreeImage(app.statsImage);	// this must be freed after use
}
