#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"
#include "./game.h"

void game_cleanup(game* game) {
  free(game->player);

  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      free(game->aliens[i][j]);
    }
  }

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    free(game->bullets[i]);
  }
}

void game_pause(game* game) {
  game->state = PAUSED;
}

void game_resume(game* game) {
  game->state = RUNNING;
}

//initialize game
void game_init(game* game) {
  game->state = START;

  game->level = 1;

  //allocate memory to player
  game->player = malloc(sizeof(player));

  //spawn player
  player_spawn(game->player);  

  //spawn all aliens and move them once (because they spawn at the border and end up moving
  //down right at the beginning)
  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      game->aliens[i][j] = malloc(sizeof(alien));
      position pos = {.x = BORDER + j * SPRITE_SIZE, .y = 2*BORDER + i * SPRITE_SIZE};
      alien_spawn(game->aliens[i][j], pos, i);
      game->aliens[i][j]->direction = RIGHT;
      alien_move(game->aliens[i][j], game->aliens[i][j]->direction);
      alien_move(game->aliens[i][j], DOWN);
    }
  }

  //initialize all bullets and set them as inactive
  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    game->bullets[i] = malloc(sizeof(bullet));
    game->bullets[i]->status = INACTIVE;
  }
}

//update game
void game_update(game* game, int alienmovecounter) {

  //get position of first alien, to be used to check wall collisions
  position alienpos = game->aliens[0][0]->pos;

  //move all aliens once a second (since FPS=60),
  //moving them down and changing direction if they collide with walls
  if(alienmovecounter % 60 == 0) {
    for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
      for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
        if(alienpos.x < SPRITE_SIZE) {
          game->aliens[i][j]->direction = RIGHT;
          alien_move(game->aliens[i][j], DOWN);
        }
        else if(alienpos.x + (ALIEN_BLOCK_COLUMNS * SPRITE_SIZE) > WINDOW_WIDTH - SPRITE_SIZE) {
          game->aliens[i][j]->direction = LEFT;
          alien_move(game->aliens[i][j], DOWN);
        }
        alien_move(game->aliens[i][j], game->aliens[i][j]->direction);
      }
    }
  }

  //make a random aline fire a bullet every second
  if(alienmovecounter % 60 == 0) {
    int x = rand() % ALIEN_BLOCK_COLUMNS;
    int y = rand() % ALIEN_BLOCK_ROWS;
    if(game->aliens[y][x]->status == ALIVE) {
      bullet_spawn(ALIEN,game->aliens[y][x]->pos, game->bullets);
    }
  }

  //move all active bullets, check their collisions with aliens and player
  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    if(game->bullets[i]->status == INACTIVE) {
      continue;
    }
    else if(game->bullets[i]->status == ACTIVE) {
      bullet_move(game->bullets[i]);
      check_player_collision(game->bullets[i], game->player);
      check_alien_collision(game->bullets[i], game->aliens);
    }
    if(game->bullets[i]->status == ACTIVE && (game->bullets[i]->pos.y < 0 || game->bullets[i]->pos.y > WINDOW_HEIGHT)) {
      game->bullets[i]->status = INACTIVE;
    }
  }

  //check if player is going outside window
  if(game->player->pos.x < BORDER) {
    game->player->pos.x = BORDER;
  }
  if(game->player->pos.x + SPRITE_SIZE > WINDOW_WIDTH - BORDER) {
    game->player->pos.x = WINDOW_WIDTH - SPRITE_SIZE - BORDER;
  }

  int alien_left = 0;
  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      if(game->aliens[i][j]->status == ALIVE) {
        alien_left = 1;
      }
    }
  }
  if(alien_left == 0) {
    game->state = OVER;
  }
}
