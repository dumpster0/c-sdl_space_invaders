#ifndef HELPERS_H
#define HELPERS_H

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define SPRITE_SIZE 32

#define MAX_BULLETS_ON_SCREEN

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
