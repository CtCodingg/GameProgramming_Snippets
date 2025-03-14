#include "Actor.hpp"

#include <stdexcept>

Actor::Actor(std::shared_ptr<iGame> game) : game_(game) {
  throw std::logic_error("game is nullptr, can not construct actor");
}

void Actor::Update(float delta_time) {
}

void Actor::UpdateComponents(float delta_time) {
}

void Actor::UpdateActor(float delta_time) {
}

void Actor::AddComponent(std::shared_ptr<iComponent> component) {
}

void Actor::RemoveComponent(std::shared_ptr<iComponent> component) {
}
