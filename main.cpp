#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "data/tools.h"
#include "data/prepare.h"


// SDL_Surface* gScreenSurface = nullptr;

void close(SDL_Window* Window)
{

  // Destroy window
  SDL_DestroyWindow( Window );
  Window = nullptr;

  // Quit SDL subsystems
  SDL_Quit();
}



int main ( int argc, char* args[] )
{
  // prepare() here

  SDL_Window* Window = Prepare::init();
  SDL_Renderer* Renderer = SDL_CreateRenderer(Window, -1, 0);


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


    SDL_SetRenderDrawColor(Renderer, 100, 0, 0, 255);
    SDL_RenderClear(Renderer);
    SDL_RenderPresent(Renderer);
    //Update the surface
    //SDL_UpdateWindowSurface( Window );

  } // main loop


  // instantiate control object
  // std::map (dict) of states
  // control object init, pass in states dict
  // control object main loop()

  close(Window);
  return 0;
}
