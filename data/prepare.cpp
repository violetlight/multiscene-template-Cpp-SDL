#include "prepare.h"
#include "constants.h"
#include "SDL/SDL_mixer.h"
#include "SDL/SDL_ttf.h"

SDL_Window* Screen::window = nullptr;
SDL_Renderer* Screen::renderer = nullptr;


bool Prepare::init() {
  const char CAPTION[] = "Multiscene Template";
  bool success = true; //currently unused

  // Initialize SDL
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
  {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
    //Initialize SDL_ttf
  }
  else
  {
    if( TTF_Init() == -1 )
    {
       printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
       success = false;
    }
    // Create window
    Screen::window = SDL_CreateWindow(CAPTION,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                Constants::SCREEN_W, Constants::SCREEN_H,
                                SDL_WINDOW_SHOWN);
    if(Screen::window == nullptr)
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      // Get window surface in another function
      //gScreenSurface = SDL_GetWindowSurface( Window );

      Screen::renderer = SDL_CreateRenderer(Screen::window, -1, 0); // wrap this in error catching too
    }
  }

  if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
  {
      success = false;
  }
  return success;

} // need to handle error..
