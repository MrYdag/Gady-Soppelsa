#include "event.h"

/* for an alternative keyboard management */
void alternative_HandleEvent(char *key, int *Exit,int *Menu, sprite_t *sprite,
    bool *isJumping,sprite_t *tab_shoot, int *ntab_shoot,
			     SDL_Surface *shoot, int *shoot_again){

    // prepare multiplayer game
    SDLKey tabkey[NBPLAYERS][6] = {{SDLK_q ,SDLK_d , SDLK_z, SDLK_ESCAPE, SDLK_a, SDLK_SPACE}};
    int i;
    for(i=0; i < NBPLAYERS; i++){

        if (key[tabkey[i][0]]){ // LEFT Q
            sprite_turn_left(sprite);
            sprite_move(sprite, -1, isJumping);
        }

        if (key[tabkey[i][1]]){ // RIGHT Q
            sprite_turn_right(sprite);
            sprite_move(sprite, 1, isJumping);

        }

        /*if (key[tabkey[i][2]]){ // JUMP Z
            sprite_jump(sprite, timer, isJumping);
            sprite_move(sprite, 0, isJumping);
        }
*/
        if (key[tabkey[i][3]]){ // ESCAPE
            *Exit = 1;
        }

        if (key[tabkey[i][4]]){ // ENTER
            *Menu = 1;
            *Exit = 0;
        }

        if (key[tabkey[i][5]]){ // SPACE
            if (*shoot_again) {
                sprite_add(tab_shoot, ntab_shoot, 100, shoot, 8, 8, sprite->x, sprite->y, 1, 1, 0, 1, 0, 0, 10);
                printf("%d  " , *ntab_shoot);
                *shoot_again = false;
            }
        } else {
            *shoot_again = true;
        }

    }
}


void update_events(char* keys, int *Exit, sprite_t *sprite){

      SDL_Event event;
      while(SDL_PollEvent(&event)){
        switch (event.type){
        case SDL_QUIT:
            *Exit = 1;
            break;
        case SDL_KEYUP:
            keys[event.key.keysym.sym] = 0;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym){
            case SDLK_ESCAPE:
                break;
            default:
                break;
            }
            keys[event.key.keysym.sym] = 1;
            break;
        }
    }
}
