#include "renderer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
void render();
void prepare_scene(void);
void present_scene(void);
GPU_Image *load_image(char *filename);
GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color);
void draw_enemy(void);
void draw_player(void);
void draw_stats(void);
void label_waypoints(void);
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ END Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void render()
{
	prepare_scene();

	draw_enemy();
	draw_player();
	draw_stats();
	label_waypoints();

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
GPU_Image* texture_from_font(TTF_Font *font, char *text, SDL_Color color)
{
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, color, 600);
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

// render the  enemies
void draw_enemy(void)
{
	for(u32 i = 0; i < app.enemyCount; i++)
	{
		if(app.enemy[i].alive)
		{
			app.enemy[i].renderRect.x = app.enemy[i].pos.x - app.enemySprite->w / 2.0f;
			app.enemy[i].renderRect.y = app.enemy[i].pos.y - app.enemySprite->h / 2.0f;
			app.enemy[i].renderRect.w = app.enemySprite->w;
			app.enemy[i].renderRect.h = app.enemySprite->h;

			GPU_FlipEnum flipflag = 0;
			if(app.enemy[i].facing)
				flipflag = GPU_FLIP_NONE;
			if(!app.enemy[i].facing)
				flipflag = GPU_FLIP_HORIZONTAL;

			GPU_BlitRectX(app.enemySprite, NULL, app.renderTarget, &app.enemy[i].renderRect,
				0.0f, app.enemySprite->w / 2.0f, app.enemySprite->h / 2.0f, flipflag);
		}
	}
}

// render the player
void draw_player(void)
{
	// TODO make_rect(sprite); get rid of some globals
	app.player.renderRect.x = app.player.pos.x - app.playerSprite->w / 2.0f;
	app.player.renderRect.y = app.player.pos.y - app.playerSprite->h / 2.0f;
	app.player.renderRect.w = app.playerSprite->w;
	app.player.renderRect.h = app.playerSprite->h;
	
	GPU_FlipEnum flipflag = 0;
	if(app.player.facing)
		flipflag = GPU_FLIP_NONE;
	if(!app.player.facing)
		flipflag = GPU_FLIP_HORIZONTAL;

	GPU_BlitRectX(app.playerSprite, NULL, app.renderTarget, &app.player.renderRect,
				0.0f, app.playerSprite->w / 2.0f, app.playerSprite->h / 2.0f, flipflag);
}

// onscreen text overlay
void draw_stats(void)
{
	GPU_RectangleFilled2(app.renderTarget, {140, 500, 370, 170}, {0, 0, 0, 100});

	char textBuffer[256];
	memset(&textBuffer, 0, sizeof(textBuffer));

	snprintf(textBuffer, sizeof(textBuffer), "Refresh Rate: %dHz\ndelta time: %.3f\nplayer speed: %.2f\nplayer move vector: {%.2f, %.2f}\nenemies: %u/%u\n",
											app.appHz,
											app.dt,
											app.player.speed,
											app.player.vel.x, app.player.vel.y,
											app.enemyCount, app.eSpawn.maxSpawns);

	GPU_Image *statsImage = texture_from_font(app.font, textBuffer, COLOR_WHITE);
	GPU_SetAnchor(statsImage, 0.0f, 0.0f);
	GPU_SetImageFilter(statsImage, GPU_FILTER_NEAREST);
	GPU_Blit(statsImage, NULL, app.renderTarget, 150, 500);
	GPU_FreeImage(statsImage);	// this must be freed after use
}

void label_waypoints(void)
{
	for(u8 i = 0; i < WAYPOINT_COUNT; i++)
	{
		GPU_Rect rect = GPU_MakeRect(app.waypoint[i].pos.x - 5, app.waypoint[i].pos.y, 65.0f, 30.0f);
		GPU_RectangleFilled2(app.renderTarget, rect, {0, 0, 0, 100});

		GPU_Image *text = texture_from_font(app.font, app.waypoint[i].name, COLOR_WHITE);
		GPU_SetAnchor(text, 0.0f, 0.0f);
		GPU_SetImageFilter(text, GPU_FILTER_NEAREST);
		GPU_Blit(text, NULL, app.renderTarget, app.waypoint[i].pos.x, app.waypoint[i].pos.y);
		GPU_FreeImage(text);
	}
}
