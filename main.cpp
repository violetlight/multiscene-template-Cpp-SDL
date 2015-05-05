#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init();
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

SDL_Window* gWindow = nullptr;
SDL_Surface* gScreenSurface = nullptr;
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
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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




SDL_Surface* loadSurface( std::string path )
{
  //Load image at specified path
  SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
  if( loadedSurface == nullptr )
  {
    printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
  }

  return loadedSurface;
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

  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close();
  return 0;
}
