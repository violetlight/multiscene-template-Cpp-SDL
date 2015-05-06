#include "prepare.h"
#include "constants.h"


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
  }
  else
  {
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
      return success;
    }
  }

} // need to handle error..
