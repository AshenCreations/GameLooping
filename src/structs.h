struct Ui_id
{
    //void (*owner)(void);    //! not used currently
    s32 index;
};

struct Atomic
{
    GPU_Rect rect;
    SDL_Color color;
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
    Button button[BUTTON_COUNT];
} App;
