#pragma once

#include "SpriteComponent.hpp"
#include "Actor.hpp"
#include "Component.hpp"
#include "Ship.hpp"
#include "Enemy.hpp"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>

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

  Game(int width, int height);

  void RunLoop();
  void AddActor(Actor* actor);
  void AddSprite(SpriteComponent* sprite);
  void RemoveSprite(SpriteComponent* sprite);
  void RemoveActor(Actor* actor);

  SDL_Texture* GetTexture(const std::string& fileName);

  float GetWinWidth() const { return win_width_; }
  float GetWinHeight() const { return win_height_; }

  int ActualNumberOfEnemies() { return enemy_.size(); }
  void RemoveEnemy(Enemy* enemy);

protected:
  void _ProcessInput();
  void _UpdateGame();
  void _GenerateOutput();
  void _LoadData();
  void _UnloadData();

private:
  std::unordered_map<std::string, SDL_Texture*> textures_;

  std::vector<Actor*> actors_;
  std::vector<Actor*> pending_actors_;

  std::vector<SpriteComponent*> sprites_;

  SDL_Window* window_ = nullptr;
  SDL_Renderer* renderer_ = nullptr;
  Uint32 ticks_count_ = 0;
  bool is_running_ = true;
  bool updating_actors_ = false;
  float win_width_ = 0.f;
  float win_height_ = 0.f;

  Ship* ship_ = nullptr;
  std::vector<Enemy*> enemy_;
  int startNumberOfEnemies_ = 5;

  int level_ = 1;
  std::chrono::steady_clock::time_point start_timepoint_;
};