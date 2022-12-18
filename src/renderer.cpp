#include "renderer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void render(f64 alpha);
void prepare_scene(void);
void present_scene(void);
GPU_Image *load_image(char *filename);
GPU_Image* texture_from_font(TTF_Font *font, char *text, u8 style, SDL_Color color);
void draw_enemy(f64 alpha);
void draw_player(f64 alpha);
void draw_stats(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void render(f64 alpha)
{
	prepare_scene();

	draw_enemy(alpha);
	draw_player(alpha);
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

void draw_player(f64 alpha)
{
	GPU_Blit(app.playerSprite, NULL, app.renderTarget,
			app.player.pos.x,
			app.player.pos.y);
}

// onscreen text counter for enemyCount
void draw_stats(void)
{
	GPU_RectangleFilled2(app.renderTarget, {140, 500, 370, 170}, {0, 0, 0, 100});
	
	char textBuffer[150];
	memset(&textBuffer, 0, sizeof(textBuffer));

	snprintf(textBuffer, sizeof(textBuffer), "Refresh Rate: %uHz\ndelta time: %.3f\nplayer speed: %.2f\nplayer move vector: {%.2f, %.2f}\nenemies: %u/%u\n",
											app.appHz, app.dt,
											app.player.speed,
											app.player.vel.x, app.player.vel.y,
											app.enemyCount, app.eSpawn.maxSpawns);
	
	GPU_Image *statsImage = texture_from_font(app.font, textBuffer, TTF_STYLE_NORMAL, COLOR_WHITE);
	GPU_SetAnchor(statsImage, 0.0f, 0.0f);
	GPU_SetImageFilter(statsImage, GPU_FILTER_NEAREST);
	GPU_Blit(statsImage, NULL, app.renderTarget, 150, 500);
	GPU_FreeImage(statsImage);	// this must be freed after use
}
