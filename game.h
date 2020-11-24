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
} game;

#endif
