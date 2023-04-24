#pragma once
#include "common.h"

void init(void);
void init2(void);
void init_SDL(void);
void init_screen(void);
void cleanup(void);
void init_keybinds(void);
void init_spawner(void);
void init_sound(void);
void init_player(void);
void init_enemies(void);
void init_waypoints(void);
void init_renderlayers(void);

extern App app;
