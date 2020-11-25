#ifndef HELPERS_H
#define HELPERS_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define SPRITE_SIZE 32

#define MAX_BULLETS_ON_SCREEN 10

#define ALIEN_BLOCK_ROWS 5
#define ALIEN_BLOCK_COLUMNS 8

#define PLAYER_STARTING_X WINDOW_WIDTH/2
#define PLAYER_STARTING_Y WINDOW_HEIGHT - 20

typedef struct {
  int x;
  int y;
} position;

typedef enum {
  PLAYER,
  ALIEN,
  BULLET
} character;

typedef enum {
  LEFT,
  RIGHT
} direction;




#endif
