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
      position pos = {.x = BORDER + j * SPRITE_SIZE, .y = BORDER + i * SPRITE_SIZE};
      alien_spawn(game->aliens[i][j], pos, i);
      game->aliens[i][j]->direction = RIGHT;
      alien_move(game->aliens[i][j], game->aliens[i][j]->direction);
    }
  }

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    game->bullets[i] = malloc(sizeof(bullet));
    game->bullets[i]->status = INACTIVE;
  }
}

void game_update(game* game, int alienmovecounter) {

  position alienpos = game->aliens[0][0]->pos;

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

  //check if player is going outside window
  if(game->player->pos.x < BORDER) {
    game->player->pos.x = BORDER;
  }
  if(game->player->pos.x + SPRITE_SIZE > WINDOW_WIDTH - BORDER) {
    game->player->pos.x = WINDOW_WIDTH - SPRITE_SIZE - BORDER;
  }
}
