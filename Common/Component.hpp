#pragma once

#include "iComponent.hpp"
#include "iActor.hpp"

#include <memory>

class Component : public iComponent {
public:
  Component() = delete;
  virtual ~Component() = default;
  Component(const Component& other) = default;
  Component& operator=(const Component& other) = default;
  Component(Component&& other) = default;
  Component& operator=(Component&& other) = default;

  Component(std::shared_ptr<iActor> owner, int update_order = 100);

  void Update(float delta_time) override;
  int GetUpdateOrder() const override;

private:
  std::shared_ptr<iActor> owner_ = nullptr;
  int update_order_ = 100;
};