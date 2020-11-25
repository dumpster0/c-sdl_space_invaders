#include <stdio.h>

#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"

void bullet_spawn(character shooter, position pos, bullet* bullets[]) {
  bullet* bullet;

  bullet->pos = pos;
  bullet->shooter = shooter;
  bullet->status = ACTIVE;

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    if(bullets[i]->status == INACTIVE) {
      bullets[i] = bullet;
      break;
    }
  }
}

void bullet_move(bullet* bullet) {

}

void check_alien_collision(bullet* bullet, alien aliens[]) {

}

void check_player_collision(bullet* bullet, player* player) {

}
