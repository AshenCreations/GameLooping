#pragma once
#include "common.h"

int round_float2Int(float a);
float square(float a);
Vec2 square(Vec2 a);
float cubed(float a);
float check_distance(Vec2 a, Vec2 b);
float Vec2_length(Vec2 vec);

float remap_range(float value, float iMin, float iMax, float oMin, float oMax);

float lerp(float a, float b, float t);
u8 lerp(u8 a, u8 b,float t);
Vec2 lerp(Vec2 a, Vec2 b, float t);
Color lerp(Color a, Color b, float t);
float inverse_lerp(float a, float b, float v);
float inverse_lerp(Vec2 a, Vec2 b, Vec2 value);
float remap_lerp(float iMin, float iMax, float oMin, float oMax, float value);

float dot_product(Vec2 a, Vec2 b);
Vec2 unit_Vec2(Vec2 a);
bool point_in_circle(Vec2 pos, Circle a);
bool circle_in_circle(Circle a, Circle b);

Vec2 make_Vec2(float x, float y);
Vec2 make_Vec2(float val);

Color extract_RGB(SDL_Color iCol);

float get_time_ms(void);
float get_time_secs(void);

int setBit(int x, unsigned char position);
int clearBit(int x, unsigned char position);
int modifyBit(int x, unsigned char position, bool newState);
int flipBit(int x, unsigned char position);
bool isBitSet(int x, unsigned char position);

extern App app;
