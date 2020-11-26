#ifndef RENDER_H
#define RENDER_H

void render_game(game* game, SDL_Renderer* renderer, SDL_Window* window);
void render_bg(SDL_Renderer* renderer);
void render_paused(SDL_Renderer* renderer, game* game);
void render_start(SDL_Renderer* renderer, game* game);
void render_over(SDL_Renderer* renderer, game* game);

#endif
