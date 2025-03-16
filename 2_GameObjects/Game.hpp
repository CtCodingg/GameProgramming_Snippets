#pragma once

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Component.hpp"

#include <SDL/SDL.h>

#include <vector>
#include <memory>

struct Ball {
  Vector2DFloat pos;
  Vector2DFloat vel;
};

class Game {
public:
  Game() = delete;
  virtual ~Game();
  Game(const Game& other) = delete;
  Game& operator=(const Game& other) = delete;
  Game(Game&& other) = delete;
  Game& operator=(Game&& other) = delete;

  Game(int width, int height, bool single_player, int number_of_balls);

  void RunLoop();
  void AddActor(std::shared_ptr<Actor> actor);
  void RemoveActor(std::shared_ptr<Actor> actor);
  void AddSprite(std::shared_ptr<SpriteComponent> sprite);

protected:
  void ProcessInput();
  void UpdateGame();
  void GenerateOutput();

private:
  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  bool running_ = true;
  int width_ = 1920;
  int height_ = 1080;

  Uint64 ticks_count_ = 0;
  Uint8 target_framerat_ = 60;

  bool updating_actors_ = false;
  std::vector<std::shared_ptr<Actor>> actors_;
  std::vector<std::shared_ptr<Actor>> pending_actors_;
  std::vector<std::shared_ptr<SpriteComponent>> sprites_;
};