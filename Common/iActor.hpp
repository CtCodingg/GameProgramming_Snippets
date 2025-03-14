#pragma once

#include "Vector.hpp"

#include <memory>
#include <vector>

class iComponent;
class iGame;

class iActor {
public:
  
  enum class State {
    Active,
    Paused,
    Dead
  };

  iActor() = default;
  virtual ~iActor() = default;
  iActor(const iActor& other) = default;
  iActor& operator=(const iActor& other) = default;
  iActor(iActor&& other) = default;
  iActor& operator=(iActor&& other) = default;

  virtual void Update(float delta_time) = 0;
  virtual void UpdateComponents(float delta_time) = 0;
  virtual void UpdateActor(float delta_time) = 0;
  virtual void AddComponent(std::shared_ptr<iComponent> component) = 0;
  virtual void RemoveComponent(std::shared_ptr<iComponent> component) = 0;

  virtual std::shared_ptr<iGame> GetGame() = 0;
  virtual std::vector<std::shared_ptr<iComponent>> GetComponents() = 0;
  virtual State GetState() = 0;
  virtual Vector2DFloat GetPosition() = 0;
  virtual float GetScale() = 0;
  virtual float GetRotation() = 0;
};