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

struct enemySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns;
    f32 cooldown;
    f32 spawnedSpeed;
};

struct Enemy
{
    Vec2 nextPos, pos, vel, dest;
    f32 speed;
    bool alive;
};

struct Player
{
    Vec2 pos, vel;
    f32 speed;
    bool facing;
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
    GPU_Image *smiley;
    GPU_Image *playerSprite;

    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    enemySpawner eSpawn;
    Player player;

    Soundboard sounds;

    struct
    {
        u32 frameCounter;
    }Dev;
} App;
