#include "Game.hpp"

#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include <random>

Game::Game(int width, int height, bool single_player, int number_of_balls) :
  width_(width), height_(height), single_player_(single_player) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error("Error initializing sdl library");
  }

  window_ = SDL_CreateWindow("1_Basic2D", width, height, 0);
  if (window_ == nullptr) {
    throw std::runtime_error("Error creating window");
  }

  renderer_ = SDL_CreateRenderer(window_, nullptr);
  if (renderer_ == nullptr) {
    throw std::runtime_error("Error creating renderer");
  }

  paddle_pos_p0_.SetX(border_thickness_);
  paddle_pos_p0_.SetY(height_ / 2);
  if (!single_player_) {
    paddle_pos_p1_.SetX(width_ - border_thickness_ - paddle_width_);
    paddle_pos_p1_.SetY(height_ / 2);
  }

  const int range_from_pos_x = width_ / 5;
  const int range_to_pos_x = width_ - width_ / 5;
  const int range_from_pos_y = height_ / 5;
  const int range_to_pos_y = height_ - height_ / 5;

  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr_pos_x(range_from_pos_x, range_to_pos_x);
  std::uniform_int_distribution<int> distr_pos_y(range_from_pos_y, range_to_pos_y);

  for (int i = 0; i < number_of_balls; i++) {
    balls_.push_back(Ball{});
    balls_.at(i).pos.SetX(distr_pos_x(generator));
    balls_.at(i).pos.SetY(distr_pos_y(generator));
    balls_.at(i).vel.SetX(-width_ / 5);
    balls_.at(i).vel.SetY(height_ / 3);
  }
}

Game::~Game() {
  if(renderer_)
    SDL_DestroyRenderer(renderer_);
  if(window_)
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

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT:
        running_ = false;
        break;
    }
  }

  paddle_direction_p0_ = 0;
  paddle_direction_p1_ = 0;

  const bool* state = SDL_GetKeyboardState(nullptr);
  if (state[SDL_SCANCODE_ESCAPE]) {
    running_ = false;
  }
  if (state[SDL_SCANCODE_W]) {
    paddle_direction_p0_ -= 1;
  }
  if (state[SDL_SCANCODE_S]) {
    paddle_direction_p0_ += 1;
  }
  if (state[SDL_SCANCODE_UP]) {
    paddle_direction_p1_ -= 1;
  }
  if (state[SDL_SCANCODE_DOWN]) {
    paddle_direction_p1_ += 1;
  }
}

void Game::UpdateGame() {
  while (SDL_GetTicks() < (ticks_count_ + (1000 / target_framerat_))) {
    ;
  }
  float delta_time = (SDL_GetTicks() - ticks_count_) / 1000.f;
  ticks_count_ = SDL_GetTicks();
  delta_time = std::min(delta_time, 0.05f);

  for (auto& ball : balls_) {
    ball.pos.SetX(ball.pos.GetX() + ball.vel.GetX() * delta_time);
    ball.pos.SetY(ball.pos.GetY() + ball.vel.GetY() * delta_time);
  }

  const float paddle_speed = height_ / 2;
  if (paddle_direction_p0_ != 0) {
    paddle_pos_p0_.SetY(paddle_pos_p0_.GetY() + (paddle_direction_p0_ * paddle_speed * delta_time));
    if (paddle_pos_p0_.GetY() < (paddle_height_ / 2 + border_thickness_)) {
      paddle_pos_p0_.SetY(paddle_height_ / 2 + border_thickness_);
    }
    else if (paddle_pos_p0_.GetY() > (height_ - paddle_height_ / 2 - border_thickness_)) {
      paddle_pos_p0_.SetY(height_ - paddle_height_ / 2 - border_thickness_);
    }
  }

  for (auto& ball : balls_) {
    float diff = paddle_pos_p0_.GetY() - ball.pos.GetY();
    diff = (diff > 0.0f) ? diff : -diff;
    if (diff <= paddle_height_ / 2.0f && ball.pos.GetX() <= (border_thickness_ + paddle_width_) && ball.pos.GetX() >= (border_thickness_) && ball.vel.GetX() < 0.0f) {
      ball.vel.SetX(ball.vel.GetX() * -1.f);
    }
    else if (ball.pos.GetX() <= 0.0f) {
      running_ = false;
    }
    else if (ball.pos.GetX() >= (width_ - border_thickness_) && ball.vel.GetX() > 0.0f && single_player_) {
      ball.vel.SetX(ball.vel.GetX() * -1.f);
    }

    if (paddle_direction_p1_ != 0) {
      paddle_pos_p1_.SetY(paddle_pos_p1_.GetY() + (paddle_direction_p1_ * paddle_speed * delta_time));
      if (paddle_pos_p1_.GetY() < (paddle_height_ / 2 + border_thickness_)) {
        paddle_pos_p1_.SetY(paddle_height_ / 2 + border_thickness_);
      }
      else if (paddle_pos_p1_.GetY() > (height_ - paddle_height_ / 2 - border_thickness_)) {
        paddle_pos_p1_.SetY(height_ - paddle_height_ / 2 - border_thickness_);
      }
    }

    if (!single_player_) {
      diff = paddle_pos_p1_.GetY() - ball.pos.GetY();
      diff = (diff > 0.0f) ? diff : -diff;
      if (diff <= paddle_height_ / 2.0f && ball.pos.GetX() >= (width_ - border_thickness_ - paddle_width_) && ball.pos.GetX() <= (width_ - border_thickness_) && ball.vel.GetX() > 0.0f) {
        ball.vel.SetX(ball.vel.GetX() * -1.f);
      }
      else if (ball.pos.GetX() > width_) {
        running_ = false;
      }
    }

    if (ball.pos.GetY() <= border_thickness_ && ball.vel.GetY() < 0.0f) {
      ball.vel.SetY(ball.vel.GetY() * -1);
    }
    else if (ball.pos.GetY() >= (height_ - border_thickness_) && ball.vel.GetY() > 0.0f) {
      ball.vel.SetY(ball.vel.GetY() * -1);
    }
  }
}

void Game::GenerateOutput() {
  SDL_SetRenderDrawColorFloat(renderer_, 0, 0, 1.f, 1.f);
  SDL_RenderClear(renderer_);

  SDL_SetRenderDrawColorFloat(renderer_, 1.f, 1.f, 1.f, 1.f);
  const SDL_FRect wall_top{ 0, 0, width_, border_thickness_ };
  const SDL_FRect wall_right{ width_ - border_thickness_, 0, border_thickness_, height_};
  const SDL_FRect wall_bottom{ 0, height_ - border_thickness_, width_, border_thickness_ };
  const SDL_FRect wall_left{ 0, 0, border_thickness_, height_ };
  SDL_RenderFillRect(renderer_, &wall_top);
  SDL_RenderFillRect(renderer_, &wall_right);
  SDL_RenderFillRect(renderer_, &wall_bottom);
  SDL_RenderFillRect(renderer_, &wall_left);

  SDL_SetRenderDrawColorFloat(renderer_, 0.f, 0.f, 0.f, 1.f);
  for (auto& ball : balls_) {
    const SDL_FRect ballRect{ ball.pos.GetX() - ball_size_ / 2, ball.pos.GetY() - ball_size_ / 2, ball_size_, ball_size_ };
    SDL_RenderFillRect(renderer_, &ballRect);
  }
  const SDL_FRect paddle_p0{ paddle_pos_p0_.GetX() - paddle_width_ / 2, paddle_pos_p0_.GetY() - paddle_height_ / 2, paddle_width_, paddle_height_ };
  
  SDL_RenderFillRect(renderer_, &paddle_p0);
  if (!single_player_) {
    const SDL_FRect paddle_p1{ paddle_pos_p1_.GetX() - paddle_width_ / 2, paddle_pos_p1_.GetY() - paddle_height_ / 2, paddle_width_, paddle_height_ };
    SDL_RenderFillRect(renderer_, &paddle_p1);
  }

  SDL_RenderPresent(renderer_);
}
