#pragma once

#include "Actor.hpp"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

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
	void Draw(SDL_Renderer* renderer);
	int GetLaserHeightMin() const { return position_.y - laser_height_ / 2; };
	int GetLaserHeightMax() const  { return position_.y + laser_height_ / 2; };
	bool IsLaserEnabled() const { return laser_enabled_; }

protected:
	void _UpdateActor(float delta_time) override;

private:
	float right_speed_ = 0.f;
	float down_speed = 0.f;
	bool laser_enabled_ = false;
	int laser_height_ = 20;
	SDL_Texture* laser_texture_ = nullptr;
};