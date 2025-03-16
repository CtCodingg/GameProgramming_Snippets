#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

#include <string>

class SDL_TextureLoader {
  SDL_TextureLoader() = delete;
  virtual ~SDL_TextureLoader() = delete;
  SDL_TextureLoader(const SDL_TextureLoader& other) = delete;
  SDL_TextureLoader& operator=(const SDL_TextureLoader& other) = delete;
  SDL_TextureLoader(SDL_TextureLoader&& other) = delete;
  SDL_TextureLoader& operator=(SDL_TextureLoader&& other) = delete;

  static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const std::string & filename);
};