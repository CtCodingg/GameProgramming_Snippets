#pragma once

#include "iActor.hpp"
#include "iGame.hpp"
#include "Vector.hpp"

#include <memory>
#include <vector>

class Actor : public iActor {
public:
  Actor() = delete;
  virtual ~Actor() = default;
  Actor(const Actor& other) = default;
  Actor& operator=(const Actor& other) = default;
  Actor(Actor&& other) = default;
  Actor& operator=(Actor&& other) = default;

  Actor(std::shared_ptr<iGame> game);

  void Update(float delta_time) override;
  void UpdateComponents(float delta_time) override;
  void UpdateActor(float delta_time) override;
  void AddComponent(std::shared_ptr<iComponent> component) override;
  void RemoveComponent(std::shared_ptr<iComponent> component) override;

  std::shared_ptr<iGame> GetGame() override { return game_; }
  std::vector<std::shared_ptr<iComponent>> GetComponents() override { return components_; }
  State GetState() override { return state_; }
  Vector2DFloat GetPosition() override { return position_; }
  float GetScale() override { return scale_; }
  float GetRotation() override { return rotation; }

private:
  std::shared_ptr<iGame> game_ = nullptr;
  std::vector<std::shared_ptr<iComponent>> components_;
  State state_;
  Vector2DFloat position_;
  float scale_ = 0.f;
  float rotation = 0.f;
};