#include<stdio.h>
#include <stdlib.h>
#include <time.h>

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

  //initialize the game variable and allocate memory to it
  //this holds everything related to the current game,
  //including state, level, player, aliens, and bullets
  game* game0 = malloc(sizeof(game));
  game_init(game0);

  
  //initialize the SDL_VIDEO subsystem
  //also automatically inits the 2 default SDL subsystems, file i/o and threading
  SDL_Init(SDL_INIT_VIDEO);

  //create the renderer and window
  SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  //create event to listen for keypresses and SDL_QUIT
  SDL_Event event; 

  //draw a black screen, just in case
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  int playerleft = 0;
  int playerright = 0;
  int quit = 0;
  int starttimer;
  int alienmovecounter = 0;

  while(1) {

    //initializing startimer for every iteration to count the time taken
    //by the loop, to facilitate FPS capping using SDL_Delay at the end
    //of the loop
    starttimer = SDL_GetTicks();

    ++alienmovecounter;

    //polling for event started
    while(SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        quit = 1;
        break;
      }

      //checking keypresses while game is running
      else if(event.type == SDL_KEYDOWN && game0->state == RUNNING) {
        
        if(event.key.keysym.sym == SDLK_LEFT) {
          playerright = 0;
          playerleft = 1;
        }
        else if(event.key.keysym.sym == SDLK_RIGHT) {
          playerleft = 0;
          playerright = 1;
        }
        if(event.key.keysym.sym == SDLK_SPACE) {
          bullet_spawn(PLAYER, game0->player->pos, game0->bullets);
        }
        if(event.key.keysym.sym == SDLK_ESCAPE) {
          game_pause(game0);
        }
      }

      //checking keypresses in pause menu
      else if(event.type == SDL_KEYDOWN && game0->state == PAUSED) {
      }

      //checking keyups while game is running
      else if(event.type == SDL_KEYUP && game0->state == RUNNING) {
        if(event.key.keysym.sym == SDLK_LEFT) {
          playerleft = 0;
        }
        if(event.key.keysym.sym == SDLK_RIGHT) {
          playerright = 0;
        }
      }
    } //polling for event ended

    //break out from gameloop if quit
    if(quit) {
      break;
    }
    
    //do player movement based on values of variables
    //putting player_move() directly in the event polling loop causes it to be called
    //irregularly and upredictably, making movement choppy
    if(playerleft == 1) {
      player_move(game0->player, LEFT);
    }
    if(playerright == 1) {
      player_move(game0->player, RIGHT);
    }

    //render background
    render_bg(renderer);

    //update entire game variable
    game_update(game0, alienmovecounter);
    //render player, aliens, and bullets using the game variable
    render_game(game0, renderer, window);
    //present renderer
    SDL_RenderPresent(renderer);

    //cap framerate to FPS
    //1000/FPS is the number of ms for one frame
    //if current iteration of the loop has run for less time than
    //this (running time is given by SDL_GetTicks() - starttimer),
    //then we delay until that time
    if(SDL_GetTicks() - starttimer < 1000/FPS) {
      SDL_Delay(1000/FPS - (SDL_GetTicks() - starttimer));
    }
  }


  //clean up renderer and window
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);

  SDL_Quit();

  return 0;
}
