#ifndef EVENT_H
#define EVENT_H

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "sprite.h"

#define NBPLAYERS 1
#define ACCEL 0.005

/* Define events functions */

void alternative_HandleEvent(char *key, int *Exit,int *Menu,sprite_t *sprite, bool *isJumping,
    sprite_t *tab_shoot, int *ntab_shoot, SDL_Surface *shoot, int *shoot_again);

void update_events(char* keys, int *Exit, sprite_t *sprite);

#endif
