#include "Component.hpp"
#include "Actor.hpp"

Component::Component(std::shared_ptr<Actor> owner, int update_order) :
  owner_(owner), update_order_(update_order) 
{}

int Component::GetUpdateOrder() const {
  return update_order_;
}

void Component::SetTexture(SDL_Texture* texture) {
  texture_ = texture;
  SDL_QueryTexture(texture_, nullptr, nullptr, &tex_width_, &tex_height_);
}

int Component::GetTextureWidth() const {
  return tex_width_;
}

int Component::GetTextureHeight() const {
  return tex_height_;
}
