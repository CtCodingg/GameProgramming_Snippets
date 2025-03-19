#pragma once

#include "SpriteComponent.hpp"
#include "Vector.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

class BGSpriteComponent : public SpriteComponent {
public:
  BGSpriteComponent() = delete;
  virtual ~BGSpriteComponent() = default;
  BGSpriteComponent(const BGSpriteComponent& other) = default;
  BGSpriteComponent& operator=(const BGSpriteComponent& other) = default;
  BGSpriteComponent(BGSpriteComponent&& other) = default;
  BGSpriteComponent& operator=(BGSpriteComponent&& other) = default;

  BGSpriteComponent(Actor* owner, int draw_order = 10);

  void Update(float delta_time) override;
  void Draw(SDL_Renderer* renderer) override;
  void SetBGTextures(const std::vector< SDL_Texture*> textures);

  void SetScreenSize(const Vector2DFloat& screen_size) { screensize_ = screen_size; }
  void SetScrollSpeed(float speed) { scroll_speed_ = speed; }
  float GetScrollSpeed() const { return scroll_speed_; }

private:
  struct BGTexture {
    SDL_Texture* texture;
    Vector2DFloat offset;
  };
  
  std::vector<BGTexture> bg_textures_;
  Vector2DFloat screensize_;
  float scroll_speed_ = 0.f;
};