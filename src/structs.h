struct Vec2
{
    f32 x, y;

    // vector + vector
    Vec2 operator+(const Vec2 &other)
    {
        Vec2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }

    // vector * scalar
    Vec2 operator*(f32 scalar)
    {
        Vec2 result;
        result.x = x * scalar;
        result.y = y * scalar;
        return result;
    }

    // vector - vector
    Vec2 operator-(const Vec2 &other)
    {
        Vec2 result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }

    //! vector *= scalar not working
    Vec2 operator*=(const f32 &other)
    {
        Vec2 result;
        result.x = x * other;
        result.y = y * other;
        return result;
    }
    
    //! vector /= scalar not working
    Vec2 operator/=(const f32 &other)
    {
        Vec2 result;
        result.x = x / other;
        result.y = y / other;
        return result;
    }
};

struct IVec2
{
    s32 x, y;
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
    u8 left, right, up, down, escape, printscreen;
};

struct enemySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns;
    f64 cooldown;
};

struct Waypoint
{
    Vec2 pos;
};

struct Enemy
{
    Vec2 pos, velocity, dest;
    f32 speed;
    bool alive;
};

struct Player
{
    Vec2 pos, vel;
    f32 speed;
};

// A State struct only contains any data which is linked to movement/physics
// any Images or Sounds will be distorted by state blending & therefore unreadable
struct State
{
    Player player;

    // state * scalar
    State operator*(f64 scalar)
    {
        State result;
        result.player.pos = player.pos * scalar;
        result.player.vel = player.vel * scalar;
        return result;
    }

    // state + state
    State operator+(const State &other)
    {
        State result;
        result.player.pos = player.pos + other.player.pos;
        result.player.vel = player.vel + other.player.vel;
        return result;
    }
};

// main app struct
typedef struct
{
    SDL_Window *window;
    GPU_Target *renderTarget;
    Keybinds keybind;
    bool keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;

    f64 t, dt;
    f32 dtMulti;
    u8 appHz;

    TTF_Font *font;
    GPU_Image *smiley;
    GPU_Image *playerSprite;
    Waypoint waypoint[3];

    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    enemySpawner eSpawn;

    State previousState, currentState;

    struct
    {
        u32 frameCounter;
    }Dev;
} App;
