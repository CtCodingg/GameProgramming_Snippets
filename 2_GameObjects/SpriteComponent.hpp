#pragma once

#include "Component.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Actor;

class SpriteComponent : public Component {
public:
  SpriteComponent() = delete;
  virtual ~SpriteComponent() = default;
  SpriteComponent(const SpriteComponent& other) = default;
  SpriteComponent& operator=(const SpriteComponent& other) = default;
  SpriteComponent(SpriteComponent&& other) = default;
  SpriteComponent& operator=(SpriteComponent&& other) = default;

  SpriteComponent(std::shared_ptr<Actor> owner, int update_order = 100, int draw_order = 100);

  void Update(float delta_time) override;
  void Draw(SDL_Renderer* renderer) override;
  int GetDrawOrder() const { return draw_order_; }

private:
  int draw_order_ = 100;
};