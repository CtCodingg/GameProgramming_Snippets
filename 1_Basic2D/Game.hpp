#pragma once

#include <Common/iGame.hpp>
#include <Common/Vector2D.hpp>

#include <SDL3/SDL.h>

#include <vector>

struct Ball {
  Vector2D pos;
  Vector2D vel;
};

class Game final : public iGame {
public:
  Game() = delete;
  virtual ~Game();
  Game(const Game& other) = delete;
  Game& operator=(const Game& other) = delete;
  Game(Game&& other) = delete;
  Game& operator=(Game&& other) = delete;

  Game(int width, int height, bool single_player, int number_of_balls);

  void RunLoop() override;

protected:
  void ProcessInput() override;
  void UpdateGame() override;
  void GenerateOutput() override;

private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  bool running_ = true;
  int width_ = 1920;
  int height_ = 1080;

  const int border_thickness_ = 15;
  const int ball_size_ = 15;
  const int paddle_width_ = 15;
  const int paddle_height_ = 80;
  Vector2D paddle_pos_p0_;
  Vector2D paddle_pos_p1_;
  std::vector<Ball> balls_;

  Uint64 ticks_count_ = 0;
  Uint8 target_framerat_ = 60;

  int paddle_direction_p0_ = 0;
  int paddle_direction_p1_ = 0;

  bool single_player_ = true;
};