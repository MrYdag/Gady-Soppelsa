#include "MarioFCT.h"

/* -------------------------------Clavier-------------------------------------*/

/* for an alternative keyborad management */
void alternative_HandleEvent(char *key, int *Exit)
{
  // prepare multiplayer game
  SDLKey tabkey[NBPLAYERS][6] = {{SDLK_z ,SDLK_s ,SDLK_q ,SDLK_d , SDLK_SPACE, SDLK_ESCAPE}}; 
  int i;
  for(i=0;i<NBPLAYERS;i++) {
    if (key[tabkey[i][0]]) { //UP
    }

    if (key[tabkey[i][1]]) { //DOWN
    }

    if (key[tabkey[i][2]]) { // LEFT
    }

    if (key[tabkey[i][3]]) { // RIGHT

    }
    if (key[tabkey[i][4]]) { // SPACE
    }
	
    if (key[tabkey[i][5]]) { // ESCAPE
      *Exit = 1;
    }

    
  }
  
}

/*-------------------------------------------------------------*/
void update_events(char* keys, int *Exit)
{
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      *Exit = 1;
      break;
    case SDL_KEYUP:
      keys[event.key.keysym.sym] = 0;
      break;
    case SDL_KEYDOWN:
      switch (event.key.keysym.sym) {
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

/*-------------------------------------------------------------*/

int main(int argc, char* argv[]){
  SDL_Surface  *background,*world, *temp;

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

  int Exit = 0;
  char key[SDLK_LAST] = {0};
  

  while (!Exit) {

      update_events(key,&Exit);
      alternative_HandleEvent(key,&Exit);
    
      /* update the screen */
      SDL_UpdateRect(background, 0, 0, 0, 0);

      for (int x = 0; x < SCREEN_WIDTH / SCREEN_HEIGHT; x++) {
	for (int y = 0; y < SCREEN_HEIGHT / SCREEN_HEIGHT; y++) {
	  SDL_Rect position;
	  position.x = x * SCREEN_HEIGHT;
	  position.y = y * SCREEN_HEIGHT;
	  SDL_BlitSurface(world, NULL, background, &position);
	}
      }

      /* update the world */
      SDL_UpdateRect(background, 0, 0, 0, 0);

    }


  SDL_FreeSurface(world);
  SDL_Quit();

  return 0;


}



