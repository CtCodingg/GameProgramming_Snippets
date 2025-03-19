#pragma once

#include "Vector.hpp"

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
  virtual ~Actor();
  Actor(const Actor& other) = default;
  Actor& operator=(const Actor& other) = default;
  Actor(Actor&& other) = default;
  Actor& operator=(Actor&& other) = default;

  Actor(Game* game);

  void Update(float delta_time);
  void AddComponent(Component* component);
  void RemoveComponent(Component* component);

  Game* GetGame() { return game_; }
  std::vector<Component*> GetComponents() { return components_; }
  State GetState() { return state_; }
  void SetState(State state) { state_ = state; }
  Vector2DFloat GetPosition() { return position_; }
  void SetPosition(Vector2DFloat pos) { position_ = pos; }
  float GetScale() { return scale_; }
  void SetScale(float scale) { scale_ = scale; }
  float GetRotation() { return rotation_; }
  void SetRotation(float rot) { rotation_ = rot; }

protected:
  void _UpdateComponents(float delta_time);
  virtual void _UpdateActor(float delta_time);

  Game* game_ = nullptr;
  std::vector<Component*> components_;
  State state_ = State::Active;
  Vector2DFloat position_;
  float scale_ = 0.f;
  float rotation_ = 0.f;
};