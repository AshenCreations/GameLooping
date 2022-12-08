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

    // does this operator even work ???
    Vec2 operator*=(const f32 &other)
    {
        Vec2 result;
        result.x = x * other;
        result.y = y * other;
        return result;
    }
    Vec2 operator-=(Vec2 A)
    {
        Vec2 result;
        result.x -= A.x;
        result.y -= A.y;
        return result;
    }
};

struct IVec2
{
    s32 x, y;
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

struct Enemy
{
    Vec2 pos, velocity, dest;
    bool alive;
};

struct enemySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns;
    f64 cooldown;
};

// main app struct
typedef struct
{
    GPU_Target *renderTarget;
    Keybinds keybind;
    bool keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;
    u32 keypressCooldown;

    TTF_Font *font;
    GPU_Image *smiley;
    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    enemySpawner eSpawn;

    GPU_Image *statsImage;
    char statsText[100];
} App;
