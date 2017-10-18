#include "sprite.h"

void sprite_init (sprite_t *sprite, float x, float y, float vx, float vy,
		  int w, int h, SDL_Surface *picture, int current_frame,
		  int num_frame, int vie){

  sprite->x = x;
  sprite->y = y;
  sprite->vx = vx;
  sprite->vy = vy;
  sprite->w = w;
  sprite->h = h;
  sprite->picture = picture;
  sprite->current_frame = current_frame;
  sprite->num_frame = num_frame;
  sprite->vie = vie;
}

void sprite_draw(sprite_t *name, SDL_Surface *background){

  /* Define the source rectangle for the BlitSurface */
  SDL_Rect nameImage, namePosition;
  nameImage.y = 0;
  nameImage.w = name->w;
  nameImage.h = name->h;

  /* choose image according to direction and animation flip: */
  nameImage.x = name->w*((int)name->current_frame);
  namePosition.x = (int)name->x;
  namePosition.y = (int)name->y;
  SDL_BlitSurface(name->picture, &nameImage, background, &namePosition);
}

void sprite_add (sprite_t *tab, int *ntab, int max, SDL_Surface *sprite_picture,
                  int sprite_size_w, int sprite_size_h, float x, float y,
                  float vx, float vy, int n_frame, int c_frame, float nb_life){
  if (*ntab < max){
    sprite_init(&tab[*ntab], x, y, vx, vy, sprite_size_w, sprite_size_h, sprite_picture, c_frame, n_frame, nb_life);
    *ntab += 1;
  }
}
