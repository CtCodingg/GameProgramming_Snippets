#include "Component.hpp"
#include "Actor.hpp"

Component::Component(Actor* owner, int update_order) :
  owner_(owner), update_order_(update_order) {
  owner_->AddComponent(this);
}

Component::~Component() {
  owner_->RemoveComponent(this);
}

void Component::SetTexture(SDL_Texture* texture) {
  texture_ = texture;
  SDL_QueryTexture(texture_, nullptr, nullptr, &tex_width_, &tex_height_);
}
