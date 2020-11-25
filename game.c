#include <stdio.h>

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

  player_spawn(game->player);  

  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      position pos = {.x = i * SPRITE_SIZE, .y = j * SPRITE_SIZE};
      alien_spawn(game->aliens[i][j], pos, i);
    }
  }
}
