#include<stdio.h>
#include <stdlib.h>

//sdl headers
#include "SDL2/SDL.h"

//custom headers
#include "./helpers.h"
#include "./aliens.h"
#include "./bullets.h"
#include "./game.h"
#include "./player.h"
#include "./render.h"

int main() {
  
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);





  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  return 0;
}
