#include "Ship.hpp"
#include "Game.hpp"
#include "AnimSpriteComponent.hpp"
#include "Vector.hpp"

Ship::Ship(Game* game) : Actor(game) {
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	std::vector<SDL_Texture*> anims = {
		game->GetTexture("Assets/Ship01.png"),
		game->GetTexture("Assets/Ship02.png"),
		game->GetTexture("Assets/Ship03.png"),
		game->GetTexture("Assets/Ship04.png"),
	};
	asc->SetAnimTextures(anims);
	laser_texture_ = game->GetTexture("Assets/Laser.png");
}

void Ship::ProcessKeyboard(const uint8_t* state) {
	right_speed_ = 0.0f;
	down_speed = 0.0f;
	laser_enabled_ = false;

	if (state[SDL_SCANCODE_D]) {
		right_speed_ += 250.0f;
	}
	if (state[SDL_SCANCODE_A]) {
		right_speed_ -= 250.0f;
	}

	if (state[SDL_SCANCODE_S]) {
		down_speed += 300.0f;
	}
	if (state[SDL_SCANCODE_W]) {
		down_speed -= 300.0f;
	}
	if (state[SDL_SCANCODE_L]) {
		laser_enabled_ = true;
	}
}

void Ship::_UpdateActor(float delta_time) {
	Actor::_UpdateActor(delta_time);

	Vector2DFloat pos = GetPosition();
	pos.x += right_speed_ * delta_time;
	pos.y += down_speed * delta_time;
	if (pos.x < 25.0f) {
		pos.x = 25.0f;
	}
	else if (pos.x > 800.f) {
		pos.x = 800.f;
	} 
	
	if (pos.y < 25.0f) {
		pos.y = 25.0f;
	} 
	else if (pos.y > 1060.f) {
		pos.y = 1060.f;
	}

	SetPosition(pos);
}

void Ship::Draw(SDL_Renderer* renderer) {
	if (laser_texture_ && laser_enabled_) {
		SDL_Rect r;
		r.w = static_cast<int>(game_->GetWinWidth() - position_.x);
		r.h = static_cast<int>(laser_height_);
		r.x = static_cast<int>(position_.x);
		r.y = static_cast<int>(position_.y - laser_height_ / 2);
		SDL_RenderCopyEx(renderer, laser_texture_, nullptr, &r, 0, nullptr, SDL_FLIP_NONE);
	}
}