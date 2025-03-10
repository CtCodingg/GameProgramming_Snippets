#pragma once

#include <Common/iGame.hpp>
#include <SDL3/SDL.h>

#include <mutex>
#include <thread>

class Game final : public iGame {
public:
  Game() = delete;
  virtual ~Game();
  Game(const Game& other) = delete;
  Game& operator=(const Game& other) = delete;
  Game(Game&& other) = delete;
  Game& operator=(Game&& other) = delete;

  Game(int width, int height, int fps);

  void RunLoop() override;

protected:
  void ProcessInput() override;
  void UpdateGame() override;
  void GenerateOutput() override;

private:
  SDL_Window* window_ = nullptr;
  bool running_ = true;
  int fps_ = 60;
};