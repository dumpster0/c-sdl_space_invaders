#ifndef ALIENS_H
#define ALIENS_H

typedef enum {
  DEAD,
  ALIVE
} alienstatus;

typedef struct {
  position pos;
  alienstatus status;
  int sprite;
  int index;
} alien;

#endif
