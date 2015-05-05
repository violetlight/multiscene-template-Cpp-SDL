#include "prepare.h"
#include "constants.h"


SDL_Window* Prepare::init() {
  const char CAPTION[] = "Multiscene Template";
  SDL_Window* Window = nullptr;
  bool success = true; //currently unused

  // Initialize SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    // Create window
    Window = SDL_CreateWindow( CAPTION,
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                Constants::SCREEN_W, Constants::SCREEN_H,
                                SDL_WINDOW_SHOWN );
    if( Window == nullptr )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      // Get window surface in another function
      //gScreenSurface = SDL_GetWindowSurface( Window );
      return Window;
    }
  }

} // need to handle error..
