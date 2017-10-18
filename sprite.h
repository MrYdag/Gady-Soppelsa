#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

struct Sprite_t {
  float x,y;
  float vx,vy;
  int w,h;
  SDL_Surface *picture;
  float current_frame;
  int num_frame;
  int vie;
};

typedef struct Sprite_t sprite_t;

void sprite_init (sprite_t *sprite, float x, float y, float vx, float vy,
                  int w, int h, SDL_Surface *picture, int current_frame,
                  int num_frame, int vie);

void sprite_draw(sprite_t *name, SDL_Surface *background);

void sprite_add (sprite_t *tab, int *ntab, int max, SDL_Surface *sprite_picture,
                  int sprite_size_w, int sprite_size_h, float x, float y,
                  float vx, float vy, int n_frame,
                  int c_frame, float nb_life);

