#pragma once

#include <SDL/SDL.h>

#include <mutex>
#include <thread>

class Game {
public:
  Game() = delete;
  virtual ~Game();
  Game(const Game& other) = delete;
  Game& operator=(const Game& other) = delete;
  Game(Game&& other) = delete;
  Game& operator=(Game&& other) = delete;

  Game(int width, int height, int fps);

  void RunLoop();

protected:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

private:
  SDL_Window* window_ = nullptr;
  bool running_ = true;
  int fps_ = 60;
};