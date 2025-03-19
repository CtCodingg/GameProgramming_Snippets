#pragma once

struct Vector2DFloat {
  Vector2DFloat() = default;
  Vector2DFloat(float _x, float _y) : x(_x), y(_y) {}
  float x = 0.f;
  float y = 0.f;
};