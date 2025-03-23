#pragma once

#include "Component.hpp"

#include <vector>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class SpriteComponent : public Component {
public:
  SpriteComponent() = delete;
  virtual ~SpriteComponent();
  SpriteComponent(const SpriteComponent& other) = default;
  SpriteComponent& operator=(const SpriteComponent& other) = default;
  SpriteComponent(SpriteComponent&& other) = default;
  SpriteComponent& operator=(SpriteComponent&& other) = default;

  SpriteComponent(Actor* owner, int draw_order = 100);

  virtual void Draw(SDL_Renderer* renderer);

  int GetDrawOrder() const { return draw_order_; }

protected:
  int draw_order_ = 100;
};