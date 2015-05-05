#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "data/prepare.h"

void close(SDL_Window* Window);

//Loads individual image
SDL_Surface* loadSurface( std::string path );

SDL_Surface* gScreenSurface = nullptr;

void close(SDL_Window* Window)
{

  // Destroy window
  SDL_DestroyWindow( Window );
  Window = nullptr;

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
  // prepare() here

  SDL_Window* Window = Prepare::init();


  bool quit = false;
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
    SDL_UpdateWindowSurface( Window );

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close(Window);
  return 0;
}
