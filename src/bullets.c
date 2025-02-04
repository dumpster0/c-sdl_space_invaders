#include <stdio.h>

#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"

void bullet_spawn(character shooter, position pos, bullet* bullets[MAX_BULLETS_ON_SCREEN]) {
  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    if(bullets[i]->status == INACTIVE) {
      bullets[i]->pos = pos;
      bullets[i]->shooter = shooter;
      bullets[i]->status = ACTIVE;
      break;
    }
  }
}

void bullet_move(bullet* bullet) {
  switch(bullet->shooter) {
    case PLAYER : bullet->pos.y -= BULLET_SPEED; break;
    case ALIEN : bullet->pos.y += BULLET_SPEED; break;
    default : {}
  }
}

void check_alien_collision(bullet* bullet, alien* aliens[ALIEN_BLOCK_ROWS][ALIEN_BLOCK_COLUMNS]) {
  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      if(bullet->shooter == PLAYER && aliens[i][j]->status == ALIVE && bullet->pos.y + SPRITE_SIZE >= aliens[i][j]->pos.y && bullet->pos.y <= aliens[i][j]->pos.y + SPRITE_SIZE && bullet->pos.x + SPRITE_SIZE >= aliens[i][j]->pos.x && bullet->pos.x <= aliens[i][j]->pos.x + SPRITE_SIZE) {
        bullet->status = INACTIVE;
        aliens[i][j]->status = DEAD;
      }
    }
  }
}

void check_player_collision(bullet* bullet, player* player) {
  if(bullet->shooter == ALIEN && bullet->pos.y + SPRITE_SIZE >= player->pos.y && bullet->pos.y <= player->pos.y + SPRITE_SIZE && bullet->pos.x + SPRITE_SIZE >= player->pos.x && bullet->pos.x <= player->pos.x + SPRITE_SIZE) {
    bullet->status = INACTIVE;
    player->lives -= 1;
  }
}
