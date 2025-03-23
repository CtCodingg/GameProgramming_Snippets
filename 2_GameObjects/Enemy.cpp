#include "Enemy.hpp"
#include "Game.hpp"
#include "AnimSpriteComponent.hpp"
#include "Vector.hpp"

#include <random>
#include <map>

enum class IMAGE_PATH {
	STANDARD = 0,
	LAURA = 1,
	SCHILLER = 2
};

Enemy::Enemy(Game* game) : Actor(game) {
	AnimSpriteComponent* asc = new AnimSpriteComponent(this);
	
	std::map<IMAGE_PATH, std::string> img_paths;
	img_paths[IMAGE_PATH::STANDARD] = "Assets/Enemy01.png";
	img_paths[IMAGE_PATH::LAURA] = "Assets/Laura.png";
	img_paths[IMAGE_PATH::SCHILLER] = "Assets/Schiller.png";

	std::random_device rand_dev;
	std::mt19937 generator(rand_dev());
	std::uniform_int_distribution<int> distr_pos_y(0, 2);
	
	std::vector<SDL_Texture*> anims = {
		game_->GetTexture(img_paths[(IMAGE_PATH)distr_pos_y(generator)])
	};
	asc->SetAnimTextures(anims);
}

Enemy::~Enemy() {
	game_->RemoveEnemy(this);
}

void Enemy::_UpdateActor(float delta_time) {
	Actor::_UpdateActor(delta_time);

	position_.x += right_speed_ * delta_time;
	position_.y += down_speed * delta_time;
	if (position_.x < 0.0f || position_.x > game_->GetWinWidth()) {
		state_ = State::Dead;
	}

	if (position_.y <= 0.0f) {
		down_speed *= -1;
	}
	else if (position_.y > game_->GetWinHeight()) {
		down_speed *= -1;
	}
}
