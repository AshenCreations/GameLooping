#pragma once
#include "common.h"
#include "utils.h"
#include "sound.h"
#include "input.h"

void update(void);

void spawn_enemy(void);
void update_enemy(void);
void move_to(Player *player);
void update_player(void);
void screenclip_enemy(void);
void screenclip_player(void);
void player_collision(void);


extern App app;
