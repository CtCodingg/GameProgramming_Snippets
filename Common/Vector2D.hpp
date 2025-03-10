#pragma once

class Vector2D {
public:
  Vector2D() = default;
  virtual ~Vector2D() = default;
  Vector2D(const Vector2D& other) = default;
  Vector2D& operator=(const Vector2D& other) = default;
  Vector2D(Vector2D&& other) = default;
  Vector2D& operator=(Vector2D&& other) = default;

  Vector2D(float x, float y);

  void SetX(float x);
  float GetX() const;
  void SetY(float y);
  float GetY() const;

private:
  float x_ = 0.f;
  float y_ = 0.f;
};