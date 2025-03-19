#pragma once

#include "Actor.hpp"

class Ship : public Actor
{
public:
	Ship() = delete;
	virtual ~Ship() = default;
	Ship(const Ship& other) = default;
	Ship& operator=(const Ship& other) = default;
	Ship(Ship&& other) = default;
	Ship& operator=(Ship&& other) = default;

	Ship(Game* game);
	void ProcessKeyboard(const uint8_t* state);

	float GetRightSpeed() const { return right_speed_; }
	float GetDownSpeed() const { return down_speed; }

protected:
	void _UpdateActor(float delta_time) override;

private:
	float right_speed_ = 0.f;
	float down_speed = 0.f;
};