#include "SpriteComponent.hpp"
#include "Actor.hpp"

SpriteComponent::SpriteComponent(std::shared_ptr<Actor> owner, int update_order, int draw_order) :
  Component(owner, update_order), draw_order_(draw_order)
{}

void SpriteComponent::Update(float delta_time) {
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
}
