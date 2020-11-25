#include<stdio.h>
#include <stdlib.h>

//sdl headers
#include "SDL2/SDL.h"

//custom headers
#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"
#include "./game.h"
#include "./render.h"

int main() {

  game* game0 = malloc(sizeof(game));
  game_init(game0);

  
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_Event event; 

  int quit = 0;

  while(1) {
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        quit = 1;
        break;
      }

      else if(event.type == SDL_KEYDOWN && game0->state == RUNNING) {
        switch(event.key.keysym.sym) {  //add things
          case SDLK_LEFT : player_move(game0->player, LEFT); break;
          case SDLK_RIGHT : player_move(game0->player, RIGHT); break;
          case SDLK_SPACE : bullet_spawn(PLAYER, game0->player->pos, game0->bullets); break;
          case SDLK_ESCAPE : game_pause(game0); break;
          default : {}
        }
      }
      else if(event.type == SDL_KEYDOWN && game0->state == PAUSED) {
      }
    }

    if(quit) {
      break;
    }

    game_update(game0);

  }


  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
