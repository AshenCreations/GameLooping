#pragma once
#include "common.h"
#include "types.h"
#include "textures.h"
#include "utils.h"

void render(float alpha);

void set_renderlayer(GPU_Image* image);
void update_part_frame(float alpha);

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

enum RenderLayerBits
{
	BIT_BG = 1,
	BIT_MG,
	BIT_FG
};

extern App app;
