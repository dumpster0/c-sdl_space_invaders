#include <stdio.h>
#include <stdlib.h>

#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"
#include "./game.h"


void game_pause(game* game) {
  game->state = PAUSED;
}

void game_resume(game* game) {
  game->state = RUNNING;
}

void game_init(game* game) {
  game->state = RUNNING;

  game->level = 1;

  game->player = malloc(sizeof(player));

  player_spawn(game->player);  

  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      game->aliens[i][j] = malloc(sizeof(alien));
      position pos = {.x = i * SPRITE_SIZE, .y = j * SPRITE_SIZE};
      alien_spawn(game->aliens[i][j], pos, i);
      game->aliens[i][j]->direction = RIGHT;
    }
  }

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    game->bullets[i] = malloc(sizeof(bullet));
    game->bullets[i]->status = INACTIVE;
  }
}

void game_update(game* game) {

  position alienpos = game->aliens[0][0]->pos;

  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      if(alienpos.x < SPRITE_SIZE || alienpos.x > WINDOW_WIDTH - SPRITE_SIZE) {
        game->aliens[i][j]->direction = (game->aliens[i][j]->direction == LEFT) ? RIGHT : LEFT;
      }
      alien_move(game->aliens[i][j], game->aliens[i][j]->direction);
    }
  }

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    if(game->bullets[i]->status == INACTIVE) {
      continue;
    }
    else if(game->bullets[i]->status == ACTIVE) {
      bullet_move(game->bullets[i]);
      check_player_collision(game->bullets[i], game->player);
      check_alien_collision(game->bullets[i], game->aliens);
    }
  }
}
