#include <stdio.h>

#include "./helpers.h"
#include "./aliens.h"

void alien_move(alien* alien, direction direction) {
  
}

void alien_spawn(alien* alien, position pos, int index) { 
  alien->pos = pos;
  alien->status = ALIVE;
  alien->index = index;
  alien->sprite = 0;
}
