struct Vec2
{
    f32 x, y;

    Vec2 &operator*=(f32 A);
    Vec2 &operator+=(Vec2 A);
};

struct IVec2
{
    s32 x, y;
};

struct Ui_id
{
    // void (*owner)(void);    //! not used currently
    s32 index;
};

struct Button
{
    s32 index;
    GPU_Image *texture;
};

struct Ui_context
{
    Ui_id hot, active;
};

struct Mouse
{
    IVec2 pos;
    u32 buttons;
};

struct Enemy
{
    Vec2 pos;
    Vec2 dPos;
    bool alive;
};

struct entitySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns, cooldown;
};

struct Waypoint
{
    Vec2 pos;
};

struct Keybinds
{
    u8 left, right, up, down, escape, printscreen;
};

struct Player
{
    Vec2 pos;
    Vec2 dPos;
};

typedef struct
{
    GPU_Target *renderTarget;
    Keybinds keybind;
    bool keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;
    Ui_context ui_context;
    Button button[UI_BUTTON_COUNT];
    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    Player player;


    entitySpawner eSpawn;
    Waypoint waypoint[3];

    GPU_Image *spriteImages[9];
} App;
