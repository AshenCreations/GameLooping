#include "renderer.h"
#include "textures.h"
#include "utils.h"


// Render all the things
void render(float alpha)
{
	// clear to help check layer system
	GPU_ClearRGB(app.screen.screenOutput, 35, 0, 35);

	// check screenState to see which layers should be drawn/hidden
	if(isBitSet(app.screenState, 1))
	{
		draw_background();
	}
	if(isBitSet(app.screenState, 2))
	{
		draw_middleground(alpha);
	}
	if(isBitSet(app.screenState, 3))
	{
		draw_foreground();
	}

	// show screen
	present_scene();
}

//********************************************************
// arrange BG then draw to screen
void draw_background(void)
{
	// set render target to BG layer & clear it to transparent
	GPU_LoadTarget(app.screen.BG);
	GPU_ClearRGBA(app.screen.BG->target, 0, 0, 0, 0);

	// grass
	GPU_BlitRect(app.grass, NULL, app.screen.BG->target, NULL);

	GPU_BlitRect(app.screen.BG, NULL, app.screen.screenOutput, NULL);
}

// arrange MG then screen
void draw_middleground(float alpha)
{
	// switch rendertarget to MG
	GPU_LoadTarget(app.screen.MG);
	//clear MG to transparent
	GPU_ClearRGBA(app.screen.MG->target, 0, 0, 0, 0);

	// draw MG things
	draw_enemy(alpha, app.screen.MG->target);
	draw_player_moves(alpha, app.screen.MG->target);
	draw_player(alpha, app.screen.MG->target);

	// blit MG to screenOutput
	GPU_BlitRect(app.screen.MG, NULL, app.screen.screenOutput, NULL);
}

// arrange FG then screen
void draw_foreground(void)
{
	GPU_LoadTarget(app.screen.FG);
	GPU_ClearRGBA(app.screen.FG->target, 0, 0, 0, 0);

	draw_stats(app.screen.FG->target);
	label_waypoints(app.screen.FG->target);
	draw_time(get_time_secs(), app.screen.FG->target);
	draw_player_vectorlabel(app.screen.FG->target);

	GPU_BlitRect(app.screen.FG, NULL, app.screen.screenOutput, NULL);
}

//********************************************************

// show the screen
void present_scene(void)
{
	GPU_Flip(app.screen.screenOutput);
}

// render the  enemies
void draw_enemy(float alpha, GPU_Target *target)
{
	for(int i = 0; i < app.enemyCount; i++)
	{
		if(app.enemy[i].alive)
		{
			//frame offset
			app.enemy[i].pos += app.enemy[i].dPos * alpha;

			// draw enemy
			app.enemy[i].renderRect = GPU_MakeRect(app.enemy[i].pos.x - app.enemySprite->w / 2.0f,
												app.enemy[i].pos.y - app.enemySprite->h / 2.0f,
												app.enemySprite->w, app.enemySprite->h);

			GPU_FlipEnum flipflag = GPU_FLIP_NONE;
			if(!app.enemy[i].facing)
				flipflag = GPU_FLIP_HORIZONTAL;

			GPU_BlitRectX(app.enemySprite, NULL, target, &app.enemy[i].renderRect,
				0.0f, app.enemySprite->w / 2.0f, app.enemySprite->h / 2.0f, flipflag);

			// draw hp bar
			GPU_Rect rect = {app.enemy[i].pos.x - (app.enemySprite->w / 2), app.enemy[i].pos.y - (app.enemySprite->h / 2) - 12,
							56 * (app.enemy[i].currentHP / (float)app.enemy[i].maxHP), 6};
			SDL_Color color = {200, 0, 0, 255};
			GPU_RectangleFilled2(target, rect, color);
		}
	}
}

// render the player
void draw_player(float alpha, GPU_Target *target)
{
	// frame offset here, so that draw_player_moves() can be drawn before player
	app.player.pos += app.player.dPos * (float)alpha;

	app.player.renderRect = GPU_MakeRect(app.player.pos.x - app.playerSprite->w / 2.0f,
										app.player.pos.y - app.playerSprite->h / 2.0f,
										app.playerSprite->w,
										app.playerSprite->h);

	GPU_FlipEnum flipflag = GPU_FLIP_NONE;
	if(!app.player.facing)
		flipflag = GPU_FLIP_HORIZONTAL;

	GPU_BlitRectX(app.playerSprite, NULL, target, &app.player.renderRect,
				0.0f, app.playerSprite->w / 2.0f, app.playerSprite->h / 2.0f, flipflag);
}

// draw queue->size label & waypoint circles with move lines
void draw_player_moves(float alpha, GPU_Target *target)
{
	// frame offset here, so that draw_player_moves() can be drawn before player
	app.player.pos += app.player.dPos * (float)alpha;

	// draw waypoint circles & route lines
    if(!app.player.moveQueue.queue_is_empty())
	{
		// line from player to targetPos
		GPU_Line(target, app.player.pos.x, app.player.pos.y, app.player.targetPos.x, app.player.targetPos.y, COLOR_GREEN);

		for(int i = 0; i < app.player.moveQueue.size; i++)
		{
			// waypoint marker
			GPU_Circle(target, app.player.lArray[i].x, app.player.lArray[i].y, 20.0f, COLOR_GREEN);

			// lines from waypoint to next waypoint
			if(i < app.player.moveQueue.size - 1)
			{
				GPU_Line(target, app.player.lArray[i].x, app.player.lArray[i].y,
						app.player.lArray[i + 1].x, app.player.lArray[i + 1].y, COLOR_GREEN);
			}
		}
	}
}

// onscreen text overlay
void draw_stats(GPU_Target *target)
{
	u16 textW = FC_GetWidth(app.fcfont, "Refresh Rate: %dHz\ndelta time: %.3f\nplayer speed: %.2f\nspawned: %d/%u",
										app.appHz, app.dt, app.player.speed, app.enemyCount, app.eSpawn.maxSpawns);
	u16 textH = FC_GetHeight(app.fcfont,"Refresh Rate: %dHz\ndelta time: %.3f\nplayer speed: %.2f\nspawned: %d/%u",
										app.appHz, app.dt, app.player.speed, app.enemyCount, app.eSpawn.maxSpawns);
	GPU_RectangleFilled2(target,
						{300 - 4, 500, (float)textW + 8, (float)textH},
						{0, 0, 0, 125});

	FC_DrawColor(app.fcfont, target, 300, 500,
				COLOR_WHITE,
				"Refresh Rate: %dHz\ndelta time: %.3f\nplayer speed: %.2f\nspawned: %d/%u",
				app.appHz,
				app.dt,
				app.player.speed,
				app.enemyCount, app.eSpawn.maxSpawns);
}

// labels for waypoints
void label_waypoints(GPU_Target *target)
{
	for(int i = 0; i < WAYPOINT_COUNT; i++)
	{
		u16 textW = FC_GetWidth(app.fcfont, app.waypoint[i].name);
		u16 textH = FC_GetHeight(app.fcfont, app.waypoint[i].name);
		GPU_RectangleFilled2(target,
							{app.waypoint[i].pos.x - 4, app.waypoint[i].pos.y, (float)textW + 8, (float)textH},
							{0, 0, 0, 125});

		FC_DrawColor(app.fcfont, target,
					app.waypoint[i].pos.x,
					app.waypoint[i].pos.y,
					COLOR_WHITE,
					app.waypoint[i].name);
	}
}

void draw_player_vectorlabel(GPU_Target *target)
{
	u16 textW = FC_GetWidth(app.fcfont, "x: %.2f\ny: %.2f", app.player.vel.x, app.player.vel.y);
	u16 textH = FC_GetHeight(app.fcfont, "x: %.2f\ny: %.2f", app.player.vel.x, app.player.vel.y);
	GPU_RectangleFilled2(target,
						{app.player.pos.x - (textW / 2.0f) - 4,
						app.player.pos.y + (textH / 2.0f) + 4,
						(float)textW + 8,
						(float)textH},
						{0, 0, 0, 125});

	SDL_Color tempColor = FC_GetDefaultColor(app.fcfont);
	FC_SetDefaultColor(app.fcfont, COLOR_RED);

	FC_DrawAlign(app.fcfont, target,
				app.player.pos.x,
				app.player.pos.y + app.playerSprite->h / 2.0f,
				FC_ALIGN_CENTER,
				"x: %.2f\ny: %.2f", app.player.vel.x, app.player.vel.y);

	FC_SetDefaultColor(app.fcfont, tempColor);
}

void draw_time(double time, GPU_Target *target)
{
	u16 textW = FC_GetWidth(app.fcfont, "%.3f", time);
	u16 textH = FC_GetHeight(app.fcfont, "%.3f", time);
	GPU_RectangleFilled2(target,
						{0, 0, (float)textW + 4, (float)textH},
						{0, 0, 0, 125});

	FC_DrawColor(app.fcfont, target,
				0,
				0,
				COLOR_GREEN,
				"%.3f", time);
}
