#pragma once

struct Vec2
{
    f32 x, y;
};

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

internal Vec2 vec_2(float x, float y)
{
  return {x, y};
}

internal Vec2 vec_2(float val)
{
  return {val, val};
}

struct IVec2
{
    s32 x, y;
};

struct Point
{
    f32 x, y;
};

struct Circle
{
    Vec2 pos;
    f32 radius;
};

struct Mouse
{
    IVec2 pos;
    u32 buttons;
};

struct Keybinds
{
    u8 left, right, up, down, escape, printscreen, space;
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
    s32 cooldown;
    f32 spawnedSpeed;
};

struct Enemy
{
    Vec2 pos, vel;
    Vec2 targetWaypoint;
    f32 minDistance;
    f32 speed;
    u8 WpIdx;
    bool alive;
    bool facing;
    GPU_Rect renderRect;
};

struct Player
{
    Vec2 pos, vel;
    f32 speed;
    bool facing;
    GPU_Rect renderRect;
};

// struct Entity
// {
//     Vec2 pos, vel;
//     f32 speed;
//     enum EntityType type;
//     u8 healthMax, healthCurrent;
// };

struct Soundboard
{
    Mix_Chunk *nope, *bruh;
    // Mix_Music *track1;
};

// main app struct
typedef struct
{
    SDL_Window *window;
    GPU_Target *renderTarget;
    Keybinds keybind;
    bool keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;

    f64 t;
    f32 dt;
    f32 dtMulti;
    s32 appHz;

    TTF_Font *font;
    GPU_Image *enemySprite;
    GPU_Image *playerSprite;

    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    enemySpawner eSpawn;
    Player player;

    Soundboard sounds;

    Waypoint waypoint[WAYPOINT_COUNT];

    struct
    {
        u32 frameCounter;
    }Dev;
} App;
