typedef struct
{
    f32 x, y;
}Vec2;

typedef struct
{
    f32 x, y, z;
}Vec3;

typedef struct
{
    s32 x, y;
}IVec2;

typedef struct
{
    s32 x, y, z;
}IVec3;

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
    bool alive;
};

struct entitySpawner
{
    Vec2 pos;
    u32 numberSpawned, maxSpawns, cooldown;
};

// struct Waypoint
// {
//     Vec2 pos;
// };

struct Keybinds
{
    u8 left, right, up, down, escape, printscreen;
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
    entitySpawner eSpawn;
    // Waypoint waypoint[3];
    GPU_Image *spriteImages[9];
} App;
