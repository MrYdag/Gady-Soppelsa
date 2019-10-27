#include "MarioFCT.h"
#include "event.h"
#include "sprite.h"

int main(int argc, char* argv[]){

    SDL_Surface  *screen,*menu, *world, *temp, *brick, *garane, *grass, *token, *shoot ;
    /* Colorkey for the girl */
    int colorkey;

    double timer = 0;

    bool isJumping = false;

    int shoot_again = true;


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

    /* load Menu*/
    temp  = SDL_LoadBMP("Menu.bmp");
    menu = SDL_DisplayFormat(temp);
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

    /* load Garane */
    temp  = SDL_LoadBMP("Jeton.bmp");
    token = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    /* load Bullet */
    temp  = SDL_LoadBMP("bullet.bmp");
    shoot = SDL_DisplayFormat(temp);
    SDL_FreeSurface(temp);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(garane, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    colorkey = SDL_MapRGB(screen->format, 255, 0, 255);
    SDL_SetColorKey(token, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

    colorkey = SDL_MapRGB(screen->format, 255, 125, 0);
    SDL_SetColorKey(shoot, SDL_SRCCOLORKEY | SDL_RLEACCEL, colorkey);

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

    /* initialisation for tokens */
    int ntab_token = 0;
    sprite_t *tab_token;
    tab_token = malloc(TAB_NUMBER * sizeof (sprite_t));

    /* initialisation for bullet */
    int ntab_shoot = 0;
    sprite_t *tab_shoot;
    tab_shoot = malloc(TAB_NUMBER * sizeof (sprite_t));

    /* initilisation of the girl */
    sprite_t girl;
    sprite_init (&girl, 50, 760, 0, 0, 1, 1, 32, 32, garane, 3, 8, 1);


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
                sprite_add(tab_brick, &ntab_brick, TAB_NUMBER, brick, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 1, 0, 1);
            }

            /* if it is a 2 we draw grass and earth */
            if (tab[i][j] == '2'){
                if (tab[i][j-1] == '2'){
                    sprite_add(tab_grass, &ntab_grass, 1400, grass, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 2, 1, 1);
                }
                else {
                    sprite_add(tab_grass, &ntab_grass, 1400, grass, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 2, 0, 1);
                }
            }

            /* if it is a 4 we draw a token */
            if (tab[i][j] == '4'){
                sprite_add(tab_token, &ntab_token, TAB_NUMBER, token, 32, 32, 32*i, 32*j, 0, 0, 1, 1, 1, 0, 1);
            }
          }
        }
    int fclose(FILE* fichier);


    int Exit = 0;
    int Menu = 0;
    char key[SDLK_LAST] = {0};

    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    position.w = SCREEN_WIDTH;
    position.h = SCREEN_HEIGHT;



    while(!Menu){

        update_events(key, &Menu, &girl);
        alternative_HandleEvent(key, &Exit,&Menu, &girl, &isJumping, tab_shoot, &ntab_shoot,
			     shoot, &shoot_again);


        /* update the menu */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_BlitSurface(menu, NULL, screen, &position);

    }

    while (!Exit){


        update_events(key, &Exit, &girl);
        alternative_HandleEvent(key, &Exit, &Menu, &girl, &isJumping, tab_shoot, &ntab_shoot,
			     shoot, &shoot_again);
        sprite_jump_down(&girl, timer, &isJumping);

        bool collide1;
        //bool collide2;



        for (int r = 0; r <= ntab_grass; r++){
            collide1 = collide(&girl, &tab_grass[r]);

            if (collide1){
                girl.x = tab_grass[r].x - 32;
                girl.y = tab_grass[r].y - 32;
                isJumping = false;
            }
        }





        for (int i = 0; i < ntab_brick; i++){
            sprite_draw(&tab_brick[i], screen);
        }

        for (int j = 0; j < ntab_grass; j++){
            sprite_draw(&tab_grass[j], screen);
        }

        for (int k = 0; k < ntab_token; k++){
            sprite_draw(&tab_token[k], screen);
        }

        for (int l = 0; l < ntab_shoot; l++){
            sprite_move(&tab_shoot[l], 1, 1);
            sprite_draw(&tab_shoot[l], screen);
            //printf("Bonjour  ");
        }

        sprite_draw(&girl, screen);

         /*update the world */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        SDL_BlitSurface(world, NULL, screen, &position);

        timer += 0.001;

    }

    /* Free variables */

    for (int r = 0; r < TAB_HEIGHT; r++){
        free(tab[r]);
    }
    free(tab);


    SDL_FreeSurface(menu);
    SDL_FreeSurface(world);
    SDL_Quit();




    return 0;
}




