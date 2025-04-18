#include "Game.hpp"

#include "BGSpriteComponent.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <random>
#include <algorithm>

Game::Game(int width, int height) : win_width_(width), win_height_(height) {
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
    throw std::runtime_error("Error initializing sdl library");
  }

  window_ = SDL_CreateWindow("0_HelloWorld", 100, 100, width, height, 0);
  if (window_ == nullptr) {
    throw std::runtime_error("Error creating window");
  }

  renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer_ == nullptr) {
    throw std::runtime_error("Error creating renderer");
  }

  if (IMG_Init(IMG_INIT_PNG) == 0) {
    throw std::runtime_error("Error initializing sdl_image");
  }

  _LoadData();
  ticks_count_ = SDL_GetTicks();
}

Game::~Game() {
  _UnloadData();
  IMG_Quit();
  if (renderer_)
    SDL_DestroyRenderer(renderer_);
  if (window_)
    SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::RunLoop() {
  start_timepoint_ = std::chrono::steady_clock::now();
  while (is_running_) {
    _ProcessInput();
    _UpdateGame();
    _GenerateOutput();
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - start_timepoint_).count() > 5) {
      level_++;
      start_timepoint_ = std::chrono::steady_clock::now();
    }
  }
}

void Game::AddActor(Actor* actor) {
  if (updating_actors_) {
    pending_actors_.emplace_back(actor);
  }
  else {
    actors_.emplace_back(actor);
  }
}

void Game::RemoveActor(Actor* actor) {
  auto iter = std::find(pending_actors_.begin(), pending_actors_.end(), actor);
  if (iter != pending_actors_.end()) {
    std::iter_swap(iter, pending_actors_.end() - 1);
    pending_actors_.pop_back();
  }

  iter = std::find(actors_.begin(), actors_.end(), actor);
  if (iter != actors_.end()) {
    std::iter_swap(iter, actors_.end() - 1);
    actors_.pop_back();
  }
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
  SDL_Texture* tex = nullptr;

  auto iter = textures_.find(fileName);
  if (iter != textures_.end()) {
    tex = iter->second;
  }
  else {
    SDL_Surface* surf = IMG_Load(fileName.c_str());
    if (!surf) {
      SDL_Log("Failed to load texture file %s", fileName.c_str());
      return nullptr;
    }

    tex = SDL_CreateTextureFromSurface(renderer_, surf);
    SDL_FreeSurface(surf);
    if (!tex) {
      SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
      return nullptr;
    }

    textures_.emplace(fileName.c_str(), tex);
  }
  return tex;
}

void Game::_LoadData() {
  ship_ = new Ship(this);
  ship_->SetPosition(Vector2DFloat(100.0f, win_height_ / 2));
  ship_->SetScale(1.5f);

  const int number_of_enemies = startNumberOfEnemies_;
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr_pos_y(10, GetWinHeight() - 10);
  std::uniform_int_distribution<int> speed_right(-500, -200);
  std::uniform_int_distribution<int> speed_down(-200, 200);
  for (int i = 0; i <= number_of_enemies; i++) {
    enemy_.push_back(new Enemy(this));
    enemy_.at(i)->SetPosition(Vector2DFloat{ GetWinWidth(), (float)distr_pos_y(generator) });
    enemy_.at(i)->SetScale(1.5f);
    enemy_.at(i)->SetRightSpeed((float)speed_right(generator));
    enemy_.at(i)->SetDownSpeed((float)speed_down(generator));
  }

  Actor* tmp = new Actor(this);
  tmp->SetPosition(Vector2DFloat(win_width_ / 2, win_height_ / 2));

  BGSpriteComponent* bg = new BGSpriteComponent(tmp);
  bg->SetScreenSize(Vector2DFloat(win_width_, win_height_));
  std::vector<SDL_Texture*> bgtexs = {
    GetTexture("Assets/Farback01.png"),
    GetTexture("Assets/Farback02.png")
  };
  bg->SetBGTextures(bgtexs);
  bg->SetScrollSpeed(-100.0f);

  bg = new BGSpriteComponent(tmp, 50);
  bg->SetScreenSize(Vector2DFloat(win_width_, win_height_));
  bgtexs = {
    GetTexture("Assets/Stars.png"),
    GetTexture("Assets/Stars.png")
  };
  bg->SetBGTextures(bgtexs);
  bg->SetScrollSpeed(-200.0f);
}

void Game::_UnloadData() {
  for (auto i : textures_) {
    SDL_DestroyTexture(i.second);
  }
  textures_.clear();
}

void Game::AddSprite(SpriteComponent* sprite) {
  int draw_order = sprite->GetDrawOrder();
  auto iter = sprites_.begin();
  for (; iter != sprites_.end(); ++iter) {
    if (draw_order < (*iter)->GetDrawOrder()) {
      break;
    }
  }
  sprites_.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
  size_t i = 0;
  for (; i < sprites_.size(); i++) {
    if (sprite == sprites_.at(i)) {
      break;
    }
  }
  sprites_.erase(sprites_.begin() + i);
}

void Game::RemoveEnemy(Enemy* enemy) {
  size_t i = 0;
  for (; i < enemy_.size(); i++) {
    if (enemy == enemy_.at(i)) {
      break;
    }
  }
  enemy_.erase(enemy_.begin() + i);
}

void Game::_ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      is_running_ = false;
      break;
    }
  }

  const Uint8* state = SDL_GetKeyboardState(NULL);
  if (state[SDL_SCANCODE_ESCAPE]) {
    is_running_ = false;
  }

  ship_->ProcessKeyboard(state);
}

void Game::_UpdateGame() {
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count_ + 16))
    ;

  float deltaTime = (SDL_GetTicks() - ticks_count_) / 1000.0f;
  if (deltaTime > 0.05f) {
    deltaTime = 0.05f;
  }
  ticks_count_ = SDL_GetTicks();

  updating_actors_ = true;
  for (auto actor : actors_) {
    actor->Update(deltaTime);
  }
  updating_actors_ = false;

  for (auto pending : pending_actors_) {
    actors_.emplace_back(pending);
  }
  pending_actors_.clear();

  std::vector<Actor*> deadActors;
  for (auto actor : actors_) {
    if (actor->GetState() == Actor::State::Dead) {
      deadActors.emplace_back(actor);
    }
  }

  for (auto actor : deadActors) {
    delete actor;
  }

  while (ActualNumberOfEnemies() < (startNumberOfEnemies_ + 2 * level_)) {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr_pos_y(10, GetWinHeight() - 10);
    std::uniform_int_distribution<int> speed_right(-500 + 10 * level_, -200);
    std::uniform_int_distribution<int> speed_down(-200 + 10 * level_, 200 + 10 * level_);
    Enemy* enemy = new Enemy(this);
    enemy->SetPosition(Vector2DFloat{ GetWinWidth(), (float)distr_pos_y(generator) });
    enemy->SetScale(1.5f);
    enemy->SetRightSpeed((float)speed_right(generator));
    enemy->SetDownSpeed((float)speed_down(generator));
    enemy_.push_back(enemy);
  }

  constexpr int threshold = 80;
  for (const auto& enemy : enemy_) {
    if ((enemy->GetPosition().x - threshold < ship_->GetPosition().x) && (ship_->GetPosition().x < enemy->GetPosition().x + threshold) &&
      ((enemy->GetPosition().y - threshold < ship_->GetPosition().y) && (ship_->GetPosition().y < enemy->GetPosition().y + threshold))) {
      is_running_ = false;
    }

    if ((ship_->IsLaserEnabled()) && (ship_->GetLaserHeightMin() < enemy->GetPosition().y) && (enemy->GetPosition().y < ship_->GetLaserHeightMax())) {
      enemy->SetState(Actor::State::Dead);
    }
  }
}

void Game::_GenerateOutput() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);

  for (auto sprite : sprites_) {
    sprite->Draw(renderer_);
  }
  ship_->Draw(renderer_);

  SDL_RenderPresent(renderer_);
}
