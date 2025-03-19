#pragma once

#include <SDL/SDL.h>

class Actor;

class Component {
public:
  Component() = delete;
  virtual ~Component();
  Component(const Component& other) = default;
  Component& operator=(const Component& other) = default;
  Component(Component&& other) = default;
  Component& operator=(Component&& other) = default;

  Component(Actor* owner, int update_order = 100);

  virtual void Update(float delta_time) {}
  void SetTexture(SDL_Texture* texture);

  int GetUpdateOrder() const { return update_order_; }
  int GetTextureWidth() const { return tex_width_; }
  int GetTextureHeight() const { return tex_height_; }

protected:
  Actor* owner_ = nullptr;
  int update_order_ = 100;
  SDL_Texture* texture_ = nullptr;
  int tex_width_ = 0;
  int tex_height_ = 0;
};