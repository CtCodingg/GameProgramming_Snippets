#pragma once

#include <SDL/SDL.h>

#include <memory>

class Actor;

class Component {
public:
  Component() = delete;
  virtual ~Component() = default;
  Component(const Component& other) = default;
  Component& operator=(const Component& other) = default;
  Component(Component&& other) = default;
  Component& operator=(Component&& other) = default;

  Component(std::shared_ptr<Actor> owner, int update_order = 100);

  virtual void Update(float delta_time) = 0;
  virtual void Draw(SDL_Renderer* renderer) = 0;
  int GetUpdateOrder() const;
  int GetTextureWidth() const;
  int GetTextureHeight() const;
  void SetTexture(SDL_Texture* texture);

protected:
  std::shared_ptr<Actor> owner_ = nullptr;
  int update_order_ = 100;
  SDL_Texture* texture_ = nullptr;
  int tex_width_ = 0;
  int tex_height_ = 0;
};