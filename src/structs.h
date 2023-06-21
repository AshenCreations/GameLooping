#pragma once

#include "types.h"
#include "math.h"

struct Circle
{
    Point pos;
    float radius;
};

struct Color
{
	u8 r, g, b;
};

struct IVec2
{
    int x, y;
};
struct Mouse
{
    IVec2 pos;
    u32 buttons;
	u32 wasButtons;
};
struct Keystate
{
	bool keyPressed;
	bool wasPressed;
};
struct Keybinds
{
    int escape, left, right, up, down, ctrl, BGLayer, MGLayer, FGLayer;
};

struct Waypoint
{
	Vec2 pos;
	char *name;
};
struct enemySpawner
{
    Vec2 pos, targetWaypoint;
    u32 spawnedIdx, maxSpawns;
    float cooldown;
    float spawnedSpeed;
};
struct Enemy
{
	int ID;
	Vec2 pos, vel, targetPos, oldPos, dPos;
	float speed;
	float minDistance;
	int WpIdx;
	int currentHP, maxHP;
	bool alive, facing, hasTarget;
	GPU_Rect renderRect;
	Circle collider;



	float cooldownTest;

	//TODO: try to add a timer to an enemy
	//TODO: base the timer in seconds
	//! why was i doing this ?????
	void add_timer(float time)
	{
		cooldownTest = time;
		// add_to_timers_queue(ID);
	}
};

struct Player
{
	Vec2 pos, vel, accel, targetPos, oldPos, dPos;
	float speed, maxSpeed;
	float minDistance;
	bool alive, facing, hasTarget;
	GPU_Rect renderRect;
	Circle collider;

	Queue <Vec2, PLAYER_MAX_NUM_MOVES> moveQueue;
	Vec2 lArray[PLAYER_MAX_NUM_MOVES];

	int damage;
	float damageCd;
};

struct Soundbank
{
    Mix_Chunk *nope, *bruh;
    // Mix_Music *track1;
};

struct Screen
{
	GPU_Target *renderOutput;
	GPU_Image *BG, *MG, *FG;
};

// main app struct
typedef struct
{
	SDL_Window *window;
	Screen screen;
	Keystate keys[MAX_KEYBOARD_KEYS];
	Mouse mouse;
	Keybinds keybind;
	u32 screenState;

	double time;
	float dt;
	float dtMulti;
	int appHz;
	int updatesPerFrame;
	float oneSecond;

	GPU_Image *enemySprite;
	GPU_Image *playerSprite;
	FC_Font *fcfont;
	GPU_Image *grass;
	Soundbank sounds;

	Waypoint waypoint[WAYPOINT_COUNT];
	Enemy enemy[MAX_ENEMIES];
	int enemyCount;
	enemySpawner eSpawn;
	Player player;
} App;
