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
}

void Ship::ProcessKeyboard(const uint8_t* state) {
	right_speed_ = 0.0f;
	down_speed = 0.0f;

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
