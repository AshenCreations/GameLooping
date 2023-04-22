#pragma once

struct Vec2
{
    float x, y;
};

typedef Vec2 Point;

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Vec2 operators ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
internal Vec2 operator+(Vec2 a, Vec2 other)
{
  return Vec2{
    a.x + other.x,
    a.y + other.y};
}

internal Vec2 operator+(Vec2 a, float scalar)
{
  return Vec2{
    a.x + scalar,
    a.y + scalar};
}

internal Vec2& operator+=(Vec2& a, Vec2 b)
{
  a = a + b;
  return a;
}

internal Vec2 operator-(Vec2 a, Vec2 other)
{
  return Vec2{
    a.x - other.x,
    a.y - other.y};
}

internal Vec2 operator-(float scalar, Vec2 a)
{
  return Vec2{
    scalar - a.x,
    scalar - a.y};
}

internal Vec2& operator-=(Vec2& a, Vec2 b)
{
  a = a - b;
  return a;
}

internal Vec2 operator*(Vec2 a, Vec2 other)
{
  return Vec2{
    a.x * other.x,
    a.y * other.y};
}

internal Vec2 operator*(Vec2 a, float scalar)
{
  return Vec2{
    a.x * scalar,
    a.y * scalar};
}

internal Vec2 operator/(Vec2 a, Vec2 other)
{
  return Vec2{
    a.x / other.x,
    a.y / other.y};
}

internal Vec2 operator/(Vec2 a, float scalar)
{
  return Vec2{
    a.x / scalar,
    a.y / scalar};
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

struct IVec2
{
    int x, y;
};

struct Circle
{
    Point pos;
    float radius;
};

struct Color
{
	u8 r, g, b;
};

struct Mouse
{
    IVec2 pos;
    unsigned buttons;
	unsigned wasButtons;
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

	// Array <Vec2, 3> testArray;
	int damage;
	float damageCooldown;
};

struct Soundbank
{
    Mix_Chunk *nope, *bruh;
    // Mix_Music *track1;
};

struct Screen
{
	GPU_Target *screenOutput;
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
	float oneSecond;

	GPU_Image *enemySprite;
	GPU_Image *playerSprite;
	GPU_Image *grass;
	FC_Font *fcfont;
	Soundbank sounds;

	Waypoint waypoint[WAYPOINT_COUNT];
	Enemy enemy[MAX_ENEMIES];
	int enemyCount;
	enemySpawner eSpawn;
	Player player;
} App;
