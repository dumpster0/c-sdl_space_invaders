#include <stdio.h>

#include "SDL2/SDL.h"

#include "./helpers.h"
#include "./aliens.h"
#include "./player.h"
#include "./bullets.h"
#include "./game.h"
#include "./render.h"

void render_bg(SDL_Renderer* renderer) {
  SDL_Surface* bg_surface;
  SDL_Texture* bg_texture;

  bg_surface = SDL_LoadBMP("./media/invaders_bg.bmp");
  bg_texture = SDL_CreateTextureFromSurface(renderer, bg_surface);
  SDL_FreeSurface(bg_surface);

  SDL_RenderCopy(renderer, bg_texture, NULL, NULL);
  SDL_DestroyTexture(bg_texture);
}

void render_player(player* player, SDL_Renderer* renderer) {
  SDL_Surface* player_surface;
  SDL_Texture* player_texture;

  SDL_Rect player_rect;
  player_rect.h = player_rect.w = SPRITE_SIZE;
  player_rect.x = player->pos.x;
  player_rect.y = player->pos.y;

  player_surface = SDL_LoadBMP("./media/invaders_player.bmp");
  player_texture = SDL_CreateTextureFromSurface(renderer, player_surface);
  SDL_FreeSurface(player_surface);

  SDL_RenderCopy(renderer, player_texture, NULL, &player_rect);

  SDL_DestroyTexture(player_texture);
}

void render_alien(alien* alien, SDL_Renderer* renderer) {
  SDL_Surface* alien_surface;

  SDL_Rect alien_rect;
  alien_rect.h = alien_rect.w = SPRITE_SIZE;
  alien_rect.x = alien->pos.x;
  alien_rect.y = alien->pos.y;

  switch(alien->index) {
    case 0 : alien_surface = SDL_LoadBMP("./media/invaders_boss.bmp"); break;
    case 1 : alien_surface = SDL_LoadBMP("./media/invaders_bezos.bmp"); break;
    case 2 : alien_surface = SDL_LoadBMP("./media/invaders_zucc.bmp"); break;
    case 3 : alien_surface = SDL_LoadBMP("./media/invaders_musk.bmp"); break;
    case 4 : alien_surface = SDL_LoadBMP("./media/invaders_gates.bmp"); break;
  }

  SDL_Texture* alien_texture = SDL_CreateTextureFromSurface(renderer, alien_surface);
  SDL_FreeSurface(alien_surface);
  SDL_RenderCopy(renderer, alien_texture, NULL, &alien_rect);

  SDL_DestroyTexture(alien_texture);
}

void render_bullet(bullet* bullet, SDL_Renderer* renderer) {

}

void render_game(game* game, SDL_Renderer* renderer, SDL_Window* window) {
  render_player(game->player, renderer);

  for(int i = 0; i < ALIEN_BLOCK_ROWS; ++i) {
    for(int j = 0; j < ALIEN_BLOCK_COLUMNS; ++j) {
      render_alien(game->aliens[i][j], renderer);
    }
  }

  for(int i = 0; i < MAX_BULLETS_ON_SCREEN; ++i) {
    render_bullet(game->bullets[i], renderer);
  }
}
