#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#include "sprite.h"



#define SCREEN_WIDTH  1120
#define SCREEN_HEIGHT 960
#define SPRITE_SIZE 32

#define TAB_WIDTH 36
#define TAB_HEIGHT 30

#define TAB_NUMBER  1081


int collision (sprite_t *sprite1, sprite_t *sprite2);

bool collision2 (sprite_t *s1, sprite_t *s2);

double max (double a, double b);

double min (double a, double b);
