#include <sdl2/SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
const char gTitle[] = "Multiscene Template";




bool init()
{
  bool success = true;

  // Initialize SDL
  if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
  {
    printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    success = false;
  }
  else
  {
    // Create window
    gWindow = SDL_CreateWindow( gTitle,
                                SDL_WINDOWPOS_CENTERED,  SDL_WINDOWPOS_CENTERED,
                                SCREEN_WIDTH, SCREEN_HEIGHT,
                                SDL_WINDOW_SHOWN );
    if( gWindow == NULL )
    {
      printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
      success = false;
    }
    else
    {
      // Get window surface
      gScreenSurface = SDL_GetWindowSurface( gWindow );
    }
  }

  return success;
}




void close()
{

  // Destroy window
  SDL_DestroyWindow( gWindow );
  gWindow = NULL;

  // Quit SDL subsystems
  SDL_Quit();
}




int main ( int argc, char* args[] )
{

  if( !init() )
  {
    printf( "Failed to initialize!\n" );
  } else
  {
    bool quit = false;
    // Event handler
    SDL_Event e;

    while( !quit )
    {
      while( SDL_PollEvent( &e ) != 0)
      {
        // Quit event
        if( e.type == SDL_QUIT )
        {
          quit = true;
        }
      } // events

      //Update the surface
      SDL_UpdateWindowSurface( gWindow );

    } // main loop

  }

  // control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close();
  return 0;
}
