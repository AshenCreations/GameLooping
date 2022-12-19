#pragma once

#define internal static
#define global_variable static

#define WINDOW_TITLE "Game Looping Learning"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900
#define MAX_KEYBOARD_KEYS 350
#define KEYPRESS_COOLDOWN 1

// fonts
#define FONT_PATH "fonts/continuum.ttf"
#define FONT_SIZE 24

// images
#define IMAGEPATH_smiley "img/smiley.png"
#define IMAGEPATH_player "img/monakS_64x64.png"

// sounds
#define SOUNDPATH_NOPE "sound/nope.wav"
#define SOUNDPATH_BRUH "sound/bruh.wav"

// Colors
#define COLOR_BLACK {0, 0, 0, 255}
#define COLOR_WHITE {255, 255, 255, 255}

#define PLAYER_SPEED 12.0f
#define MAX_ENEMIES 100
#define ENEMY_SPEED 18.0f

#define SPAWN_POINT {100, 100}
#define WAYPOINT_1 {1200, 100}
#define WAYPOINT_2 {1200, 700}
#define WAYPOINT_3 {800, 500}

#define INVERSE_ROOT_2 0.707106781186f
#define PI_32 3.14159265359f
