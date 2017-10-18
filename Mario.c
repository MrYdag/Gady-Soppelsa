#include "MarioFCT.h"
#include "event.h"
#include "sprite.h"

int main(int argc, char* argv[]){

  SDL_Surface  *background, *world, *temp, *block;


  /* initialize SDL */
  SDL_Init(SDL_INIT_VIDEO);

  /* set the title bar */
  SDL_WM_SetCaption("SDL Animation", "SDL Animation");

  /* create window */
  background = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0);

  /* set keyboard repeat */
  SDL_EnableKeyRepeat(20, 20);

  /* load Background */
  temp  = SDL_LoadBMP("Background.bmp");
  world = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);

  /* load Blocks */
  temp  = SDL_LoadBMP("block.bmp");
  block = SDL_DisplayFormat(temp);
  SDL_FreeSurface(temp);


/* tab's memory */
  int **tab;
  tab = (int**)malloc(TAB_WIDTH * sizeof(int*));
  for (int a = 0; a < TAB_WIDTH; a++){
    tab[a] = (int*)malloc(TAB_HEIGHT * sizeof(int));
  }

/* open and read the enters file */

  FILE* fichier = fopen("Niveau1.txt" , "r+");

  int caract;
  int ntab_block = 0;
  sprite_t tab_block[1400];

  for (int j = 0; j < TAB_HEIGHT; j++){
    for (int i = 0; i < TAB_WIDTH; i++){
      caract = fgetc(fichier);
      tab[i][j] = caract;
      if (tab[i][j] == '1'){
          sprite_add(tab_block, &ntab_block, 1400, block, 32, 32, 32*i, 32*j, 0, 0, 1, 0, 1);
	  printf("%d,%d\n", j,i);
      }
    }
  }
  int fclose(FILE* fichier);


  int Exit = 0;
  char key[SDLK_LAST] = {0};


  while (!Exit) {

    update_events(key,&Exit);
    alternative_HandleEvent(key,&Exit);



    for (int x = 0; x < SCREEN_WIDTH / SCREEN_HEIGHT; x++) {
      for (int y = 0; y < SCREEN_HEIGHT / SCREEN_HEIGHT; y++) {
        SDL_Rect position;
        position.x = x * SCREEN_HEIGHT;
        position.y = y * SCREEN_HEIGHT;
        SDL_BlitSurface(world, NULL, background, &position);
      }
    }

    for (int i = 0; i < ntab_block; i++){
      sprite_draw(&tab_block[i], world);
    }

    /* update the world */
    SDL_UpdateRect(background, 0, 0, 0, 0);

  }


  for (int r = 0; r < TAB_HEIGHT; r++){
    free(tab[r]);
  }
  free(tab);

  SDL_FreeSurface(world);
  SDL_Quit();

  return 0;


}



