#ifndef GAME_H
#define GAME_H

typedef enum {
  RUNNING,
  PAUSED,
  OVER
} gamestate;

typedef struct {
  gamestate state;
  int level;
  player* player;
  alien* aliens[ALIEN_BLOCK_ROWS][ALIEN_BLOCK_COLUMNS];
  bullet* bullets[MAX_BULLETS_ON_SCREEN];
} game;

void game_pause(game* game);
void game_resume(game* game);
void game_init(game* game);
void game_update(game* game);

#endif
