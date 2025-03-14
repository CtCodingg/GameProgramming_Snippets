#include "Component.hpp"

Component::Component(std::shared_ptr<iActor> owner, int update_order) :
  owner_(owner), update_order_(update_order) 
{}

void Component::Update(float delta_time) {
}

int Component::GetUpdateOrder() const {
  return update_order_;
}
