#include "Vector2D.hpp"

Vector2D::Vector2D(float x, float y) :
  x_(x), y_(y)
{
}

void Vector2D::SetX(float x) {
  x_ = x;
}

float Vector2D::GetX() const {
  return x_;
}

void Vector2D::SetY(float y) {
  y_ = y;
}

float Vector2D::GetY() const {
  return y_;
}
