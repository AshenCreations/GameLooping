struct Vec2
{
    f32 x, y;

    Vec2 &operator*=(f64 A);
    Vec2 &operator+=(Vec2 A);
    Vec2 &operator-=(Vec2 A);
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
    GPU_Image *image;
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

struct Keybinds
{
    u8 left, right, up, down, escape, printscreen;
};

struct Enemy
{
    Vec2 pos, dPos;
    bool alive;
};

struct enemySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns;
    f64 cooldown;
};

//! not used
struct Waypoint
{
    Vec2 pos;
};

//! not used
struct Player
{
    Vec2 pos;
    Vec2 dPos;
    bool playerFacing;
};

//! not used
struct Command
{
    void (*execute)(void);
};

// main app struct
typedef struct
{
    GPU_Target *renderTarget;
    Keybinds keybind;
    bool keyboard[MAX_KEYBOARD_KEYS];
    Mouse mouse;
    Ui_context ui_context;
    TTF_Font *font;
    Button button[UI_BUTTON_COUNT];
    GPU_Image *smiley;
    Enemy enemy[MAX_ENEMIES];
    u32 enemyCount;
    char enemyCountText[30];
    enemySpawner eSpawn;
    GPU_Image *enemyCounter;

    GPU_Image *instruction;
    char instructionText[50];

    // Waypoint waypoint[3];
    
    Player player;
    Command command;



    // GPU_Image *spriteImages[9];
} App;
