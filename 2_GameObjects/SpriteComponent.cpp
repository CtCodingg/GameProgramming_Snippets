#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Math.hpp"
#include "Game.hpp"

SpriteComponent::SpriteComponent(Actor* owner, int draw_order) :
  Component(owner), draw_order_(draw_order) {
	owner_->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner_->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
	if (texture_) {
		SDL_Rect r;
		r.w = static_cast<int>(tex_width_ * owner_->GetScale());
		r.h = static_cast<int>(tex_height_ * owner_->GetScale());
		r.x = static_cast<int>(owner_->GetPosition().x - r.w / 2);
		r.y = static_cast<int>(owner_->GetPosition().y - r.h / 2);
		SDL_RenderCopyEx(renderer, texture_, nullptr, &r, -Math::ToDegrees(owner_->GetRotation()), nullptr, SDL_FLIP_NONE);
	}
}
