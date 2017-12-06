#include "MarioFCT.h"
#include "event.h"
#include "sprite.h"

int main(int argc, char* argv[]){

    SDL_Surface  *screen, *world, *temp, *brick, *garane, *grass, *token;
    /* Colorkey for the girl */
    int colorkey;

    double timer = 0;


    /* initialize SDL */
    SDL_Init(SDL_INIT_VIDEO);

    /* set the title bar */
    SDL_WM_SetCaption("SDL Animation", "SDL Animation");

    /* create window */
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

    /* set keyboard repeat */
    SDL_EnableKeyRepeat(20, 20);

    /* load Background */
    temp  = SDL_LoadBMP("Background.bmp");
    world = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* load Blocks */
    temp  = SDL_LoadBMP("brique.bmp");
    brick = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* load grass */
    temp = SDL_LoadBMP("dirt.bmp");
    grass = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* load Garane */
    temp  = SDL_LoadBMP("sprite.bmp");
    garane = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* load Token */
    temp  = SDL_LoadBMP("jeton.bmp");
    token = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(garane, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(token, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    /* tab's memory */
    int **tab;
    tab = (int**)malloc(TAB_WIDTH * sizeof(int*));
    for (int a = 0; a < TAB_WIDTH; a++){
        tab[a] = (int*)malloc(TAB_HEIGHT * sizeof(int));
    }

    /* open and read the enters file */

    FILE* fichier = fopen("Niveau1.txt" , "r+");

    int caract;

    /* initialisation for bricks */
    int ntab_brick = 0;
    sprite_t *tab_brick;
    tab_brick = malloc(TAB_NUMBER * sizeof (sprite_t));

    /* initialisation for grass */
    int ntab_grass = 0;
    sprite_t *tab_grass;
    tab_grass = malloc(TAB_NUMBER * sizeof (sprite_t));

    /* initialisation for token */
    int ntab_token = 0;
    sprite_t *tab_token;
    tab_token = malloc(TAB_NUMBER * sizeof (sprite_t));

    /* Initialisation for coins
    int ntab_coin = 0;
    sprite_t *tab_coin;
    tab_coin = malloc(TAB_NUMBER * sizeof (sprite_t));*/

    /* initilisation of the girl */
    sprite_t girl;
    sprite_init (&girl, 50, 100, 0, 0, 1, 1, 32, 32, garane, 3, 8, 1, false);


    /* read the file and set the tab */
    for (int j = 0; j < TAB_HEIGHT; j++){
        for (int i = 0; i < TAB_WIDTH; i++){

            /* to get back the caracter in the file */
            caract = fgetc(fichier);

            /* if it isn't a number we don't put it in the tab */
            if (caract != '\n'){
                tab[i][j] = caract;
            }

            /* if it is a 1 we draw a brick */
            if (tab[i][j] == '1'){
                sprite_add(tab_brick, &ntab_brick, TAB_NUMBER, brick,
                           SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE*i, SPRITE_SIZE*j,
                           0, 0, 1, 1, 1, 0, 1, false);
            }

            /* if it is a 2 we draw grass and earth */
            if (tab[i][j] == '2'){
                if (tab[i][j-1] == '2'){
                    sprite_add(tab_grass, &ntab_grass, 1400, grass, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 2, 1, 1, false);
                }
                else {
                    sprite_add(tab_grass, &ntab_grass, 1400, grass, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 2, 0, 1, false);
                }
            }

            /* if it is a 4 we draw a token */
            if (tab[i][j] == '3'){
                sprite_add(tab_token, &ntab_token, TAB_NUMBER, token, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 1, 0, 1, false);
            }
          }
        }

    int fclose(FILE* fichier);


    int Exit = 0;
    char key[SDLK_LAST] = {0};


    while (!Exit){

        update_events(key, &Exit, &girl);
        alternative_HandleEvent(key, &Exit, &girl, &timer);
        sprite_move2(&girl);

        /* Collide with the screen */
        if (girl.x < 0.0){
            girl.x = SCREEN_WIDTH - girl.w;
        }
        if(girl.x > SCREEN_WIDTH - girl.w){
            girl.x = 0.0;
        }
        if (girl.y < 0.0){
            girl.y = 0.0;
            girl.isJumping = true;
            sprite_jump_down(&girl, &timer);
        }
        if (girl.y > SCREEN_HEIGHT - girl.w){
            Exit = 0;
        }


        bool collide_grass;
        bool collide_brick;

        /* Collision with grass (ground) */
        for (int r = 0; r <= ntab_grass; r++){
            collide_grass = collision(&girl, &tab_grass[r]);

            if (collide_grass){
                girl.y = tab_grass[r].y - girl.w;
                girl.vy = 0;
                girl.isJumping = false;
            }
        }


        for (int s = 0; s <= ntab_brick; s++){
            collide_brick = collision(&girl, &tab_brick[s]);

            if (collide_brick){
                girl.isJumping = false;
                girl.vy = 0;
                girl.y -= tab_brick[s].y - girl.w;


        }


                /* collision above bricks
                if (tab_brick[s].y == (girl.y + SPRITE_SIZE)){
                    girl.y = tab_brick[s].y - SPRITE_SIZE;
                    girl.isJumping = false;
                    girl.vy = 0;
                }*/
                /* collision bellow bricks
                if (girl.y == (tab_brick[s].y + SPRITE_SIZE)){
                    girl.y = tab_brick[s].y + SPRITE_SIZE;
                    sprite_jump_down(&girl, &timer);
                }*/

            /* Collision with bricks on the left side and above
            if (collide2 && ((girl.x + girl.w) == tab_brick[s].x)){
                girl.x = tab_brick[s].x - girl.w;
                girl.y = tab_brick[s].y - girl.w;
                girl.vy = 0;
                girl.isJumping = false;
            }*/
            /* Collision with bricks on the right side and above
            if (collide2 && (girl.x == (tab_brick[s].x + tab_brick[s].w))){
                girl.x = tab_brick[s].x + girl.w;
                //girl.y = tab_brick[s].y - girl.w;
                girl.vy = 0;
                girl.isJumping = false;
            }*/


            /* Collision with bricks on the left side
            if (collide2 && (girl.current_frame == 2 || girl.current_frame == 3)){
                girl.x = tab_brick[s].x - girl.w;
            }*/

            /* Collision with bricks above
            if (collide2 && ((girl.y + girl.w) == tab_brick[s].y)){
                girl.y = tab_brick[s].y - girl.w;
                girl.vy = 0;
                girl.isJumping = false;
            }*/
            /* Collision with bricks bellow
            if (collide2 && (girl.y == (tab_brick[s].y + tab_brick[s].w))){
                girl.y = tab_brick[s].y + girl.w;
                sprite_jump_down(&girl, &timer);
            }*/

            //*timer = 0;
            //timer += 0.001;
        }


        SDL_Rect position;
        position.x = 0;
        position.y = 0;
        position.w = SCREEN_WIDTH;
        position.h = SCREEN_HEIGHT;


        for (int i = 0; i <= ntab_brick; i++){
            sprite_draw(&tab_brick[i], screen);
        }
        for (int i = 0; i <= ntab_grass; i++){
            sprite_draw(&tab_grass[i], screen);
        }

        for (int i = 0; i <= ntab_token; i++){
            sprite_draw(&tab_token[i], screen);
        }
        sprite_draw(&girl, screen);

        /* update the world */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_BlitSurface(world, NULL, screen, &position);
    }


    /* Free variables */
    for (int r = 0; r < TAB_HEIGHT; r++){
        free(tab[r]);
    }
    free(tab);

    SDL_FreeSurface(world);
    SDL_Quit();

    return 0;
}



