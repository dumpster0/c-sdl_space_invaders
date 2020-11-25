#include <stdio.h>
#include <stdlib.h>

#include "./helpers.h"
#include "./player.h"

void player_move(player* player, direction direction) {
  position newpos = player->pos;

  switch(direction) {
    case LEFT : newpos.x -= PLAYER_SPEED;
    case RIGHT : newpos.x += PLAYER_SPEED;
    default : {}
  }

  player->pos = newpos;
}

void player_spawn(player* player) {
  position pos = {.x = PLAYER_STARTING_X, .y = PLAYER_STARTING_Y};

  player->lives = 3;
  player->pos = pos;
}
