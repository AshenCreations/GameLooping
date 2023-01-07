#pragma once

#define internal static
#define global_variable static

// window
#define WINDOW_TITLE "Game Looping"
#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MAX_KEYBOARD_KEYS 350

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

// math
#define INVERSE_ROOT_2 0.707106781186f
#define PI_32 3.14159265359f

// stats
#define PLAYER_SPEED 12.0f
#define PLAYER_MAX_NUM_MOVES 8
#define ENEMY_SPEED 12.0f
#define MAX_ENEMIES 30
#define PLAYER_WAYPOINT_MIN_DISTANCE 0.33f
#define ENEMY_WAYPOINT_MIN_DISTANCE 0.33f

// // templated bound-checked array
// template <typename T, int N>
// struct Array
// {
//   static constexpr int maxElements = N;
  
//   int count = 0;
//   T elements[N];
  
//   T& operator[](int idx)
//   {
//     //CAKEZ_ASSERT(idx >= 0, "Idx negative!");
//     //CAKEZ_ASSERT(idx < count, "Idx out of bounds!");
//     assert(idx >= 0);
//     assert(idx < count);
//     return elements[idx];
//   }
  
//   int add(T element)
//   {
//     //CAKEZ_ASSERT(count < maxElements, "Array Full!");
//     assert(count < maxElements);
//     elements[count] = element;
//     return count++;
//   }
  
//   void remove_and_swap(int idx)
//   {
//     //CAKEZ_ASSERT(idx >= 0, "Idx negative!");
//     //CAKEZ_ASSERT(idx < count, "Idx out of bounds!");
//     assert(idx >= 0);
//     assert(idx < count);
//     elements[idx] = elements[--count];
//   }
// };
