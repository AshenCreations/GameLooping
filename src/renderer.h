#pragma once
#include "common.h"

void render(float alpha);

void update_part_frame(float alpha);
void present_scene(void);
void draw_background(void);
void draw_middleground(void);
void draw_foreground(void);

void draw_enemy(GPU_Target *target);
void draw_player(GPU_Target *target);
void draw_player_moves(GPU_Target *target);

void draw_stats(GPU_Target *target);
void label_waypoints(GPU_Target *target);
void draw_player_vectorlabel(GPU_Target *target);
void draw_time(double time, GPU_Target *target);

enum RenderSubLayers
{
	RENDER_SUB_BG = -1,
	RENDER_SUB_MG,
	RENDER_SUB_FG
};




extern App app;
