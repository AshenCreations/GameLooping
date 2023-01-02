#pragma once

struct Vec2
{
    f32 x, y;
};

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
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

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
    u16 left, right, up, down, escape, printscreen, space;
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
    Vec2 pos, vel, targetPos, oldPos, dPos;
    f32 speed;
    f32 minDistance;
    u16 WpIdx;
    bool alive, facing;
    GPU_Rect renderRect;
    Circle collideCircle;
};

struct Player
{
    Vec2 pos, vel, targetPos, oldPos, dPos;
    f32 speed;
    f32 minDistance;
    bool alive, facing, hasTarget;
    GPU_Rect renderRect;
    Circle collideCircle;
};

// // replacement data type for enemies( AND player ???)
// struct Entity
// {
//     Vec2 pos, vel, targetPos, oldPos, dPos;
//     f32 speed, minDistance;
//     u16 healthMax, healthCurrent;
//     bool alive, facing;
//     GPU_Rect renderRect;
//     Circle collideCircle;
//     enum EntityType type;
// };

struct Soundbank
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
    Soundbank sounds;

    Waypoint waypoint[WAYPOINT_COUNT];
    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    enemySpawner eSpawn;
    Player player;

    struct
    {
        u32 frameCounter;
    }Dev;
} App;

// struct command
// {
  
// };
