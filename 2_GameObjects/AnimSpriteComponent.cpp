#include "AnimSpriteComponent.hpp"
#include "Actor.hpp"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int draw_order) :
  SpriteComponent(owner, draw_order)
{}

void AnimSpriteComponent::Update(float delta_time) {
	SpriteComponent::Update(delta_time);

	if (anim_textures_.size() > 0) {
		curr_frame_ += anim_fps_ * delta_time;
		while (curr_frame_ >= anim_textures_.size()) {
			curr_frame_ -= anim_textures_.size();
		}
		SetTexture(anim_textures_.at(static_cast<int>(curr_frame_)));
	}
}

void AnimSpriteComponent::SetAnimTextures(const std::vector<SDL_Texture*> textures) {
	anim_textures_ = textures;
	if (anim_textures_.size() > 0) {
		curr_frame_ = 0.f;
		SetTexture(anim_textures_.at(0));
	}
}
