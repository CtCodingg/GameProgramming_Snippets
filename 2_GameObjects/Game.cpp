#include "Game.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <random>

Game::Game(int width, int height, bool single_player, int number_of_balls) :
  width_(width), height_(height) {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw std::runtime_error("Error initializing sdl library");
  }

  window_ = SDL_CreateWindow("0_HelloWorld", 0, 0, width, height, 0);
  if (window_ == nullptr) {
    throw std::runtime_error("Error creating window");
  }

  renderer_ = SDL_CreateRenderer(window_, 0, 0);
  if (renderer_ == nullptr) {
    throw std::runtime_error("Error creating renderer");
  }
}

Game::~Game() {
  if (renderer_)
    SDL_DestroyRenderer(renderer_);
  if (window_)
    SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::RunLoop() {
  while (running_) {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::AddActor(std::shared_ptr<Actor> actor) {
  if (updating_actors_) {
    pending_actors_.emplace_back(actor);
  }
  else {
    actors_.emplace_back(actor);
  }
}

void Game::RemoveActor(std::shared_ptr<Actor> actor) {
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

void Game::AddSprite(std::shared_ptr<SpriteComponent> sprite) {
  int draw_order = sprite->GetDrawOrder();
  auto iter = sprites_.begin();
  for (; iter != sprites_.end(); ++iter) {
    if (draw_order < (*iter)->GetDrawOrder()) {
      break;
    }
  }
  sprites_.insert(iter, sprite);
}

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running_ = false;
      break;
    }
  }

  const uint8_t* state = SDL_GetKeyboardState(nullptr);
  if (state[SDL_SCANCODE_ESCAPE]) {
    running_ = false;
  }
}

void Game::UpdateGame() {
  while (SDL_GetTicks() < (ticks_count_ + (1000 / target_framerat_))) {
    ;
  }
  float delta_time = (SDL_GetTicks() - ticks_count_) / 1000.f;
  ticks_count_ = SDL_GetTicks();
  delta_time = std::min(delta_time, 0.05f);

  updating_actors_ = true;
  for (auto actor : actors_) {
    actor->Update(delta_time);
  }
  updating_actors_ = false;

  for (auto pending : pending_actors_) {
    actors_.emplace_back(pending);
  }
  pending_actors_.clear();

  std::vector<std::shared_ptr<Actor>> deadActors;
  for (auto actor : actors_) {
    if (actor->GetState() == Actor::State::Dead) {
      deadActors.emplace_back(actor);
    }
  }

  for (auto actor : deadActors) {
    auto iter = std::find(actors_.begin(), actors_.end(), actor);
    if (iter != actors_.end()) {
      actors_.erase(iter);
    }
  }
}

void Game::GenerateOutput() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
  SDL_RenderClear(renderer_);

  for (auto sprite : sprites_) {
    sprite->Draw(renderer_);
  }

  SDL_RenderPresent(renderer_);
}
