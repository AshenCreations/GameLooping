#include "renderer.h"

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void render(f64 alpha);

void prepare_scene(void);
void present_scene(void);
void draw_enemy(f64 alpha);
void draw_player(f64 alpha);
void draw_stats(void);
void label_waypoints(void);
void draw_player_moves(Queue* queue);
void draw_label_text(SDL_Color bgColor, GPU_Image* text, f32 x, f32 y);

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ START Declarations ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

void render(f64 alpha)
{
	prepare_scene();

	draw_enemy(alpha);
	draw_player(alpha);
	
	draw_player_moves(&app.player.moveQueue);
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

// render the  enemies
void draw_enemy(f64 alpha)
{
	for(s32 i = 0; i < app.enemyCount; i++)
	{
		if(app.enemy[i].alive)
		{
			//frame offset
			app.enemy[i].pos = app.enemy[i].pos + (app.enemy[i].dPos * (f32)alpha);

			app.enemy[i].renderRect = GPU_MakeRect(app.enemy[i].pos.x - app.enemySprite->w / 2.0f,
												app.enemy[i].pos.y - app.enemySprite->h / 2.0f,
												app.enemySprite->w, app.enemySprite->h);

			GPU_FlipEnum flipflag = GPU_FLIP_NONE;
			if(!app.enemy[i].facing)
				flipflag = GPU_FLIP_HORIZONTAL;

			GPU_BlitRectX(app.enemySprite, NULL, app.renderTarget, &app.enemy[i].renderRect,
				0.0f, app.enemySprite->w / 2.0f, app.enemySprite->h / 2.0f, flipflag);

			// hp bar
			GPU_Rect rect = {app.enemy[i].pos.x - (app.enemySprite->w / 2), app.enemy[i].pos.y - (app.enemySprite->h / 2) - 12,
							56 * (app.enemy[i].currentHP / (f32)app.enemy[i].maxHP), 6};
			SDL_Color color = {200, 0, 0, 255};
			GPU_RectangleFilled2(app.renderTarget, rect, color);
		}
	}
}

// render the player
void draw_player(f64 alpha)
{
	//frame offset
	app.player.pos = app.player.pos + (app.player.dPos * (f32)alpha);

	app.player.renderRect = GPU_MakeRect(app.player.pos.x - app.playerSprite->w / 2.0f,
										app.player.pos.y - app.playerSprite->h / 2.0f,
										app.playerSprite->w,
										app.playerSprite->h);

	GPU_FlipEnum flipflag = GPU_FLIP_NONE;
	if(!app.player.facing)
		flipflag = GPU_FLIP_HORIZONTAL;

	GPU_BlitRectX(app.playerSprite, NULL, app.renderTarget, &app.player.renderRect,
				0.0f, app.playerSprite->w / 2.0f, app.playerSprite->h / 2.0f, flipflag);
}

// onscreen text overlay
void draw_stats(void)
{
	char textBuffer[256];
	memset(&textBuffer, 0, sizeof(textBuffer));

	snprintf(textBuffer, sizeof(textBuffer), "Refresh Rate: %dHz\ndelta time: %.3f\nplayer speed: %.2f\nplayer move vector: {%.2f, %.2f}\nenemies: %u/%u\n",
											app.appHz,
											app.dt,
											app.player.speed,
											app.player.vel.x, app.player.vel.y,
											app.enemyCount, app.eSpawn.maxSpawns);

	GPU_Image *statsImage = texture_from_font_wrapped(app.font, textBuffer, COLOR_WHITE, 360);
	draw_label_text({0, 0, 0, 100}, statsImage, 150, 500);
}

// labels for waypoints
void label_waypoints(void)
{
	for(u8 i = 0; i < WAYPOINT_COUNT; i++)
	{
		GPU_Image *text = texture_from_font(app.font, app.waypoint[i].name, COLOR_WHITE);
		draw_label_text({0, 0, 0, 100}, text, app.waypoint[i].pos.x, app.waypoint[i].pos.y);
	}
}

// draw queue->size label & waypoint circles with move lines
void draw_player_moves(Queue* queue)
{
	char textBuffer[16];
	memset(&textBuffer, 0, sizeof(textBuffer));
	snprintf(textBuffer, sizeof(textBuffer), "queue size: %d", queue->size);

	GPU_Image* text = texture_from_font(app.font, textBuffer, COLOR_WHITE);
	draw_label_text({0, 0, 0, 150}, text, app.player.pos.x - text->w / 2, app.player.pos.y + app.player.collider.radius);

	// draw waypoint circles & route lines
    if(!queue_is_empty(queue))
	{
		for(s32 i = 0; i < queue->size; i++)
		{
			GPU_Circle(app.renderTarget, app.player.lArray[i].x, app.player.lArray[i].y, 20.0f, COLOR_WHITE);

			// line from player to targetPos
			GPU_Line(app.renderTarget, app.player.pos.x, app.player.pos.y, app.player.targetPos.x, app.player.targetPos.y, COLOR_WHITE);

			// lines from waypoint to next waypoint
			if(i < queue->size - 1)
			{
				GPU_Line(app.renderTarget, app.player.lArray[i].x, app.player.lArray[i].y,
						app.player.lArray[i + 1].x, app.player.lArray[i + 1].y, COLOR_WHITE);
			}
		}
	}
}

// draw already imaged ttf text with background rect
void draw_label_text(SDL_Color bgColor, GPU_Image* text, f32 x, f32 y)
{
	GPU_Rect rect = GPU_MakeRect(x - 10, y, (f32)text->w + 20, (f32)text->h);
	GPU_RectangleFilled2(app.renderTarget, rect, bgColor);
	GPU_SetAnchor(text, 0.0f, 0.0f);
	GPU_SetImageFilter(text, GPU_FILTER_NEAREST);
	GPU_Blit(text, NULL, app.renderTarget, x, y);
	GPU_FreeImage(text);
}
