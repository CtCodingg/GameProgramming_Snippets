#pragma once

#include "Vector.hpp"

#include <memory>
#include <vector>

class Game;
class Component;

class Actor {
public:
  enum class State {
    Active,
    Paused,
    Dead
  };

  Actor() = delete;
  virtual ~Actor() = default;
  Actor(const Actor& other) = default;
  Actor& operator=(const Actor& other) = default;
  Actor(Actor&& other) = default;
  Actor& operator=(Actor&& other) = default;

  Actor(std::shared_ptr<Game> game);

  void Update(float delta_time);
  void UpdateComponents(float delta_time);
  void UpdateActor(float delta_time);
  void AddComponent(std::shared_ptr<Component> component);
  void RemoveComponent(std::shared_ptr<Component> component);

  std::shared_ptr<Game> GetGame() { return game_; }
  std::vector<std::shared_ptr<Component>> GetComponents() { return components_; }
  State GetState() { return state_; }
  Vector2DFloat GetPosition() { return position_; }
  float GetScale() { return scale_; }
  float GetRotation() { return rotation; }

private:
  std::shared_ptr<Game> game_ = nullptr;
  std::vector<std::shared_ptr<Component>> components_;
  State state_;
  Vector2DFloat position_;
  float scale_ = 0.f;
  float rotation = 0.f;
};