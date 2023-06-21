#pragma once

#define internal static
#define global_variable static

struct Vec2
{
    float x, y;
};
typedef Vec2 Point;

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Vec2 operators ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
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

internal Vec2 operator-(float scalar, Vec2 a)
{
  return Vec2{
    scalar - a.x,
    scalar - a.y};
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
