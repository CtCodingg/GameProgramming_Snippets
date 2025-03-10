#include "Game.hpp"
#include <iostream>
#include <stdexcept>
#include <stdint.h>

Game::Game(int width, int height, int fps) : fps_(fps) {
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error("Error initializing sdl library");
  }

  window_ = SDL_CreateWindow("0_HelloWorld", width, height, 0);
  if (window_ == nullptr) {
    throw std::runtime_error("Error creating window");
  }
}

Game::~Game() {
  SDL_DestroyWindow(window_);
  SDL_Quit();
}

void Game::RunLoop() {
  while (running_) {
    ProcessInput();
    UpdateGame();
    GenerateOutput();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000 / fps_));
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

  const bool* state = SDL_GetKeyboardState(nullptr);
  if (state[SDL_SCANCODE_ESCAPE]) {
    running_ = false;
  }
}

void Game::UpdateGame() {
}

void Game::GenerateOutput() {
}
