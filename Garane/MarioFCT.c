#include "MarioFCT.h"


/* Collide between 2 objects */
bool collide (sprite_t *sprite1, sprite_t *sprite2){

  if ((max(sprite1->x, sprite2->x) < min(sprite1->x + sprite1->w, sprite2->x + sprite2->w))
      && (max(sprite1->y, sprite2->y) < min(sprite1->y + sprite1->h, sprite2->y + sprite2->h))){

    return true;

  }else {
    return false;
  }
}

/* Gives the maximum between 2 numbers */
double max (double a, double b){
  if (a>b){
    return a;
  }else {
    return b;
  }
}

/* Gives the minimum between 2 numbers */
double min (double a, double b){
  if (a<b){
    return a;
  }else {
    return b;
  }
}
