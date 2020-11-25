#include <stdio.h>

#include "./helpers.h"
#include "./player.h"

void player_move(player* player, direction direction) {
  
}

void player_spawn(player* player) {
  position pos = {.x = PLAYER_STARTING_X, .y = PLAYER_STARTING_Y};

  player->lives = 3;
  player->pos = pos;
}
