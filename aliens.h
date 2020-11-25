#ifndef ALIENS_H
#define ALIENS_H

typedef enum {
  DEAD,
  ALIVE
} alienstatus;

typedef struct {
  position pos;
  alienstatus status;
  int index;
  int sprite;
} alien;

void alien_move(alien* alien, direction direction);
void alien_spawn(alien* alien, position pos, int index);

#endif
