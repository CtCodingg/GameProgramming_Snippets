#pragma once

#include "Actor.hpp"

class Enemy : public Actor
{
public:
	Enemy() = delete;
	virtual ~Enemy();
	Enemy(const Enemy& other) = default;
	Enemy& operator=(const Enemy& other) = default;
	Enemy(Enemy&& other) = default;
	Enemy& operator=(Enemy&& other) = default;

	Enemy(Game* game);

	float GetRightSpeed() const { return right_speed_; }
	void SetRightSpeed(float speed) { right_speed_ = speed; }
	float GetDownSpeed() const { return down_speed; }
	void SetDownSpeed(float speed) { down_speed = speed; }

protected:
	void _UpdateActor(float delta_time) override;

private:
	float right_speed_ = 0.f;
	float down_speed = 0.f;
};