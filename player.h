#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  position pos;
  int lives;
} player;

void player_spawn(player* player);
void player_move(player* player, direction direction);

#endif
