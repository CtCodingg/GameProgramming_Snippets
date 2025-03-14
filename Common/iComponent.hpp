#pragma once

class iComponent {
public:
  iComponent() = default;
  virtual ~iComponent() = default;
  iComponent(const iComponent& other) = default;
  iComponent& operator=(const iComponent& other) = default;
  iComponent(iComponent&& other) = default;
  iComponent& operator=(iComponent&& other) = default;

  virtual void Update(float delta_time) = 0;
  virtual int GetUpdateOrder() const = 0;
};