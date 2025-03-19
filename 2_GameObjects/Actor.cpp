#include "Actor.hpp"
#include "Game.hpp"
#include "Component.hpp"

#include <stdexcept>

Actor::Actor(Game* game) : game_(game) {
  if(!game_)
    throw std::logic_error("game is nullptr, can not construct actor");

	game->AddActor(this);
}

Actor::~Actor() {
	game_->RemoveActor(this);
	while (!components_.empty())
		delete components_.back();
}

void Actor::Update(float delta_time) {
  if (state_ == State::Active) {
    _UpdateComponents(delta_time);
    _UpdateActor(delta_time);
  }
}

void Actor::AddComponent(Component* component) {
	const int myOrder = component->GetUpdateOrder();
	auto iter = components_.begin();
	for (; iter != components_.end(); ++iter) {
		if (myOrder < (*iter)->GetUpdateOrder()) {
			break;
		}
	}
  components_.insert(iter, component);
}

void Actor::RemoveComponent(Component* component) {
	auto iter = std::find(components_.begin(), components_.end(), component);
	if (iter != components_.end()) {
		components_.erase(iter);
	}
}

void Actor::_UpdateComponents(float delta_time) {
  for (const auto& com : components_) {
    com->Update(delta_time);
  }
}

void Actor::_UpdateActor(float delta_time)
{
}
