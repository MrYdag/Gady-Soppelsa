#include "MarioFCT.h"

/* Says if a point is between two others */
bool is_between (float coord1, float coord2, float coordtest){
    if ((coord1 <= coordtest) && (coordtest <= coord2)){
        return true;
    } else{
        return false;
    }
}


/* Collision between two blocks */
bool collision2 (sprite_t *s1, sprite_t *s2){
    if ((is_between(s1->x, s1->x + s1->w, s2->x) && (is_between(s1->y, s1->y + s1->w, s2->y)))
        || (is_between(s2->x, s2->x + s2->w, s1->x + s1->w) && (is_between(s2->y, s2->y + s2->w, s1->y)))
         || (is_between(s1->x, s1->x + s1->w, s2->x + s2->w) && (is_between(s1->y, s1->y + s1->w, s2->y)))
         || (is_between(s2->x, s2->x + s2->w, s1->x) && (is_between(s2->y, s2->y + s2->w, s1->y)))){

            return true;
         } else {
            return false;
         }
}


int collision (sprite_t *sprite1, sprite_t *sprite2){

    float x1 = sprite1->x;
    float x2 = sprite2->x;
    float y1 = sprite1->y;
    float y2 = sprite2->y;
    float w1 = sprite1->w;
    float w2 = sprite2->w;

    if ((max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + w1, y2 + w2))){
        return 1;
    } else {
        return 0;
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
