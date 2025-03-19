#pragma once

#include "SpriteComponent.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class Actor;

class AnimSpriteComponent : public SpriteComponent {
public:
  AnimSpriteComponent() = delete;
  virtual ~AnimSpriteComponent() = default;
  AnimSpriteComponent(const AnimSpriteComponent& other) = default;
  AnimSpriteComponent& operator=(const AnimSpriteComponent& other) = default;
  AnimSpriteComponent(AnimSpriteComponent&& other) = default;
  AnimSpriteComponent& operator=(AnimSpriteComponent&& other) = default;

  AnimSpriteComponent(Actor* owner, int draw_order = 100);

  void Update(float delta_time) override;
  void SetAnimTextures(const std::vector< SDL_Texture*> textures);

  float GetAnimFps() const { return anim_fps_; }
  void SetAnimFps(float anim_fps) { anim_fps_ = anim_fps; }

private:
  std::vector<SDL_Texture*> anim_textures_;
  float curr_frame_ = 0.f;
  float anim_fps_ = 24.f;
};