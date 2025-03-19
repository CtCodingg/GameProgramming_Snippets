#include "BGSpriteComponent.hpp"
#include "Actor.hpp"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int draw_order) :
  SpriteComponent(owner, draw_order)
{}

void BGSpriteComponent::Update(float delta_time) {
  SpriteComponent::Update(delta_time);
  for (auto& bg : bg_textures_) {
		bg.offset.x += scroll_speed_ * delta_time;
		if (bg.offset.x < -screensize_.x) {
			bg.offset.x = (bg_textures_.size() - 1) * screensize_.x - 1;
		}
  }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer) {
	for (auto& bg : bg_textures_) {
		SDL_Rect r;
		r.w = static_cast<int>(screensize_.x);
		r.h = static_cast<int>(screensize_.y);
		r.x = static_cast<int>(owner_->GetPosition().x - r.w / 2 + bg.offset.x);
		r.y = static_cast<int>(owner_->GetPosition().y - r.h / 2 + bg.offset.y);
		SDL_RenderCopy(renderer, bg.texture, nullptr, &r);
	}
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*> textures) {
	int count = 0;
	for (auto tex : textures) {
		BGTexture temp;
		temp.texture = tex;
		temp.offset.x = count * screensize_.x;
		temp.offset.y = 0;
		bg_textures_.emplace_back(temp);
		count++;
	}
}
